/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "PinNames.h"
#include "Serial.h"
#include "mbed.h"
#include "platform/mbed_thread.h"

Serial serial(D1, D0);

void clearScreen() {
    // Clears the screen
    serial.printf("\033[2J");
    // Homes the cursor
    serial.printf("\033[H");
}

int main()
{
    clearScreen();

    serial.printf("Cube VolumeCalculator\n");
    serial.printf("Enter side dimension:\n");

    int side;
    int volume;
    char buffer[10];

    int index = 0;
    char c;

    while (true) {
        c = serial.getc();
        if(c) {
            if(c == '\r' || c == '\n') {
                buffer[index] = '\0';
                break;
            } else if (index < sizeof(buffer) - 1) {
                buffer[index++] = c;
                serial.putc(c);
            }
        }
    }

    side = atoi(buffer);

    // Calculate the volume
    volume = side * side * side;

    // Displaying the volume
    serial.printf("\nVolume of cube with side %d is: %d\n", side, volume);
}
