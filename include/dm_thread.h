#ifndef DM_THREAD_H
#define DM_THREAD_H

typedef enum ThreadId {
    /*  1 */ THREAD_ID_IDLE_BOOT = 1,
    /*  3 */ THREAD_ID_MAIN = 3,
    /*  5 */ THREAD_ID_GRAPHIC = 5,
    /*  6 */ THREAD_ID_6,
    /* 17 */ THREAD_ID_17 = 17,
    /* 18 */ THREAD_ID_18,
    /* 19 */ THREAD_ID_19,
} ThreadId;

// TODO: osSetThreadPri cleanup
typedef enum ThreadPriority {
    /*   1 */ THREAD_PRI_IDLE_BOOT = 1,
    /*   2 */ THREAD_PRI_6,
    /*  10 */ THREAD_PRI_MAIN = 10,
    /*  15 */ THREAD_PRI_GRAPHIC = 15,
    /* 100 */ THREAD_PRI_NN_SC_GRAPHICS = 100, /* Original name: NN_SC_GRAPHICS_PRI */
    /* 110 */ THREAD_PRI_NN_SC_AUDIO = 110, /* Original name: NN_SC_AUDIO_PRI */
    /* 120 */ THREAD_PRI_NN_SC_EVENT = 120, /* Original name: NN_SC_PRI */
} ThreadPriority;


#endif
