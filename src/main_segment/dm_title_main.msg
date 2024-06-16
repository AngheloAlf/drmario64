const char STR_800B32A8[] =
#if VERSION_US || VERSION_GW
    "This game is not designed" MSG_NEWLINE
    "for use on this system."
#elif VERSION_CN
    "本游戏不是为此系统设计的。"
#endif
    MSG_END;

/**
 * Original name: _mesBootContErr
 */
const char _mesBootContErr[] =
#if VERSION_US || VERSION_GW
    "There is no controller" MSG_NEWLINE
    "connected. Please turn OFF" MSG_NEWLINE
    "the Nintendo* 64 and insert" MSG_NEWLINE
    "a controller in socket 1."
#elif VERSION_CN
    "没有连接"
#endif
    MSG_END;

/**
 * Original name: _mesBootCSumErr
 */
const char _mesBootCSumErr[] =
#if VERSION_US || VERSION_GW
    "A Backup File is damaged." MSG_NEWLINE
    "Press the A Button to delete this file."
#elif VERSION_CN
    "备份文件已损坏。" MSG_NEWLINE
    "按A键删除这个文件。"
#endif
    MSG_END;
