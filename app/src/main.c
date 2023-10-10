
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#include "core/system.h"

#define LD4_PIN  (GPIO8)
#define LD4_PORT (GPIOE)
#define LD5_PIN  (GPIO9)
#define LD5_PORT (GPIOE)

static void gpio_setup(void) {
  rcc_periph_clock_enable(RCC_GPIOE);
  // GPIOE = 0x48000000U + 0x1000
  gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8 | GPIO9);
}

int main(void) {
  system_setup();
  gpio_setup();

  uint64_t start_time = get_ticks();

  while (1) {
    if (get_ticks() - start_time >= 1000) {
      gpio_toggle(LD5_PORT, LD5_PIN);
      gpio_toggle(LD4_PORT, LD4_PIN);
      start_time = get_ticks();
    }
  }

  return 0;
}