#include "encoding.h"
#ifndef MYCPU_H__
#define MYCPU_H__


#include <klib-macros.h>

#include ISA_H

#if defined(__ISA_X86__)
# define nemu_trap(code) asm volatile (".byte 0xd6" : :"a"(code))
#elif defined(__ISA_MIPS32__)
# define nemu_trap(code) asm volatile ("move $v0, %0; .word 0xf0000000" : :"r"(code))
#elif defined(__ISA_RISCV32__) || defined(__ISA_RISCV64__)
# define nemu_trap(code) asm volatile("mv a0, %0; .word 0x0000006b" : :"r"(code))
#elif
# error unsupported ISA __ISA__
#endif

# define SERIAL_PORT  0x100003f8
// # define SERIAL_PORT  0xa10003f8
# define KBD_ADDR     0xa1000060
# define RTC_ADDR     0xa1000048
# define VGACTL_ADDR  0xa1000100
# define AUDIO_ADDR   0xa1000200
# define FB_ADDR         0xa0000000
# define AUDIO_SBUF_ADDR 0xa0800000

extern char _pmem_start;
#define PMEM_SIZE (128 * 1024 * 1024)
#define PMEM_END  ((uintptr_t)&_pmem_start + PMEM_SIZE)

extern uint64_t get_time_us();

#define read_csr(reg) ({ unsigned long __tmp; \
  asm volatile ("csrr %0, " #reg : "=r"(__tmp)); \
  __tmp; })

#define write_csr(reg, val) ({ \
  asm volatile ("csrw " #reg ", %0" :: "rK"(val)); })

#define swap_csr(reg, val) ({ unsigned long __tmp; \
  asm volatile ("csrrw %0, " #reg ", %1" : "=r"(__tmp) : "rK"(val)); \
  __tmp; })

#define set_csr(reg, bit) ({ unsigned long __tmp; \
  asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); \
  __tmp; })

#define clear_csr(reg, bit) ({ unsigned long __tmp; \
  asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); \
  __tmp; })

#endif