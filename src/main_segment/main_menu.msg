const char _mesP1[] =
#if VERSION_US || VERSION_GW
    "This is the" MSG_NEWLINE
    "one-player mode."
#elif VERSION_CN
    "这是单人游戏模式。"
#endif
    MSG_END;

const char _mes2P[] =
#if VERSION_US || VERSION_GW
    "This is the" MSG_NEWLINE
    "two-player mode."
#elif VERSION_CN
    "这是双人游戏模式。"
#endif
    MSG_END;

const char _mes4P[] =
#if VERSION_US || VERSION_GW
    "This is the" MSG_NEWLINE
    "multiplayer mode" MSG_NEWLINE
    "for up to" MSG_NEWLINE
    "four players."
#elif VERSION_CN
    "这是最多四人的多人" MSG_NEWLINE
    "游戏模式。"
#endif
    MSG_END;

const char _mesOpt[] =
#if VERSION_US || VERSION_GW
    "Various setups" MSG_NEWLINE
    "and options are" MSG_NEWLINE
    "available here."
#elif VERSION_CN
    "这里有各种游戏设定" MSG_NEWLINE
    "和选项。"
#endif
    MSG_END;

const char _mesSt[] =
#if VERSION_US || VERSION_GW
    "The thrilling tale" MSG_NEWLINE
    "of Dr. Mario and" MSG_NEWLINE
    "the Cold Caper." MSG_WAIT(2) MSG_H
    "Force your foe to" MSG_NEWLINE
    "retire by sending" MSG_NEWLINE
    "them garbage" MSG_WAIT(2) MSG_H
    "or destroy all" MSG_NEWLINE
    "of your own" MSG_NEWLINE
    "viruses to win." MSG_WAIT(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_WAIT(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_WAIT(2) MSG_H
#elif VERSION_CN
    "发生在马力欧医生和" MSG_NEWLINE
    "感冒狂人之间的精彩" MSG_NEWLINE
    "故事。" MSG_WAIT(2) MSG_H
    "通过送给对手垃圾," MSG_NEWLINE
    "逼迫他们退出游戏。" MSG_WAIT(2) MSG_H
    "或消灭自己所有的病" MSG_NEWLINE
    "毒来赢得胜利。 " MSG_WAIT(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_WAIT(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_WAIT(2) MSG_H
#endif
    MSG_END;

const char _mesLv[] =
#if VERSION_US || VERSION_GW
    "Continue playing" MSG_NEWLINE
    "until you fail" MSG_NEWLINE
    "to clear a stage." MSG_WAIT(2) MSG_H
    "Destroy all the" MSG_NEWLINE
    "viruses to clear" MSG_NEWLINE
    "a stage." MSG_WAIT(2) MSG_H
    "The higher the" MSG_NEWLINE
    "level, the more" MSG_NEWLINE
    "viruses you have" MSG_NEWLINE
    "to destroy." MSG_WAIT(2)
    MSG_H "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_WAIT(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_WAIT(2) MSG_H
#elif VERSION_CN
    "持续游戏直到在一局" MSG_NEWLINE
    "中失败。" MSG_WAIT(2) MSG_H
    "消灭所有病毒才能过" MSG_NEWLINE
    "关。" MSG_WAIT(2) MSG_H
    "游戏难度等级越高," MSG_NEWLINE
    "需要消灭的病毒就越" MSG_NEWLINE
    "多。" MSG_WAIT(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_WAIT(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_WAIT(2) MSG_H
#endif
    MSG_END;

const char _mesVsCom[] =
#if VERSION_US || VERSION_GW
    "This is your" MSG_NEWLINE
    "chance to play" MSG_NEWLINE
    "against the" MSG_NEWLINE
    "computer." MSG_WAIT(2) MSG_H
    "Play against" MSG_NEWLINE
    "any character" MSG_NEWLINE
    "you'd like." MSG_WAIT(2) MSG_H
    "Force your foe to" MSG_NEWLINE
    "retire by sending" MSG_NEWLINE
    "them garbage" MSG_WAIT(2) MSG_H
    "or destroy all" MSG_NEWLINE
    "of your own" MSG_NEWLINE
    "viruses to win." MSG_WAIT(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_WAIT(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_WAIT(2) MSG_H
#elif VERSION_CN
    "这是你和电脑对抗的" MSG_NEWLINE
    "机会。" MSG_WAIT(2) MSG_H
    "选定任意一个你喜欢" MSG_NEWLINE
    "的对手开始游戏。" MSG_WAIT(2) MSG_H
    "通过送给对手垃圾, " MSG_NEWLINE
    "逼迫他们退出游戏。" MSG_WAIT(2) MSG_H
    "或消灭自己所有的" MSG_NEWLINE
    "病毒来赢得胜利。 " MSG_WAIT(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_WAIT(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_WAIT(2) MSG_H
#endif
    MSG_END;

const char _mesVcFlash[] =
#if VERSION_US || VERSION_GW
    "Clear levels by" MSG_NEWLINE
    "destroying the" MSG_NEWLINE
    "flashing viruses." MSG_WAIT(2) MSG_H
    "Play against" MSG_NEWLINE
    "any character" MSG_NEWLINE
    "you'd like." MSG_WAIT(2) MSG_H
    "Force your foe to" MSG_NEWLINE
    "retire by sending" MSG_NEWLINE
    "them garbage" MSG_WAIT(2) MSG_H
    "or destroy all" MSG_NEWLINE
    "of your own" MSG_NEWLINE
    "viruses to win." MSG_WAIT(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_WAIT(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_WAIT(2) MSG_H
#elif VERSION_CN
    "消灭所有的闪光病毒" MSG_NEWLINE
    "以取胜。" MSG_WAIT(2) MSG_H
    "选定任意一个你喜欢" MSG_NEWLINE
    "的对手开始游戏。" MSG_WAIT(2) MSG_H
    "通过送给对手垃圾, " MSG_NEWLINE
    "逼迫他们退出游戏" MSG_WAIT(2) MSG_H
    "或消灭自己所有的病" MSG_NEWLINE
    "毒来赢得胜利。 " MSG_WAIT(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_WAIT(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_WAIT(2) MSG_H
#endif
    MSG_END;

const char _mesLvTaiQ[] =
#if VERSION_US || VERSION_GW
    "Viruses multiply" MSG_NEWLINE
    "rapidly in this" MSG_NEWLINE
    "mode." MSG_WAIT(2) MSG_H
    "Completing combos" MSG_NEWLINE
    "will slow down" MSG_NEWLINE
    "the speed of the" MSG_NEWLINE
    "virus growth." MSG_WAIT(2) MSG_H
    "Destroy the" MSG_NEWLINE
    "viruses to keep" MSG_NEWLINE
    "the bottle clear." MSG_WAIT(2) MSG_H
    "Press the L Button" MSG_NEWLINE
    "to speed up the" MSG_NEWLINE
    "multiplication" MSG_NEWLINE
    "of the viruses." MSG_WAIT(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_WAIT(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_WAIT(2) MSG_H
#elif VERSION_CN
    "在这个模式中病毒会" MSG_NEWLINE
    "高速繁殖。" MSG_WAIT(2) MSG_H
    "连消病毒可以降低" MSG_NEWLINE
    "它们的繁殖速度。" MSG_WAIT(2) MSG_H
    "消灭病毒以保持瓶子" MSG_NEWLINE
    "清洁。" MSG_WAIT(2) MSG_H
    "按L键可以加快病毒" MSG_NEWLINE
    "的繁殖。" MSG_WAIT(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_WAIT(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_WAIT(2) MSG_H
#endif
    MSG_END;

const char _mesLvTimeAt[] =
#if VERSION_US || VERSION_GW
    "Try to get the" MSG_NEWLINE
    "highest score" MSG_NEWLINE
    "possible in a set" MSG_NEWLINE
    "amount of time." MSG_WAIT(2) MSG_H
    "Aim for a high" MSG_NEWLINE
    "score by" MSG_NEWLINE
    "destroying many" MSG_NEWLINE
    "viruses at once." MSG_WAIT(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_WAIT(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_WAIT(2) MSG_H
#elif VERSION_CN
    "尽力在限定时间内争" MSG_NEWLINE
    "取最高分。" MSG_WAIT(2) MSG_H
    "同时消灭很多病毒可" MSG_NEWLINE
    "争取最高分。" MSG_WAIT(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_WAIT(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_WAIT(2) MSG_H
#endif
    MSG_END;

const char _mesNs1[] =
#if VERSION_US || VERSION_GW
    "Please input" MSG_NEWLINE
    "your name." MSG_WAIT(2) MSG_H
    "Please select NEW" MSG_NEWLINE
    "or GUEST if this" MSG_NEWLINE
    "is your first" MSG_NEWLINE
    "time playing." MSG_WAIT(2) MSG_H
#elif VERSION_CN
    "请输入你的名字。" MSG_WAIT(2) MSG_H
    "如果是第一次游戏，" MSG_NEWLINE
    "请选择：" MSG_NEWLINE
    "新游戏或玩家。" MSG_WAIT(2) MSG_H
#endif
    MSG_END;

const char _mesNs2[] =
#if VERSION_US || VERSION_GW
    "Please input" MSG_NEWLINE
    "your name."
#elif VERSION_CN
    "请输入你的名字。"
#endif
    MSG_END;

const char _mesVsMan[] =
#if VERSION_US || VERSION_GW
    "Compete against" MSG_NEWLINE
    "another player." MSG_WAIT(2) MSG_H
    "Force your foe to" MSG_NEWLINE
    "retire by sending" MSG_NEWLINE
    "them garbage" MSG_WAIT(2) MSG_H
    "or destroy all" MSG_NEWLINE
    "of your own" MSG_NEWLINE
    "viruses to win." MSG_WAIT(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_WAIT(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_WAIT(2) MSG_H
#elif VERSION_CN
    "和另外一个玩家比赛。" MSG_WAIT(2) MSG_H
    "通过送给对手垃圾," MSG_NEWLINE
    "逼迫他们退出游戏" MSG_WAIT(2) MSG_H
    "或消灭自己所有的病" MSG_NEWLINE
    "毒来赢得胜利。 " MSG_WAIT(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_WAIT(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_WAIT(2) MSG_H
#endif
    MSG_END;

const char _mesVmFlash[] =
#if VERSION_US || VERSION_GW
    "Clear levels" MSG_NEWLINE
    "by destroying the" MSG_NEWLINE
    "flashing viruses." MSG_WAIT(2) MSG_H
    "Clear combos to" MSG_NEWLINE
    "send garbage to" MSG_NEWLINE
    "your opponent." MSG_WAIT(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_WAIT(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_WAIT(2) MSG_H
#elif VERSION_CN
    "消灭所有的闪光病毒" MSG_NEWLINE
    "以取胜。" MSG_WAIT(2) MSG_H
    "完成连消能送给对手垃圾。" MSG_WAIT(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_WAIT(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_WAIT(2) MSG_H
#endif
    MSG_END;

const char _mesVmTimeAt[] =
#if VERSION_US || VERSION_GW
    "Try to get the" MSG_NEWLINE
    "highest score" MSG_NEWLINE
    "possible in a set" MSG_NEWLINE
    "amount of time." MSG_WAIT(2) MSG_H
    "Aim for a high" MSG_NEWLINE
    "score by" MSG_NEWLINE
    "destroying many" MSG_NEWLINE
    "viruses at once." MSG_WAIT(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_WAIT(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_WAIT(2) MSG_H
#elif VERSION_CN
    "尽力在限定时间内取" MSG_NEWLINE
    "得最高分。" MSG_WAIT(2) MSG_H
    "一次消灭多个病毒可" MSG_NEWLINE
    "得高分。" MSG_WAIT(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_WAIT(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_WAIT(2) MSG_H
#endif
    MSG_END;

const char _mesVsNum[] =
#if VERSION_US || VERSION_GW
    "How many players?"
#elif VERSION_CN
    "有多少玩家？"
#endif
    MSG_END;

const char _mesVs4P[] =
#if VERSION_US || VERSION_GW
    "A four-player" MSG_NEWLINE
    "free-for-all." MSG_WAIT(2) MSG_H
    "Force your foes to" MSG_NEWLINE
    "retire by sending" MSG_NEWLINE
    "them garbage" MSG_WAIT(2) MSG_H
    "or destroy all" MSG_NEWLINE
    "of your own" MSG_NEWLINE
    "viruses to win." MSG_WAIT(2) MSG_H
    "The color of the" MSG_NEWLINE
    "combos you clear" MSG_NEWLINE
    "determines where" MSG_NEWLINE
    "your garbage goes." MSG_WAIT(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_WAIT(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_WAIT(2) MSG_H
#elif VERSION_CN
    "四人自由比赛。" MSG_WAIT(2) MSG_H
    "通过送给对手垃圾," MSG_NEWLINE
    "逼迫他们退出游戏" MSG_WAIT(2) MSG_H
    "或消灭自己所有的病" MSG_NEWLINE
    "毒来赢得胜利。 " MSG_WAIT(2) MSG_H
    "连消的颜色决定你的" MSG_NEWLINE
    "垃圾药丸送到哪里去。" MSG_WAIT(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_WAIT(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_WAIT(2) MSG_H
#endif
    MSG_END;

const char _mes4PTag[] =
#if VERSION_US || VERSION_GW
    "A two-on-two" MSG_NEWLINE
    "battle mode." MSG_WAIT(2) MSG_H
    "Force your foes to" MSG_NEWLINE
    "retire by sending" MSG_NEWLINE
    "them garbage" MSG_WAIT(2) MSG_H
    "or destroy all" MSG_NEWLINE
    "of your own" MSG_NEWLINE
    "viruses to win." MSG_WAIT(2) MSG_H
    "The color of the" MSG_NEWLINE
    "combos you clear" MSG_NEWLINE
    "determines where" MSG_NEWLINE
    "your garbage goes." MSG_WAIT(2) MSG_H
    "Garbage sent to" MSG_NEWLINE
    "your partner is" MSG_NEWLINE
    "placed in your" MSG_WAIT(2) MSG_H
    "team bank. This" MSG_NEWLINE
    "is then added" MSG_NEWLINE
    "to later garbage" MSG_WAIT(2) MSG_H
    "that either you or" MSG_NEWLINE
    "your teammate sends" MSG_NEWLINE
    "to your foes." MSG_WAIT(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_WAIT(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_WAIT(2) MSG_H
#elif VERSION_CN
    "二对二模式。" MSG_WAIT(2) MSG_H
    "通过送给对手垃圾, " MSG_NEWLINE
    "逼迫他们退出游戏，" MSG_WAIT(2) MSG_H
    "或消灭自己所有的病" MSG_NEWLINE
    "毒来赢得胜利。 " MSG_WAIT(2) MSG_H
    "连消的颜色决定你的" MSG_NEWLINE
    "垃圾药丸送到哪里去。" MSG_WAIT(2) MSG_H
    "送给同伴的垃圾药丸" MSG_NEWLINE
    "放置在你们" MSG_WAIT(2) MSG_H
    "小型垃圾箱中，然后" MSG_NEWLINE
    "又加入到" MSG_WAIT(2) MSG_H
    "你或你的同伴随后送" MSG_NEWLINE
    "给对手的垃圾中去。" MSG_WAIT(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_WAIT(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_WAIT(2) MSG_H
#endif
    MSG_END;

const char _mes4PFlash[] =
#if VERSION_US || VERSION_GW
    "Clear levels" MSG_NEWLINE
    "by destroying the" MSG_NEWLINE
    "flashing viruses." MSG_WAIT(2) MSG_H
    "You can fill your" MSG_NEWLINE
    "rivals' screens" MSG_NEWLINE
    "with garbage." MSG_WAIT(2) MSG_H
    "The color of the" MSG_NEWLINE
    "combos you clear" MSG_NEWLINE
    "determines where" MSG_NEWLINE
    "your garbage goes." MSG_WAIT(2) MSG_H
    "One more thing!" MSG_NEWLINE
    "Press any C Button" MSG_NEWLINE
    "during game play" MSG_NEWLINE
    "to see where the" MSG_WAIT(2) MSG_H
    "capsule will land." MSG_NEWLINE
    "Press the button" MSG_NEWLINE
    "again to turn the" MSG_NEWLINE
    "effect OFF." MSG_WAIT(2) MSG_H
#elif VERSION_CN
    "消灭所有的闪光病毒" MSG_NEWLINE
    "以取胜。" MSG_WAIT(2) MSG_H
    "你可以将对手的屏幕" MSG_NEWLINE
    "塞满垃圾。" MSG_WAIT(2) MSG_H
    "连消的颜色决定你的" MSG_NEWLINE
    "垃圾药丸送到哪里去。" MSG_WAIT(2) MSG_H
    "再补充一点！" MSG_NEWLINE
    "游戏中可以按任意" MSG_NEWLINE
    "一个Ｃ键来观察药丸" MSG_NEWLINE
    "落下的位置，" MSG_WAIT(2) MSG_H
    "再按一次可以取消这" MSG_NEWLINE
    "个效果。" MSG_WAIT(2) MSG_H
#endif
    MSG_END;

const char _mesRec[] =
#if VERSION_US || VERSION_GW
    "This is where" MSG_NEWLINE
    "you view" MSG_NEWLINE
    "game records."
#elif VERSION_CN
    "在这里可以看游戏纪" MSG_NEWLINE
    "录。"
#endif
    MSG_END;

const char _mesTutol[] =
#if VERSION_US || VERSION_GW
    "This is where" MSG_NEWLINE
    "you study rules" MSG_NEWLINE
    "and techniques."
#elif VERSION_CN
    "在这里可以学习游戏" MSG_NEWLINE
    "规则和技巧。"
#endif
    MSG_END;

const char _mesName[] =
#if VERSION_US || VERSION_GW
    "This is where" MSG_NEWLINE
    "you change or" MSG_NEWLINE
    "delete your name."
#elif VERSION_CN
    "在这里可以更改或删" MSG_NEWLINE
    "除你的名字。"
#endif
    MSG_END;

const char _mesVsCnt[] =
#if VERSION_US || VERSION_GW
    "This is where you" MSG_NEWLINE
    "set the number of" MSG_NEWLINE
    "games in a match."
#elif VERSION_CN
    "在这里可以设置一盘" MSG_NEWLINE
    "比赛的局数。"
#endif
    MSG_END;

const char _mesSnd[] =
#if VERSION_US || VERSION_GW
    "This is where you" MSG_NEWLINE
    "select the" MSG_NEWLINE
    "sound settings." MSG_WAIT(2) MSG_H
    "You can also" MSG_NEWLINE
    "listen to game" MSG_NEWLINE
    "music and sounds." MSG_WAIT(2) MSG_H
#elif VERSION_CN
    "在这里可以进行声音" MSG_NEWLINE
    "设置。" MSG_WAIT(2) MSG_H
    "你也可以欣赏游戏音" MSG_NEWLINE
    "乐和音效。" MSG_WAIT(2) MSG_H
#endif
    MSG_END;

const char _mesBak[] =
#if VERSION_US || VERSION_GW
    "This is where" MSG_NEWLINE
    "you can delete" MSG_NEWLINE
    "all saved data."
#elif VERSION_CN
    "在这里可以删除所有" MSG_NEWLINE
    "存档。"
#endif
    MSG_END;

const char _mesMisc[] =
#if VERSION_US || VERSION_GW
    "This is where you" MSG_NEWLINE
    "can set up other" MSG_NEWLINE
    "game items."
#elif VERSION_CN
    "在这里可以设置其他" MSG_NEWLINE
    "游戏项目。"
#endif
    MSG_END;

const char _mesRecMs1[] =
#if VERSION_US || VERSION_GW
    "Which records do" MSG_NEWLINE
    "you want to view?"
#elif VERSION_CN
    "你想看哪一条纪录？"
#endif
    MSG_END;

const char _mesRecMs2[] =
#if VERSION_US || VERSION_GW
    "Which mode" MSG_NEWLINE
    "records do you" MSG_NEWLINE
    "want to view?"
#elif VERSION_CN
    "你想看哪个模式的" MSG_NEWLINE
    "纪录？"
#endif
    MSG_END;

const char _mesRule1[] =
#if VERSION_US || VERSION_GW
    "These are the" MSG_NEWLINE
    "button control" MSG_NEWLINE
    "explanations."
#elif VERSION_CN
    "这些是控制键的" MSG_NEWLINE
    "讲解。"
#endif
    MSG_END;

const char _mesRule2[] =
#if VERSION_US || VERSION_GW
    "This is an" MSG_NEWLINE
    "explanation of" MSG_NEWLINE
    "basic game play."
#elif VERSION_CN
    "这是游戏的基本" MSG_NEWLINE
    "讲解。"
#endif
    MSG_END;

const char _mesRule3[] =
#if VERSION_US || VERSION_GW
    "These are" MSG_NEWLINE
    "explanations of" MSG_NEWLINE
    "the two-player" MSG_NEWLINE
    "games."
#elif VERSION_CN
    "这些是双人游戏的" MSG_NEWLINE
    "讲解。"
#endif
    MSG_END;

const char _mesRule4[] =
#if VERSION_US || VERSION_GW
    "These are" MSG_NEWLINE
    "explanations of" MSG_NEWLINE
    "the four-player" MSG_NEWLINE
    "games."
#elif VERSION_CN
    "这些是四人游戏的" MSG_NEWLINE
    "讲解。"
#endif
    MSG_END;

const char _mesKotu[] =
#if VERSION_US || VERSION_GW
    "Let me give" MSG_NEWLINE
    "you some advice."
#elif VERSION_CN
    "让我来给你一些" MSG_NEWLINE
    "提示。"
#endif
    MSG_END;

const char _mesNameSel[] =
#if VERSION_US || VERSION_GW
    "What are you" MSG_NEWLINE
    "going to do to" MSG_NEWLINE
    "that file name?"
#elif VERSION_CN
    "你想对那个名字进行" MSG_NEWLINE
    "什么操作？"
#endif
    MSG_END;

const char _mesNameErase[] =
#if VERSION_US || VERSION_GW
    "Delete that file" MSG_NEWLINE
    "name, and you" MSG_NEWLINE
    "delete the game" MSG_NEWLINE
    "data, too." MSG_WAIT(2) MSG_H
    "Do you really" MSG_NEWLINE
    "want to delete" MSG_NEWLINE
    "that file name?" MSG_WAIT(2) MSG_H
#elif VERSION_CN
    "如果你删除那个名字，" MSG_NEWLINE
    "那么就把相关的游戏" MSG_NEWLINE
    "数据也一同删掉了。" MSG_WAIT(2) MSG_H
    "你真的想删除这个" MSG_NEWLINE
    "名字?" MSG_WAIT(2) MSG_H
#endif
    MSG_END;

const char _mesNameErase2[] =
#if VERSION_US || VERSION_GW
    "The file name" MSG_NEWLINE
    "and game data" MSG_NEWLINE
    "have been deleted."
#elif VERSION_CN
    "名字和游戏数据删除" MSG_NEWLINE
    "完毕。"
#endif
    MSG_END;

const char _mesVsCnt2[] =
#if VERSION_US || VERSION_GW
    "Select the number" MSG_NEWLINE
    "of games to play" MSG_NEWLINE
    "in a match."
#elif VERSION_CN
    "选择一盘比赛中的" MSG_NEWLINE
    "局数。 "
#endif
    MSG_END;

const char _mesSound[] =
#if VERSION_US || VERSION_GW
    "Select with the" MSG_NEWLINE
    "+ Control Pad" MSG_NEWLINE
    "and confirm with" MSG_NEWLINE
    "the A Button."
#elif VERSION_CN
    "用十字键选择，" MSG_NEWLINE
    "A键确定。"
#endif
    MSG_END;

const char _mesStereo[] =
#if VERSION_US || VERSION_GW
    "The music will" MSG_NEWLINE
    "play in stereo."
#elif VERSION_CN
    "音乐以立体声播放。"
#endif
    MSG_END;

const char _mesMono[] =
#if VERSION_US || VERSION_GW
    "The music will" MSG_NEWLINE
    "play in mono."
#elif VERSION_CN
    "音乐以单声道播放。"
#endif
    MSG_END;

const char _mesDoErase[] =
#if VERSION_US || VERSION_GW
    "Delete all saved" MSG_NEWLINE
    "game data at once." MSG_WAIT(2) MSG_H
    "Do you really" MSG_NEWLINE
    "want to delete" MSG_NEWLINE
    "all of the" MSG_NEWLINE
    "saved game data?" MSG_WAIT(2) MSG_H
#elif VERSION_CN
    "删除所有的游戏数据。" MSG_WAIT(2) MSG_H
    "你真的想删除所有的" MSG_NEWLINE
    "游戏数据吗？" MSG_WAIT(2) MSG_H
#endif
    MSG_END;

const char _mesDoErase1[] =
#if VERSION_US || VERSION_GW
    "All of the" MSG_NEWLINE
    "saved game data" MSG_NEWLINE
    "has been deleted."
#elif VERSION_CN
    "所有存储的游戏数据" MSG_NEWLINE
    "删除完毕。"
#endif
    MSG_END;

const char _mesNoCont2[] =
#if VERSION_US || VERSION_GW
    "Please power off and insert" MSG_NEWLINE
    "more controllers."
#elif VERSION_CN
    "请关闭电源，插入更" MSG_NEWLINE
    "多共游机。"
#endif
    MSG_END;

const char _mesNoCont3[] =
#if VERSION_US || VERSION_GW
    "Please power off and insert" MSG_NEWLINE
    "more controllers."
#elif VERSION_CN
    "请关闭电源，插入更" MSG_NEWLINE
    "多共游机。"
#endif
    MSG_END;

const char _mesNoCont4[] =
#if VERSION_US || VERSION_GW
    "Please power off and insert" MSG_NEWLINE
    "more controllers."
#elif VERSION_CN
    "请关闭电源，插入更" MSG_NEWLINE
    "多共游机。"
#endif
    MSG_END;

const char _mesScore[] =
#if VERSION_US || VERSION_GW
    "You can turn the" MSG_NEWLINE
    "on-screen score" MSG_NEWLINE
    "display ON or OFF."
#elif VERSION_CN
    "你可以打开或关闭屏" MSG_NEWLINE
    "幕上的得分显示。"
#endif
    MSG_END;

const char _mesScoreOnOff[] =
#if VERSION_US || VERSION_GW
    "Please choose a" MSG_NEWLINE
    "score display" MSG_NEWLINE
    "option."
#elif VERSION_CN
    "请选择得分显示模式。"
#endif
    MSG_END;

/**
 * Original name: _mesWriting
 */
const char _mesWriting_mainmenu[] =
#if VERSION_US || VERSION_GW
    "Now saving." MSG_NEWLINE
    "Do not turn power off."
#elif VERSION_CN
    "存储中" MSG_NEWLINE
    "请勿关闭电源."
#endif
    MSG_END;

/**
 * Original name: _mesDeleting
 */
const char _mesDeleting_mainmenu[] =
#if VERSION_US || VERSION_GW
    "Now deleting." MSG_NEWLINE
    "Do not turn power off."
#elif VERSION_CN
    "删除中" MSG_NEWLINE
    "请勿关闭电源."
#endif
    MSG_END;
