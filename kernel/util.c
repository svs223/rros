#include <stddef.h>
#include <stdint.h>

uint32_t strlen(char* s){
  uint32_t len = 0;
  while(s[len] != '\0') len++;
  return len;
}
