#ifndef DM_TITLE_MAIN_H
#define DM_TITLE_MAIN_H

#include "libultra.h"
#include "main.h"

struct NNSched;

void func_80075F30(void);
enum_main_no dm_title_main(struct NNSched *sc);
void dm_title_graphic(void);
enum_main_no main_boot_error(struct NNSched *sc);
void graphic_boot_error(void);

#endif
