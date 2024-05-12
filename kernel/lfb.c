#include <stddef.h>
#include <stdint.h>

#include "mmio.h"
#include "mbox.h"
#include "delay.h"
#include "homer.h"
#include "uart1.h"

uint32_t width, height, pitch, chanodr;
uint8_t *lfb;

typedef struct {
    unsigned int magic;
    unsigned int version;
    unsigned int headersize;
    unsigned int flags;
    unsigned int numglyph;
    unsigned int bytesperglyph;
    unsigned int height;
    unsigned int width;
    unsigned char glyphs;
} __attribute__((packed)) psf_t;

extern volatile uint8_t _binary_kernel_font_psf_start;

void lfb_init(){
  wait_msec(100000); // QEMU compat

  mbox[0] = 35*4;
  mbox[1] = MBOX_REQUEST;

  mbox[2] = 0X48003; // set phy wh
  mbox[3] = 8;
  mbox[4] = 8;
  mbox[5] = 1024; // FrameBufferInfo.width
  mbox[6] = 768; // FrameBufferInfo.height
 
  mbox[7] = 0x48004; // set virtual wh
  mbox[8] = 8;
  mbox[9] = 8;
  mbox[10] = 1024; // FrameBufferInfo.virtual_width
  mbox[11] = 768; // FrameBufferInfo.virtual_height

  mbox[12] = 0x48009; // set virtual offset
  mbox[13] = 8;
  mbox[14] = 8;
  mbox[15] = 0;
  mbox[16] = 0;

  mbox[17] = 0x48005;
  mbox[18] = 4;
  mbox[19] = 4;
  mbox[20] = 32; // FrameBufferInfo.depth

  mbox[21] = 0x48006; // set pixel order
  mbox[22] = 4;
  mbox[23] = 4;
  mbox[24] = 1; // RGB, not BGR preferrably

  mbox[25] = 0x40001; // get framebuffer, get alignment on request
  mbox[26] = 8;
  mbox[27] = 8;
  mbox[28] = 4096; // FrameBufferInfo.pointer
  mbox[29] = 0;

  mbox[30] = 0x40008; // get pitch
  mbox[31] = 4;
  mbox[32] = 4;
  mbox[33] = 0; // FrameBufferInfo.pitcjh

  mbox[34] = MBOX_TAG_LAST;

  if(mbox_call(MBOX_CH_PROP) && mbox[20] == 32 && mbox[28] != 0) {
    mbox[28] &= 0x3FFFFFFF; // convert GPU address to ARM address
    width=mbox[5];
    height=mbox[6];
    pitch=mbox[33];
    chanodr=mbox[24];
    lfb = (void*)(uint64_t)mbox[28];
  } else {
    uart1_puts("failed to init fb");
  }
}

void lfb_print(int32_t x, int32_t y, char *s){
  psf_t *font = (psf_t*) &_binary_kernel_font_psf_start;

  while (*s){
    uint8_t *glyph = (uint8_t*)&_binary_kernel_font_psf_start + font->headersize + (*((uint8_t*)s)<font->numglyph?*s:0);
    int32_t offs = (y * pitch) + (x * 4);
    int32_t i, j, line, mask, bytesperline = (font->width+7)/8;

    if (*s == '\r'){
      x = 0;
    } else if (*s == '\n'){
        x = 0;
        y += font->height;
    } else {
      for(j=0; j<font->height; j++){
        line = offs;
        mask=1<<(font->width-1);
        for(i=0;i<font->width;i++){
          // if bit set, we use white color, otherwise black
          *((unsigned int*)(lfb + line))=((int)*glyph) & mask?0xFFFFFF:0;
          mask>>=1;
          line+=4;
        }
        // adjust to next line
        glyph+=bytesperline;
        offs+=pitch;
      }
      x+= (font->width+1);
      
    }
  }
  s++;
}

void lfb_displogo(){
  int32_t x, y;
  uint8_t *ptr = lfb;
  char *data = homer_data, pixel[4];

  ptr += (height - homer_height) / 2 * pitch + (width - homer_width);
  for (y = 0; y < homer_height; y++){
    for(x = 0; x < homer_width; x++){
      HEADER_PIXEL(data, pixel);
      // image is in RGB, but fb may not be
      // if its BGR, we will need to switch R (pixel[0]) and B (pixel[2]) channels
      *((uint32_t *) ptr) = chanodr ? *((uint32_t*) pixel) : (unsigned int)(pixel[0]<<16 | pixel[1]<<8 | pixel[2]);
      ptr += 4;
    }
    ptr += pitch-homer_width*4;
  }
}
