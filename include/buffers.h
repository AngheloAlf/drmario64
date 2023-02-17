#ifndef BUFFERS_H
#define BUFFERS_H

#include "libultra.h"
#include "alignment.h"
#include "macros_defines.h"

/**
 * Original name: Heap_bufferp
 */
extern u8 Heap_bufferp[];

extern u8 D_80205000[];

extern u16 gFramebuffers[2][SCREEN_HEIGHT * SCREEN_WIDTH];

void BUFFER_MALLOC(void **dst, void *buff, size_t size);
#define BUFFER_MALLOC(dst, buff, size) \
    (*dst) = ALIGN_PTR((buff)); \
    (buff) = (void *)((uintptr_t)*(dst) + (size))

void BUFFER_MALLOC64(void **dst, void *buff, size_t size);
#define BUFFER_MALLOC64(dst, buff, size) \
    (*dst) = (void *)ALIGN64((uintptr_t)(buff)); \
    (buff) = (void *)((uintptr_t)*(dst) + (size))

void BUFFER_CALLOC(void **dst, void *buff, size_t size);
#define BUFFER_CALLOC(dst, buff, size) \
    (*dst) = ALIGN_PTR((buff)); \
    bzero((*dst), (size)); \
    (buff) = (void *)((uintptr_t)*(dst) + (size))

#endif
