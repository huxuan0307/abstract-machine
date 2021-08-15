#include <am.h>
#include <mycpu.h>
#include <stdio.h>

extern char _heap_start;
int main(const char *args);

Area heap = RANGE(&_heap_start, PMEM_END);
#ifndef MAINARGS
#define MAINARGS ""
#endif
static const char mainargs[] = MAINARGS;

void putch(char ch) {
  outb(SERIAL_PORT, ch);
}

void halt(int code) {
  nemu_trap(code);
  const char* halt_str="halt ";
  int i=0;
  for(;i<sizeof(halt_str)-1;i++) {
    putch(halt_str[i]);
  }
  if (code) {
    putch('1');
  }
  else {
    putch('0');
  }
  putch('\n');
  // should not reach here
  while (1);
}

void _trm_init() {
  int ret = main(mainargs);
  nemu_trap(ret);
}
