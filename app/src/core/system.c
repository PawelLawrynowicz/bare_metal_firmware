#include "system.h"

#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/stm32/rcc.h>

static volatile uint64_t ticks = 0;

void sys_tick_handler(void) {
  ticks++;
}

uint64_t system_get_ticks(void) {
  return ticks;
}

static void rcc_setup(void) {
  rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_HSI_64MHZ]);
}

static void systick_setup(void) {
  systick_set_frequency(SYSTIC_FREQ, CPU_FREQ);
  systick_counter_enable();
  systick_interrupt_enable();
}

void system_setup(void) {
  systick_setup();
  rcc_setup();
}