#ifndef MBOX_H
#define MBOX_H

#include <stdint.h>

extern volatile uint32_t mbox[36];

int32_t mbox_call(uint8_t);

#endif
