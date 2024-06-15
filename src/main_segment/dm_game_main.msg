/**
 * Original name: _mesWriting
 */
const char _mesWriting_dmgamemain[] =
#if VERSION_US || VERSION_GW
    "Now saving." MSG_NEWLINE
    "Do not turn power off."
#elif VERSION_CN
    "存储中" MSG_NEWLINE
    "请勿关闭电源."
#endif
    MSG_END;

const char STR_800B1CE0[] =
#if VERSION_US || VERSION_GW
    "Now deleting." MSG_NEWLINE
    "Do not turn power off."
#elif VERSION_CN
    "删除中" MSG_NEWLINE
    "请勿关闭电源."
#endif
    MSG_END;
