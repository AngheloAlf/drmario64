use std::io::Cursor;
use pigment::*;

// TODO: convert input into all permutations of color type and bit depth
// to test all codepaths

// #[test]
// fn ci8() -> Result<(), Box<dyn std::error::Error>> {
//     let input_bytes = include_bytes!("ci8.png");
//     let image = Image::read_png(&mut Cursor::new(input_bytes));

//     let expected_bytes = include_bytes!("ci8.png.bin");
//     assert_eq!(image.as_ci8(), expected_bytes);
//     Ok(())
// }

// #[test]
// fn ci4() -> Result<(), Box<dyn std::error::Error>> {
//     let input_bytes = include_bytes!("ci4.png");
//     let image = Image::read_png(&mut Cursor::new(input_bytes));

//     let expected_bytes = include_bytes!("ci4.png.bin");
//     assert_eq!(image.as_ci4(), expected_bytes);
//     Ok(())
// }

// #[test]
// fn i4() -> Result<(), Box<dyn std::error::Error>> {
//     let input_bytes = include_bytes!("i4.png");
//     let image = Image::read_png(&mut Cursor::new(input_bytes));

//     let expected_bytes = include_bytes!("i4.png.bin");
//     assert_eq!(image.as_i4(), expected_bytes);
//     Ok(())
// }

#[test]
fn i8() -> Result<(), Box<dyn std::error::Error>> {
    let input_bytes = include_bytes!("i8.png");
    let image = Image::read_png(&mut Cursor::new(input_bytes));

    let expected_bytes = include_bytes!("i8.png.bin");
    assert_eq!(image.as_i8(), expected_bytes);
    Ok(())
}

// #[test]
// fn ia4() -> Result<(), Box<dyn std::error::Error>> {
//     let input_bytes = include_bytes!("ia4.png");
//     let image = Image::read_png(&mut Cursor::new(input_bytes));

//     let expected_bytes = include_bytes!("ia4.png.bin");
//     assert_eq!(image.as_ia4(), expected_bytes);
//     Ok(())
// }

#[test]
fn ia8() -> Result<(), Box<dyn std::error::Error>> {
    let input_bytes = include_bytes!("ia8.png");
    let image = Image::read_png(&mut Cursor::new(input_bytes));

    let expected_bytes = include_bytes!("ia8.png.bin");
    assert_eq!(image.as_ia8(), expected_bytes);
    Ok(())
}

#[test]
fn ia16() -> Result<(), Box<dyn std::error::Error>> {
    let input_bytes = include_bytes!("ia16.png");
    let image = Image::read_png(&mut Cursor::new(input_bytes));

    let expected_bytes = include_bytes!("ia16.png.bin");
    assert_eq!(image.as_ia16(), expected_bytes);
    Ok(())
}

#[test]
fn rgba16() -> Result<(), Box<dyn std::error::Error>> {
    let input_bytes = include_bytes!("rgba16.png");
    let image = Image::read_png(&mut Cursor::new(input_bytes));

    let expected_bytes = include_bytes!("rgba16.png.bin");
    assert_eq!(image.as_rgba16(), expected_bytes);
    Ok(())
}

#[test]
fn rgba32() -> Result<(), Box<dyn std::error::Error>> {
    let input_bytes = include_bytes!("rgba32.png");
    let image = Image::read_png(&mut Cursor::new(input_bytes));

    let expected_bytes = include_bytes!("rgba32.png.bin");
    assert_eq!(image.as_rgba32(), expected_bytes);
    Ok(())
}

// #[test]
// fn palette() -> Result<(), Box<dyn std::error::Error>> {
//     let input_bytes = include_bytes!("ci8.png");
//     let palette = get_palette_rgba16(&mut Cursor::new(input_bytes));

//     let expected_bytes = include_bytes!("ci8.pal.bin");
//     assert_eq!(palette, expected_bytes);
//     Ok(())
// }
