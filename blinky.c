/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdatomic.h>
#include "pico/stdlib.h"


#define EXTERNAL_LED (0)

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 250
#endif

// Initialize the GPIO for the LED
void pico_led_init(void) {
#ifdef PICO_DEFAULT_LED_PIN
  // A device like Pico that uses a GPIO for the LED will define
  // PICO_DEFAULT_LED_PIN so we can use normal GPIO functionality to turn the
  // led on and off
  gpio_init(PICO_DEFAULT_LED_PIN);
  gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
#endif
}

// Turn the LED on or off
void pico_set_led(bool led_on) {
#if defined(PICO_DEFAULT_LED_PIN)
  // Just set the GPIO on or off
  gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#endif
}

volatile uint32_t counter = 0;

void external_led_init(){
  gpio_init(EXTERNAL_LED);
  gpio_set_dir(EXTERNAL_LED, GPIO_OUT);
  gpio_put(EXTERNAL_LED,0);
}

// toogle led at GPIO_0 with xor_mask asynchronously
void async_led_toggle(int32_t gpio_pin){

  gpio_xor_mask(1 << gpio_pin);
  printf("Switching\n");

}

static uint32_t get_counter(){
  return counter;
}

bool repeating_timer_callback(__unused struct repeating_timer *t){

  counter++;
  printf("%u\n",counter);
  async_led_toggle(EXTERNAL_LED);
  // gpio_xor_mask(1 << EXTERNAL_LED);

  return true;
}


int main() {
  pico_led_init();
  stdio_init_all();

  external_led_init();

  // tick_start(TICK_WATCHDOG, 1000);

  // uint32_t current = watchdog_get_count();

  struct repeating_timer timer;

  if(add_repeating_timer_ms(-1000,repeating_timer_callback,NULL,&timer)){

    pico_set_led(true);

  }


  // uint32_t current = 0;

  while (true) {

    // flick a gpio pin every
    // printf("Hello there!\n");
    // if ((get_counter() - current) >= 1)
    // {
    //   printf("more than 10\n");
    //   current = get_counter();
    //   //do some task in async manner
    //   async_led_toggle(EXTERNAL_LED);
    // }

    // pico_set_led(true);
    // sleep_ms(LED_DELAY_MS);
    // pico_set_led(false);
    // sleep_ms(LED_DELAY_MS);

  }
}
