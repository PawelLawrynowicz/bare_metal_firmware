#include "core/timer.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

void timer_setup(void) {
  rcc_periph_clock_enable(RCC_TIM3);

  // High level timer configuration
  timer_set_mode(TIM3, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

  // Setup PWM mode
  timer_set_oc_mode(TIM3, TIM_OC1, TIM_OCM_PWM1);

  // Enable PWM out
  timer_enable_counter(TIM3);
  timer_enable_oc_output(TIM2, TIM_OC1);

  // target_freq = system_freq / (prescaled + arr)
  timer_set_prescaler();
}

void timer_pwm_set_duty_cycle(float duty_cycle);