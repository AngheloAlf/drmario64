use std::io::prelude::*;
use png::{ColorType, BitDepth};

// TODO: make this an option or sompthin, also ask clover
#[inline]
fn rgb_to_intensity(r: u8, g: u8, b: u8) -> u8 {
    (r as f32 * 0.2126 + g as f32 * 0.7152 + 0.0722 * b as f32) as u8
}

#[inline]
fn u8_to_u4(x: u8) -> u8 {
    x >> 4
}

#[inline]
// convert rgba8888 to rgba16
fn pack_color(r: u8, g: u8, b: u8, a: u8) -> (u8, u8) {
    let r = (r >> 3) as u16;
    let g = (g >> 3) as u16;
    let b = (b >> 3) as u16;
    let a = (a > 127) as u16;
    
    let s = (r << 11) | (g << 6) | ( b << 1) | a;

    ((s >> 8) as u8, s as u8)
}

pub struct Image {
    data: Vec<u8>,
    color_type: ColorType,
    bit_depth: BitDepth,
    width: u32,
    height: u32,
}

impl Image {
    pub fn read_png<R: Read>(r: R) -> Image {
        let decoder = png::Decoder::new(r);
        let mut reader = decoder.read_info().unwrap();
        // Allocate the output buffer.
        let mut buf = vec![0; reader.output_buffer_size()];
        // Read the next frame. An APNG might contain multiple frames.
        let info = reader.next_frame(&mut buf).unwrap();

        // Grab the bytes of the image.
        let input_bytes = &buf[..info.buffer_size()];

        Image {
            data: input_bytes.to_vec(),
            color_type: info.color_type,
            bit_depth: info.bit_depth,
            width: info.width,
            height: info.height,
        }
    }

    pub fn flip(&self, flip_x: bool, flip_y: bool) -> Image {
        let mut flipped_bytes = vec![0; self.data.len()];

        match (flip_x, flip_y) {
            (true, true) => {
                for y in 0..self.height {
                    for x in 0..self.width {
                        let old_index = (y * self.width + x) as usize * self.color_type.samples();
                        let new_index = ((self.height - y - 1) * self.width + (self.width - x - 1)) as usize * self.color_type.samples();
                        flipped_bytes[new_index..new_index + self.color_type.samples()].copy_from_slice(&self.data[old_index..old_index + self.color_type.samples()]);
                    }
                }
            },
            (true, false) => {
                for y in 0..self.height {
                    for x in 0..self.width {
                        let old_index = (y * self.width + x) as usize * self.color_type.samples();
                        let new_index = (y * self.width + (self.width - x - 1)) as usize * self.color_type.samples();
                        flipped_bytes[new_index..new_index + self.color_type.samples()].copy_from_slice(&self.data[old_index..old_index + self.color_type.samples()]);
                    }
                }
            },
            (false, true) => {
                for y in 0..self.height {
                    for x in 0..self.width {
                        let old_index = (y * self.width + x) as usize * self.color_type.samples();
                        let new_index = ((self.height - y - 1) * self.width + x) as usize * self.color_type.samples();
                        flipped_bytes[new_index..new_index + self.color_type.samples()].copy_from_slice(&self.data[old_index..old_index + self.color_type.samples()]);
                    }
                }
            },
            (false, false) => {
                flipped_bytes.copy_from_slice(&self.data);
            }
        }

        // return self with the new flipped bytes
        Image {
            data: flipped_bytes,
            color_type: self.color_type,
            bit_depth: self.bit_depth,
            width: self.width,
            height: self.height,
        }
    }

    /*
    /// Convert to ColorType::Rgba BitDepth::Eight
    fn as_rgba_eight(&self) -> Image {
        match (self.color_type, self.bit_depth) {
            (ColorType::Grayscale, BitDepth::Sixteen) => Image {
                data: self.data
                    .chunks_exact(2)
                    .flat_map(|chunk| {
                        let x = chunk[0] << 8 | chunk[1];
                        let x = (x as f32 / 0xFFFF as f32 * 0xFF as f32) as u8;
                        vec![x, x, x, 0xFF]
                    })
                    .collect(),
                color_type: ColorType::Rgba,
                bit_depth: BitDepth::Eight,
            },
            (ColorType::Grayscale, BitDepth::Eight) => Image {
                data: self.data
                    .iter()
                    .flat_map(|&x| vec![x, x, x, 0xFF])
                    .collect(),
                color_type: ColorType::Rgba,
                bit_depth: BitDepth::Eight,
            },
            (ColorType::Grayscale, BitDepth::Four) => Image {
                data: self.data
                    .iter()
                    .flat_map(|&x| vec![x, x, x, 0xFF])
                    .collect(),
                color_type: ColorType::Rgba,
                bit_depth: BitDepth::Eight,
            },
            (ColorType::Rgba, BitDepth::Eight) => Image {
                data: self.data.to_vec(),
                color_type: ColorType::Rgba,
                bit_depth: BitDepth::Eight,
            },
            (ColorType::Rgb, BitDepth::Eight) => Image {
                data: self.data
                    .chunks_exact(3)
                    .flat_map(|chunk| vec![chunk[0], chunk[1], chunk[2], 0xFF])
                    .collect(),
                color_type: ColorType::Rgba,
                bit_depth: BitDepth::Eight,
            },
            (ColorType::Indexed, BitDepth::Eight) => Image {
                data: self.data
                    .iter()
                    .flat_map(|&x| vec![x, x, x, 0xFF])
                    .collect(),
                color_type: ColorType::Rgba,
                bit_depth: BitDepth::Eight,
            },
        }
    }
    */

    pub fn as_ci8(&self) -> Vec<u8> {
        assert!(self.bit_depth == png::BitDepth::Eight);
        assert!(self.color_type == png::ColorType::Indexed);
        self.data.to_vec()
    }

    pub fn as_ci4(&self) -> Vec<u8> {
        assert!(self.color_type == png::ColorType::Indexed);

        match self.bit_depth {
            BitDepth::Four => self.data.to_vec(),
            BitDepth::Eight => self.data
                .chunks_exact(2)
                .map(|chunk| chunk[0] << 4 | chunk[1])
                .collect(),
            _ => panic!("unsupported bit depth: {:?}", self.bit_depth)
        }
    }

    pub fn as_i4(&self) -> Vec<u8> {
        match (self.color_type, self.bit_depth) {
            (ColorType::Grayscale, BitDepth::Four) => self.data.to_vec(),
            (ColorType::Grayscale, BitDepth::Eight) => self.data
                .chunks_exact(2)
                .map(|chunk| u8_to_u4(chunk[0]) << 4 | u8_to_u4(chunk[1]))
                .collect(),
            (ColorType::Rgba, BitDepth::Eight) => self.data
                .chunks_exact(8)
                .map(|chunk| {
                    let i1 = rgb_to_intensity(chunk[0], chunk[1], chunk[2]);
                    let i2 = rgb_to_intensity(chunk[4], chunk[5], chunk[6]);
                    u8_to_u4(i1) << 4 | u8_to_u4(i2)
                })
                .collect(),
            (ColorType::Rgb, BitDepth::Eight) => self.data
                .chunks_exact(6)
                .map(|chunk| {
                    let i1 = rgb_to_intensity(chunk[0], chunk[1], chunk[2]);
                    let i2 = rgb_to_intensity(chunk[3], chunk[4], chunk[5]);
                    u8_to_u4(i1) << 4 | u8_to_u4(i2)
                })
                .collect(),
            p => panic!("unsupported format {:?}", p)
        }
    }

    pub fn as_i8(&self) -> Vec<u8> {
        match (self.color_type, self.bit_depth) {
            (ColorType::Grayscale, BitDepth::Eight) => self.data.to_vec(),
            (ColorType::Grayscale, BitDepth::Four) => self.data
                .chunks_exact(2)
                .map(|chunk| chunk[0] << 4 | chunk[1])
                .collect(),
            (ColorType::Rgba, BitDepth::Eight) => self.data
                .chunks_exact(4)
                .map(|chunk| rgb_to_intensity(chunk[0], chunk[1], chunk[2]))
                .collect(),
            (ColorType::Rgb, BitDepth::Eight) => self.data
                .chunks_exact(3)
                .map(|chunk| rgb_to_intensity(chunk[0], chunk[1], chunk[2]))
                .collect(),
            p => panic!("unsupported format {:?}", p)
        }
    }

    pub fn as_ia4(&self) -> Vec<u8> {
        match (self.color_type, self.bit_depth) {
            (ColorType::GrayscaleAlpha, BitDepth::Eight) => self.data
                .chunks_exact(4)
                .map(|chunk| {
                    let intensity = (chunk[0] >> 5) << 1;
                    let alpha = (chunk[1] > 127) as u8;
                    let high = intensity | alpha;

                    let intensity = (chunk[2] >> 5) << 1;
                    let alpha = (chunk[3] > 127) as u8;
                    let low = intensity | alpha;

                    high << 4 | (low & 0xF)
                })
                .collect(),
            p => panic!("unsupported format {:?}", p)
        }
    }

    pub fn as_ia8(&self) -> Vec<u8> {
        match (self.color_type, self.bit_depth) {
            (ColorType::GrayscaleAlpha, BitDepth::Eight) => self.data
                .chunks_exact(2)
                .map(|chunk| chunk[0] << 4 | (chunk[1] & 0x0F))
                .collect(),
            p => panic!("unsupported format {:?}", p)
        }
    }

    pub fn as_ia16(&self) -> Vec<u8> {
        match (self.color_type, self.bit_depth) {
            (ColorType::GrayscaleAlpha, BitDepth::Eight) => self.data.to_vec(),
            p => panic!("unsupported format {:?}", p)
        }
    }

    pub fn as_rgba16(&self) -> Vec<u8> {
        match (self.color_type, self.bit_depth) {
            (ColorType::Rgba, BitDepth::Eight) => self.data
                .chunks_exact(4)
                .flat_map(|chunk| {
                    let (first, second) = pack_color(chunk[0], chunk[1], chunk[2], chunk[3]);
                    [first, second].into_iter()
                })
                .collect(),
            p => panic!("unsupported format {:?}", p)
        }
    }

    pub fn as_rgba32(&self) -> Vec<u8> {
        match (self.color_type, self.bit_depth) {
            (ColorType::Rgba, BitDepth::Eight) => self.data.to_vec(),
            p => panic!("unsupported format {:?}", p)
        }
    }
}

pub fn get_palette_rgba16<R: Read>(r: R) -> Vec<u8> {
    let decoder = png::Decoder::new(r);
    let reader = decoder.read_info().unwrap();
    let info = reader.info();
    let rgb_data = info.palette.as_ref().expect("no palette");
    let alpha_data = info.trns.as_ref();

    match alpha_data {
        Some(alpha_data) => rgb_data
            .chunks_exact(3)
            .zip(alpha_data.iter())
            .flat_map(|(rgb, &alpha)| {
                let (first, second) = pack_color(rgb[0], rgb[1], rgb[2], alpha);
                [first, second].into_iter()
            })
            .collect(),

        // If there's no alpha channel, assume everything is opaque
        None => rgb_data
            .chunks_exact(3)
            .flat_map(|rgb| {
                let (first, second) = pack_color(rgb[0], rgb[1], rgb[2], 0xFF);
                [first, second].into_iter()
            })
            .collect(),
    }
}
