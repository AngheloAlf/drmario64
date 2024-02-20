const char mes_1_1[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Hello, everyone!" MSG_NEWLINE
    "I'm Paragoom."
#endif
#if VERSION_CN
    "大家好！" MSG_NEWLINE
    "我是帕拉贡。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_1_2[] = MSG_COLOR(WHITE)
#if VERSION_US
    "I'm here to tell" MSG_NEWLINE
    "you how to play" MSG_NEWLINE
    "Dr. Mario. Please" MSG_NEWLINE
    "pay attention."
#endif
#if VERSION_CN
    "我在这里告诉你" MSG_NEWLINE
    "如何玩马力欧医" MSG_NEWLINE
    "生。" MSG_NEWLINE
    "请注意! "
#endif
    MSG_WAIT(2) MSG_END;

const char mes_1_3[] = MSG_COLOR(WHITE)
#if VERSION_US
    "It's all about" MSG_NEWLINE
    "vitamins! Toss 'em" MSG_NEWLINE
    "into the bottle to" MSG_NEWLINE
    "destroy viruses."
#endif
#if VERSION_CN
    "这个游戏是把维" MSG_NEWLINE
    "生素药丸扔进瓶" MSG_NEWLINE
    "子消灭病毒。" MSG_WAIT(2)
    MSG_END
    "这个游戏是把维" MSG_NEWLINE
    "生素药丸扔进瓶" MSG_NEWLINE
    "子消灭病毒。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_1_4[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Press the A and" MSG_NEWLINE
    "B Buttons to" MSG_NEWLINE
    "rotate capsules."
#endif
#if VERSION_CN
    "按Ａ和Ｂ键旋转" MSG_NEWLINE
    "药丸。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_1_5[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Clear vitamins by" MSG_NEWLINE
    "making four or" MSG_NEWLINE
    "more matching" MSG_NEWLINE
    "columns or rows."
#endif
#if VERSION_CN
    "纵向或横向排列" MSG_NEWLINE
    "四个或以上同色" MSG_NEWLINE
    "药丸可以消除它" MSG_NEWLINE
    "们。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_1_6[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Clear a stage by" MSG_NEWLINE
    "destroying all" MSG_NEWLINE
    "of the viruses" MSG_NEWLINE
    "in the bottle."
#endif
#if VERSION_CN
    "消灭瓶中所有病" MSG_NEWLINE
    "毒就可以过关。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_1_7[] = MSG_COLOR(WHITE)
#if VERSION_US
    "If the bottle gets" MSG_NEWLINE
    "filled all the way" MSG_NEWLINE
    "to the top, your" MSG_NEWLINE
    "game will be over."
#endif
#if VERSION_CN
    "如果瓶子装满的" MSG_NEWLINE
    "话，游戏就结束" MSG_NEWLINE
    "了。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_1_8[] = MSG_COLOR(WHITE)
#if VERSION_US
    "That's all" MSG_NEWLINE
    "for now. I'll" MSG_NEWLINE
    "see you later!"
#endif
#if VERSION_CN
    "就先到这里吧，" MSG_NEWLINE
    "等会儿见！"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_2_1[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Now I'll tell" MSG_NEWLINE
    "you about the" MSG_NEWLINE
    "Two-Player Vs." MSG_NEWLINE
    "game rules!"
#endif
#if VERSION_CN
    "现在让我向你介" MSG_NEWLINE
    "绍二人对战的游" MSG_NEWLINE
    "戏规则。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_2_2[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Destroy all the" MSG_NEWLINE
    "viruses faster" MSG_NEWLINE
    "than your rival" MSG_NEWLINE
    "does to win."
#endif
#if VERSION_CN
    "要赢得比赛，就" MSG_NEWLINE
    "要比对手更快地" MSG_NEWLINE
    "消灭病毒。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_2_3[] = MSG_COLOR(WHITE)
#if VERSION_US
    "If your bottle" MSG_NEWLINE
    "fills up all the" MSG_NEWLINE
    "way to the top," MSG_NEWLINE
    "you'll lose."
#endif
#if VERSION_CN
    "如果你的瓶子装" MSG_NEWLINE
    "满到瓶口的话，" MSG_NEWLINE
    "你就输了。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_2_4[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Clear combos" MSG_NEWLINE
    "to send garbage" MSG_NEWLINE
    "to your opponent."
#endif
#if VERSION_CN
    "完成连消可以把" MSG_NEWLINE
    "垃圾送给对手。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_2_5[] = MSG_COLOR(WHITE)
#if VERSION_US
    "The more combos" MSG_NEWLINE
    "you clear, the" MSG_NEWLINE
    "more garbage" MSG_NEWLINE
    "you'll send!"
#endif
#if VERSION_CN
    "连消次数越多," MSG_NEWLINE
    "送出去的垃圾就" MSG_NEWLINE
    "越多！"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_2_6[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Clear two combos" MSG_NEWLINE
    "to send two" MSG_NEWLINE
    "pieces of garbage."
#endif
#if VERSION_CN
    "完成两次连消送" MSG_NEWLINE
    "出两个垃圾。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_2_7[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Clear three combos" MSG_NEWLINE
    "for three pieces," MSG_NEWLINE
    "four combos for" MSG_NEWLINE
    "four pieces."
#endif
#if VERSION_CN
    "完成三次连消送" MSG_NEWLINE
    "出三个垃圾。完" MSG_NEWLINE
    "成四次连消送出" MSG_NEWLINE
    "四个垃圾。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_2_8[] = MSG_COLOR(WHITE)
#if VERSION_US
    "But four pieces" MSG_NEWLINE
    "is the most you" MSG_NEWLINE
    "can send at one" MSG_NEWLINE
    "time."
#endif
#if VERSION_CN
    "一次最多送出四" MSG_NEWLINE
    "个垃圾。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_2_9[] = MSG_COLOR(WHITE)
#if VERSION_US
    "That's all" MSG_NEWLINE
    "for now! I'll" MSG_NEWLINE
    "see you later!"
#endif
#if VERSION_CN
    "就先到这里吧，" MSG_NEWLINE
    "等会儿见！"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_3_1[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Now I'll tell" MSG_NEWLINE
    "you about the" MSG_NEWLINE
    "Four-Player Vs." MSG_NEWLINE
    "game rules!"
#endif
#if VERSION_CN
    "现在让我向你介" MSG_NEWLINE
    "绍四人对战的游" MSG_NEWLINE
    "戏规则。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_3_2[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Destroy all the" MSG_NEWLINE
    "viruses faster" MSG_NEWLINE
    "than your foes" MSG_NEWLINE
    "do to win."
#endif
#if VERSION_CN
    "要赢得比赛，就" MSG_NEWLINE
    "要比对手更快地" MSG_NEWLINE
    "消灭病毒。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_3_3[] = MSG_COLOR(WHITE)
#if VERSION_US
    "If your bottle" MSG_NEWLINE
    "fills up all the" MSG_NEWLINE
    "way to the top," MSG_NEWLINE
    "you'll lose."
#endif
#if VERSION_CN
    "如果你的瓶子装" MSG_NEWLINE
    "满到瓶口的话，" MSG_NEWLINE
    "你就输了。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_3_4[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Clear combos" MSG_NEWLINE
    "to send garbage" MSG_NEWLINE
    "to your foes."
#endif
#if VERSION_CN
    "完成连消可以把" MSG_NEWLINE
    "垃圾送给对手。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_3_5[] = MSG_COLOR(WHITE)
#if VERSION_US
    "The color of the" MSG_NEWLINE
    "combo you clear" MSG_NEWLINE
    "determines where" MSG_NEWLINE
    "your garbage goes."
#endif
#if VERSION_CN
    "连消的颜色决定" MSG_NEWLINE
    "你的垃圾会送到" MSG_NEWLINE
    "哪里去。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_3_6[] = MSG_COLOR(WHITE)
#if VERSION_US
    "If the combo is" MSG_NEWLINE
    "blue, the player" MSG_NEWLINE
    "on your right gets" MSG_NEWLINE
    "your garbage."
#endif
#if VERSION_CN
    "如果是蓝色，在" MSG_NEWLINE
    "你右边的玩家会" MSG_NEWLINE
    "收到垃圾。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_3_7[] = MSG_COLOR(WHITE)
#if VERSION_US
    "If the combo is" MSG_NEWLINE
    "yellow, it goes to" MSG_NEWLINE
    "the second player" MSG_NEWLINE
    "on your right."
#endif
#if VERSION_CN
    "如果是黄色，在" MSG_NEWLINE
    "你右边的第二个" MSG_NEWLINE
    "玩家会收到垃圾。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_3_8[] = MSG_COLOR(WHITE)
#if VERSION_US
    "If the combo is" MSG_NEWLINE
    "red, it goes to" MSG_NEWLINE
    "the third player" MSG_NEWLINE
    "on your right."
#endif
#if VERSION_CN
    "如果是红色，在" MSG_NEWLINE
    "你右边的第三个" MSG_NEWLINE
    "玩家会收到垃圾。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_3_9[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Clear two colors" MSG_NEWLINE
    "at the same time" MSG_NEWLINE
    "to send garbage" MSG_NEWLINE
    "to two players."
#endif
#if VERSION_CN
    "一次消掉两种颜" MSG_NEWLINE
    "色可以让两个玩" MSG_NEWLINE
    "家收到垃圾。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_3_10[] = MSG_COLOR(WHITE)
#if VERSION_US
    "If no one is on" MSG_NEWLINE
    "your right, your" MSG_NEWLINE
    "garbage goes" MSG_NEWLINE
    "to the far left."
#endif
#if VERSION_CN
    "如果在你右边的" MSG_NEWLINE
    "没有人你送出的" MSG_NEWLINE
    "垃圾就到最左边。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_3_11[] = MSG_COLOR(WHITE)
#if VERSION_US
    "When playing" MSG_NEWLINE
    "Team Battle, the" MSG_NEWLINE
    "garbage you send"
#endif
#if VERSION_CN
    "在分组对战模式" MSG_NEWLINE
    "下，你送给同伴" MSG_NEWLINE
    "的垃圾。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_3_12[] = MSG_COLOR(WHITE)
#if VERSION_US
    "to your partner" MSG_NEWLINE
    "goes into" MSG_NEWLINE
    "your bank."
#endif
#if VERSION_CN
    "会送到你们的" MSG_NEWLINE
    "储备箱，"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_3_13[] = MSG_COLOR(WHITE)
#if VERSION_US
    "The garbage in" MSG_NEWLINE
    "your bank is" MSG_NEWLINE
    "automatically" MSG_NEWLINE
    "added to the next"
#endif
#if VERSION_CN
    "储备箱中的垃圾" MSG_NEWLINE
    "会自动加到"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_3_14[] = MSG_COLOR(WHITE)
#if VERSION_US
    "time either you" MSG_NEWLINE
    "or your teammate" MSG_NEWLINE
    "sends garbage to" MSG_NEWLINE
    "your opponents."
#endif
#if VERSION_CN
    "下一次你或你的" MSG_NEWLINE
    "同伴送给对手的" MSG_NEWLINE
    "垃圾中。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_3_15[] = MSG_COLOR(WHITE)
#if VERSION_US
    "That's all" MSG_NEWLINE
    "for now! I'll" MSG_NEWLINE
    "see you later!"
#endif
#if VERSION_CN
    "就先到这里吧，" MSG_NEWLINE
    "等会儿见！"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_4_1[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Now it's time" MSG_NEWLINE
    "for me to give" MSG_NEWLINE
    "you some advice."
#endif
#if VERSION_CN
    "现在我要给你一" MSG_NEWLINE
    "些提示。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_4_2[] = MSG_COLOR(WHITE)
#if VERSION_US
    "At first, it's" MSG_NEWLINE
    "easier to match" MSG_NEWLINE
    "colors in a" MSG_NEWLINE
    "vertical row."
#endif
#if VERSION_CN
    "首先，纵向拼出" MSG_NEWLINE
    "同色药丸更容易。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_4_3[] = MSG_COLOR(WHITE)
#if VERSION_US
    "But when you get" MSG_NEWLINE
    "better, try to" MSG_NEWLINE
    "match colors" MSG_NEWLINE
    "horizontally, too."
#endif
#if VERSION_CN
    "但当你的技巧熟" MSG_NEWLINE
    "练后，尽量也横" MSG_NEWLINE
    "向拼色。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_4_4[] = MSG_COLOR(WHITE)
#if VERSION_US
    "A special melody" MSG_NEWLINE
    "plays when you've" MSG_NEWLINE
    "cleared a combo."
#endif
#if VERSION_CN
    "你完成连消时，" MSG_NEWLINE
    "会播放一段特别" MSG_NEWLINE
    "的旋律。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_4_5[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Don't forget!" MSG_NEWLINE
    "Vitamins begin to" MSG_NEWLINE
    "fall faster with" MSG_NEWLINE
    "every tenth one."
#endif
#if VERSION_CN
    "别忘了！每过十" MSG_NEWLINE
    "个药丸下落的速" MSG_NEWLINE
    "度会加快。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_4_6[] = MSG_COLOR(WHITE)
#if VERSION_US
    "The music speeds" MSG_NEWLINE
    "up when few" MSG_NEWLINE
    "viruses remain."
#endif
#if VERSION_CN
    "当剩下的病毒不" MSG_NEWLINE
    "多时，音乐的速" MSG_NEWLINE
    "度会加快。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_4_7[] = MSG_COLOR(WHITE)
#if VERSION_US
    "When your bottle" MSG_NEWLINE
    "begins to fill" MSG_NEWLINE
    "up, warning music" MSG_NEWLINE
    "will begin."
#endif
#if VERSION_CN
    "当你的瓶子快要" MSG_NEWLINE
    "装满时，会开始" MSG_NEWLINE
    "出现警告音乐。"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_4_8[] = MSG_COLOR(WHITE)
#if VERSION_US
    "Danger!" MSG_NEWLINE
    "You'd better" MSG_NEWLINE
    "hurry up!"
#endif
#if VERSION_CN
    "危险！" MSG_NEWLINE
    "你最好加快速度！"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_4_9[] = MSG_COLOR(WHITE)
#if VERSION_US
    "That's it." MSG_NEWLINE
    "Now get going!"
#endif
#if VERSION_CN
    "我要说的都说了。" MSG_NEWLINE
    "现在开始游戏吧！"
#endif
    MSG_WAIT(2) MSG_END;

const char mes_4_10[] = MSG_COLOR(WHITE)
#if VERSION_US
    "See you later!" MSG_NEWLINE
    "Bye-bye!"
#endif
#if VERSION_CN
    "后会有期！" MSG_NEWLINE
    "再见！"
#endif
    MSG_WAIT(2) MSG_END;
