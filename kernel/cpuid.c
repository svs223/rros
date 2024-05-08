#include <linux/compiler.h>
#include <stddef.h>
#include <stdint.h>

#define SOC_OTHER -1
#define SOCPN_RPI01 0xB76
#define SOCPN_RPI2 0xC07
#define SOCPN_RPI3 0xD03
#define SOCPN_RPI4 0xD08

struct binfo {
  int32_t partnum;
  int8_t boardver;
 // uint32_t mmio_base;
};

struct binfo get_binfo(){
struct binfo b;

#ifdef __AARCH64__
  asm volatile ("mrs %x0, midr_el1" : "=r" (b.partnum));
#else
  asm volatile ("mrc p15,0,%0,c0,c0,0" : "=r" (b.partnum));
#endif

  switch(b.partnum){
    case SOCPN_RPI01:
      b.boardver = 1;
      break;
    case SOCPN_RPI2:
      b.boardver = 2;
      break;
    case SOCPN_RPI3:
      b.boardver = 3;
      break;
    case SOCPN_RPI4:
      b.boardver = 4;
      break;
    default:
      b.boardver = SOC_OTHER;
      break;
  }
  
  return b;
}
