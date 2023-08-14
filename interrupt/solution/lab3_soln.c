/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int counter = 0;

bool timer_callback(repeating_timer_t *rt) {
    gpio_put(3, (gpio_get(3) == 0) ? 1 : 0);
    return true; // keep repeating
}

void toggle() {
    counter++;
    if (counter == 20) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, !(cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN)));
        printf("counter: %d\n", counter);
        counter = 0;
    } else {
        printf("counter: %d\n", counter);
    }

}

int main() {
    stdio_init_all();
    // The LED pin for the pico_w board is mapped to the wifi Radio rather than the RP2040. As such, manipulating the LED requires the use
    // of the cyw43_arch library rather than the standard library.
    // https://github.com/raspberrypi/pico-examples/blob/master/pico_w/wifi/blink/picow_blink.c
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    // Setup GP3 as an output, generating a square wave (50% duty cycle) with a period of 2000ms.
    // Initialise and set GP3 as output
    gpio_init(3);
    gpio_set_dir(3, true);
    // Toggles GP3 every 100ms
    repeating_timer_t timer;
    // Negative timeout means exact delay (rather than delay between callbacks)
    if (!add_repeating_timer_ms(-100, timer_callback, NULL, &timer)) {
        printf("Failed to add timer\n");
        return 1;
    }

    // TODO
    // Use an event based interrupt to toggle the LED.
    // Increment a variable on each interrupt and toggle the LED when counter is 20 (i.e. wheel makes an full revolution)
    // Reset the counter when LED is toggled.
    // Print out the counter value to serial on each interrupt.
    gpio_set_irq_enabled_with_callback(2, GPIO_IRQ_EDGE_RISE, true, &toggle);

    while (true) {
    }
}