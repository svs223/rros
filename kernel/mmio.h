#ifndef MMIO_H
#define MMIO_H

// channels
#define MBOX_REQUEST  0
#define MBOX_CH_POWER 0
#define MBOX_CH_FB    1
#define MBOX_CH_VUART 2
#define MBOX_CH_VCHIQ 3
#define MBOX_CH_LEDS  4
#define MBOX_CH_BTNS  5
#define MBOX_CH_TOUCH 6
#define MBOX_CH_COUNT 7
#define MBOX_CH_PROP  8

// tags
#define MBOX_TAG_GETSERIAL 0x10004
#define MBOX_TAG_LAST      0

#endif
