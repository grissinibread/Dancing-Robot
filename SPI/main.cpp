/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "NHD_0216HZ.h"

int main() {
    init_spi();
    init_lcd();

    print_lcd("Hello,"); // First line

    set_cursor(0, 1);           // Move cursor to column 0, row 1
    print_lcd("World!"); // Second line

    while(true) {
        
    }
}