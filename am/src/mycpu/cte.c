#include <am.h>
#include <klib.h>

static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context *c) {
  if (user_handler) {
    Event ev = {0};
    // printf("syscall code: %d\n", c->GPR1);
    // printf("mcause:  %x\n", c->cause);
    // printf("mstatus: %x\n", c->status);
    // printf("mepc:    %x\n", c->epc);
    switch (c->cause) {
      case InterruptTimer:
        ev.event = EVENT_IRQ_TIMER;
        break;
      case TrapMachineEnvCall: 
        if (c->GPR1 == -1) {
          ev.event = EVENT_YIELD;
          c -> epc += 4;
        }
        else {
          ev.event = EVENT_SYSCALL;
        }
        break;
      
      default: ev.event = EVENT_ERROR; break;
    }

    c = user_handler(ev, c);

    assert(c != NULL);
  }

  return c;
}

extern void __am_asm_trap(void);

bool cte_init(Context*(*handler)(Event, Context*)) {
  // initialize exception entry
  asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));

  // register event handler
  user_handler = handler;

  return true;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) {
  // Context *c = (Context*)kstack.end - 1;
  return NULL;
}

void yield() {
  asm volatile("li a7, -1; ecall");
}

bool ienabled() {
  return false;
}

void iset(bool enable) {
}
