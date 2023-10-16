#include "timer.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

// 64_000_000
// target_freq = system_freq / ((PRESCALER - 1) * (ARR_VALUE - 1))
#define PRESCALER (64)
#define ARR_VALUE (1000)  // Auto-reload register value

void timer_setup(void) {
  rcc_periph_clock_enable(RCC_TIM1);

  // High level timer configuration
  timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

  // Setup PWM mode
  timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_PWM1);

  // Setup frequency and resolution
  timer_set_prescaler(TIM1, PRESCALER - 1);
  timer_set_period(TIM1, ARR_VALUE - 1);

  // Enable the output compare channell
  timer_enable_oc_output(TIM1, TIM_OC1);
  timer_enable_break_main_output(TIM1);  // For advanced timers like TIM1, enable the main output

  // Enable PWM out
  timer_enable_counter(TIM1);
}

void timer_pwm_set_duty_cycle(float duty_cycle) {
  // duty_cycle = (CCR / ARR) * 100
  // CCR = duty_cycle / 100 * arr

  const float raw_value = (float)ARR_VALUE * (duty_cycle / 100.0f);
  timer_set_oc_value(TIM1, TIM_OC1, (uint32_t)raw_value);
}