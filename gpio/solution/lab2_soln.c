/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

bool timer_callback(repeating_timer_t *rt) {
    gpio_put(3, (gpio_get(3) == 0) ? 1 : 0);
    return true; // keep repeating
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

    // Setup GP3 as an output, generating a square wave (50% duty cycle) with a period of 2000ms.
    // Initialise and set GP3 as output
    gpio_init(3);
    gpio_set_dir(3, true);
    // Toggles GP3 every 1000ms
    repeating_timer_t timer;
    // Negative timeout means exact delay (rather than delay between callbacks)
    if (!add_repeating_timer_ms(-1000, timer_callback, NULL, &timer)) {
        printf("Failed to add timer\n");
        return 1;
    }

    // TODO
    // Initialise GP2 as an input and connect a jumper accross GP2 and GP3
    gpio_init(2);
    gpio_set_dir(2, false);
    gpio_pull_down(2);

    while (true) {
        // TODO
        // Continuously Poll GP2 and get LED accordingly.
        if (gpio_get(2) == 0) {
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        } else {
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        }
    }
}