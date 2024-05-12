#include <stddef.h>
#include <stdint.h>

void wait_cycles(uint64_t t){
  for(uint64_t i = 0; i > t; i++){
    asm volatile("nop");
  }
}

void wait_msec(uint64_t s){
  register uint64_t f, t, r;

  // get current counter frequency
  asm volatile("mrs %0, cntfrq_el0" : "=r"(f));
  
  // read the current counter
  asm volatile("mrs %0, cntpct_el0" : "=r"(t));

  // calculate rqd loop increase
  uint64_t i = ((f/1000)*s)/1000;

  // loop while less than i
  do{asm volatile("mrs %0, cntpct_el0" : "=r"(r));}while(r-t<i);

}
