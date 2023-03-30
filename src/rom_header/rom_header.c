#include "version.h"
#include "libultra.h"

typedef struct RomHeader {
    /* 0x00 */ u32 unk_00; // PI BSB Domain 1 register
    /* 0x04 */ u32 clockrate;
    /* 0x08 */ void (*entrypointAddr)(void);
    /* 0x0C */ u16 unk_0C;
    /* 0x0E */ u8 revision;
    /* 0x0F */ char libultraVersion;

    /* 0x10 */ u32 checksum1;
    /* 0x14 */ u32 checksum2;
    /* 0x18 */ u32 unk_18;
    /* 0x1C */ u32 unk_1C;

    /* 0x20 */ char gameName[20];

    /* 0x34 */ u32 unk_34;
    /* 0x38 */ u32 unk_38;
    /* 0x3C */ char cartridgeId[2];
    /* 0x3E */ char countryCode;
    /* 0x3F */ u8 version;
} RomHeader; // size = 0x40

void entrypoint(void);

extern u32 ROMHEADER_CHECKSUM1;
extern u32 ROMHEADER_CHECKSUM2;

RomHeader gRomHeader = {
    // unk_00
    0x80371240,
    // clockrate
    0x0000000F,
    // entrypointAddr
    entrypoint,
    // unk_0C
    0x0000,
    // revision
    20,
// libultraVersion
#if VERSION_US
    'K',
#elif VERSION_CN
    'L',
#else
    '\0',
#endif

    // checksum1
    (u32)&ROMHEADER_CHECKSUM1,
    // checksum2
    (u32)&ROMHEADER_CHECKSUM2,
    // unk_18
    0x00000000,
    // unk_1C
    0x00000000,

// gameName
#if VERSION_US
    "DR.MARIO 64         ",
#else
    "",
#endif

    // unk_34
    0x00000000,
// unk_38
#if VERSION_US
    0x0000004E,
#else
    0,
#endif
// cartridgeId
#if VERSION_US
    "N6",
#else
    "",
#endif
// countryCode
#if VERSION_US
    'E',
#else
    0,
#endif
    // version
    0,
};
