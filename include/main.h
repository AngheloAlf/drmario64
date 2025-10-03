#ifndef MAIN_H
#define MAIN_H

#include "libultra.h"

struct NNSched;

typedef enum enum_main_no {
    /*  0 */ MAIN_11,
    /*  1 */ MAIN_12,
    /*  2 */ MAIN_STORY,
    /*  3 */ MAIN_TITLE,
    /*  4 */ MAIN_MANUAL,
    /*  5 */ MAIN_GAME,
    /*  6 */ MAIN_MENU,
    /*  7 */ MAIN_TECHMES,
    /*  8 */ MAIN_CONT_ERROR, // "no controller connected"
    /*  9 */ MAIN_TV_ERROR, // "game not designed for this system"
    /* 10 */ MAIN_CSUM_ERROR, // "backup file is damaged"
} enum_main_no;


void mainproc(void *arg);

// COMMON

extern struct NNSched B_800EB670;
extern enum_main_no main_no;
extern enum_main_no main_old;


#endif
