#include <stddef.h>
#include <stdint.h>



size_t strlen(char* s){
  uint64_t off = 0;
  while(s[off] != '\0') off++;
  return off;
}

