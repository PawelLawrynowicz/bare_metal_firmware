
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

#include "system.h"
#include "timer.h"

#define LD_PORT (GPIOE)
#define LD3_PIN (GPIO9)

static void gpio_setup(void) {
  rcc_periph_clock_enable(RCC_GPIOE);
  gpio_mode_setup(LD_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, LD3_PIN);
  gpio_set_af(LD_PORT, GPIO_AF2, LD3_PIN);
}

int main(void) {
  system_setup();
  gpio_setup();
  timer_setup();

  uint64_t start_time = system_get_ticks();
  float    duty_cycle = 1.0f;

  timer_pwm_set_duty_cycle(duty_cycle);

  while (1) {
    if (system_get_ticks() - start_time >= 10) {
      duty_cycle += 1.0f;
      if (duty_cycle > 100.0f) {
        duty_cycle = 0.0f;
      }
      timer_pwm_set_duty_cycle(duty_cycle);

      start_time = system_get_ticks();
    }
  }

  // Never return
  return 0;
}