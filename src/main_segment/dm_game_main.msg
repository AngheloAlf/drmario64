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

/**
 * Original name: _mesPassword
 */
char _mesPassword[] =
    MSG_COLOR(BLACK) "     Password" MSG_NEWLINE
    MSG_END;

/**
 * Original name: _mesEasyCont
 */
char _mesEasyCont[] = MSG_H MSG_COLOR(BLUE)
#if VERSION_US || VERSION_GW
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    "Congratulations!" MSG_NEWLINE
    "Next time try to" MSG_NEWLINE
    "finish EASY" MSG_NEWLINE
    "without losing." MSG_NEWLINE
#elif VERSION_CN
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    "祝贺你！" MSG_NEWLINE
    "下次尝试" MSG_NEWLINE
    "不要在" MSG_NEWLINE
    "生手模式中失败" MSG_NEWLINE
    MSG_NEWLINE
    "中国制作 神游工程部" MSG_NEWLINE
#endif
    MSG_WAIT(2) MSG_END;

/**
 * Original name: _mesEasyNoCont
 */
char _mesEasyNoCont[] = MSG_H MSG_COLOR(BLUE)
#if VERSION_US || VERSION_GW
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    "Congratulations! You" MSG_NEWLINE
    "finished EASY without" MSG_NEWLINE
    "losing." MSG_NEWLINE
    "Now try NORMAL." MSG_NEWLINE
#elif VERSION_CN
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    "祝贺你！" MSG_NEWLINE
    "你以全胜成绩" MSG_NEWLINE
    "完成了生手模式" MSG_NEWLINE
    "现在试试熟手模式吧" MSG_NEWLINE
    MSG_NEWLINE
    "中国制作  神游工程部" MSG_NEWLINE
#endif
    MSG_WAIT(2) MSG_END;

/**
 * Original name: _mesNormalCont
 */
char _mesNormalCont[] = MSG_H MSG_COLOR(ORANGE2)
#if VERSION_US || VERSION_GW
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    "Congratulations!" MSG_NEWLINE
    "Next time try to" MSG_NEWLINE
    "finish NORMAL" MSG_NEWLINE
    "without losing." MSG_NEWLINE
#elif VERSION_CN
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    "祝贺你！" MSG_NEWLINE
    "下次尝试" MSG_NEWLINE
    "不要在" MSG_NEWLINE
    "熟手模式中失败" MSG_NEWLINE
    MSG_NEWLINE
    "中国制作  神游工程部" MSG_NEWLINE
#endif
    MSG_WAIT(2) MSG_END;

/**
 * Original name: _mesNormalNoCont
 */
char _mesNormalNoCont[] = MSG_H MSG_COLOR(ORANGE2)
#if VERSION_US || VERSION_GW
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    "Congratulations! You" MSG_NEWLINE
    "finished NORMAL" MSG_NEWLINE
    "without losing." MSG_NEWLINE
    "Now try HARD." MSG_NEWLINE
#elif VERSION_CN
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    "祝贺你！" MSG_NEWLINE
    "你以全胜成绩" MSG_NEWLINE
    "完成了熟手模式" MSG_NEWLINE
    "现在试试高手模式吧" MSG_NEWLINE
    MSG_NEWLINE
    "中国制作  神游工程部" MSG_NEWLINE
#endif
    MSG_WAIT(2) MSG_END;

/**
 * Original name: _mesHardCont
 */
char _mesHardCont[] = MSG_H MSG_COLOR(ORANGE)
#if VERSION_US || VERSION_GW
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    "Congratulations!" MSG_NEWLINE
    "Next time try to" MSG_NEWLINE
    "finish HARD" MSG_NEWLINE
    "without losing." MSG_NEWLINE
#elif VERSION_CN
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    "祝贺你！" MSG_NEWLINE
    "下次尝试" MSG_NEWLINE
    "不要在" MSG_NEWLINE
    "高手模式中失败" MSG_NEWLINE
    MSG_NEWLINE
    "中国制作  神游工程部" MSG_NEWLINE
#endif
    MSG_WAIT(2) MSG_END;

/**
 * Original name: _mesHardCont
 */
char _mesHardNoCont[] = MSG_H MSG_COLOR(ORANGE)
#if VERSION_US || VERSION_GW
    "Congratulations! You" MSG_NEWLINE
    "finished HARD" MSG_NEWLINE
    "without losing." MSG_NEWLINE
    "Great job! Now let me" MSG_NEWLINE
    "tell you a secret." MSG_NEWLINE
    "Hold down the Z Button" MSG_NEWLINE
    "while selecting the" MSG_NEWLINE
    "HARD Story Mode level" MSG_NEWLINE
    "and the level will" MSG_NEWLINE
    "become SUPER HARD."
#elif VERSION_CN
    "祝贺你！" MSG_NEWLINE
    "你以全胜成绩" MSG_NEWLINE
    "完成了高手模式。" MSG_NEWLINE
    "真是了不起！现在让我" MSG_NEWLINE
    "告诉你一个秘密。" MSG_NEWLINE
    "按住Z键选择高手故事模式" MSG_NEWLINE
    "就能将难度提升为圣手。" MSG_NEWLINE
    "中国制作  神游工程部" MSG_NEWLINE
#endif
    MSG_WAIT(2) MSG_END;

/**
 * Original name: _mesSHardCont
 */
char _mesSHardCont[] = MSG_H MSG_COLOR(GREEN)
#if VERSION_US || VERSION_GW
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    "Congratulations!" MSG_NEWLINE
    "Next time try to" MSG_NEWLINE
    "finish SUPER HARD" MSG_NEWLINE
    "without losing." MSG_NEWLINE
#elif VERSION_CN
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    "祝贺你！" MSG_NEWLINE
    "下次尝试" MSG_NEWLINE
    "不要在" MSG_NEWLINE
    "圣手模式中失败" MSG_NEWLINE
    MSG_NEWLINE
    "中国制作  神游工程部" MSG_NEWLINE
#endif
    MSG_WAIT(2) MSG_END;

/**
 * Original name: _mesSHardNoCont
 */
char _mesSHardNoCont[] = MSG_H MSG_COLOR(GREEN)
#if VERSION_US || VERSION_GW
    MSG_NEWLINE
    MSG_NEWLINE
    MSG_NEWLINE
    "Congratulations! You" MSG_NEWLINE
    "finished SUPER HARD" MSG_NEWLINE
    "without losing." MSG_NEWLINE
    "Amazing! You are truly" MSG_NEWLINE
    "A Dr. Mario expert!" MSG_NEWLINE
#elif VERSION_CN
    MSG_NEWLINE
    MSG_NEWLINE
    "祝贺你！" MSG_NEWLINE
    "你以全胜成绩" MSG_NEWLINE
    "完成了圣手模式。" MSG_NEWLINE
    "不可思议！你是一名真正的 " MSG_NEWLINE
    "马力欧医生专家" MSG_NEWLINE
    MSG_NEWLINE
    "中国制作  神游工程部" MSG_NEWLINE
#endif
    MSG_WAIT(2) MSG_END;

