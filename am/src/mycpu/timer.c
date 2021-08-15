#include <am.h>

static uint64_t time_us = 0;

void __am_timer_init() {

}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  asm volatile ("csrr %0, mcycle":"=r"(time_us));
  uptime->us = time_us;
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  const int fq = 1000;
  // todo: 
  rtc->second = time_us / fq;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
