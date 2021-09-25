#ifndef ARCH_H__
#define ARCH_H__

#define Interrupt              0x8000000000000000
#define InterruptTimer         (Interrupt | 7)
#define TrapUserEnvCall        8
#define TrapSupervisorEnvCall  9
#define TrapMachineEnvCall     11
// #define Exception
// #define Exception
// #define Exception
// #define Exception

struct Context {
  // TODO: fix the order of these members to match trap.S
  uintptr_t gpr[32], cause, status, epc;
};


#define GPR1 gpr[17]  // a7 x17 : syscall code 
#define GPR2 gpr[10]  // a0 x10 : first arg
#define GPR3 gpr[11]  // a1 x11
#define GPR4 gpr[12]  // a2 x12
#define GPRx gpr[10]  // a0 x10 : return value
// todo riscv use a0, a1 reg to return syscall result

#endif

