#include <stdint.h>

int8_t get_el(){
  uint64_t el;
  asm volatile("mrs %0, CurrentEL" : "=r"(el));

  if (el == 0b1000){
    return 2;
  }

  if (el <= 0b1000){
    return 1;
  }

  return 3;
}
