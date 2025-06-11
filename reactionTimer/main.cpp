/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "DigitalIn.h"
#include "DigitalOut.h"
#include "PinNames.h"
#include "ThisThread.h"
#include "Timer.h"
#include "mbed.h"
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <string>


using namespace ThisThread;

// Configure User LED
DigitalOut LED(LED1);

// Configure User Button as Input
DigitalIn Button(PC_13);

Timer t;


int main() {
    printf("Press the button as soon as you see the light...\n");
    srand(time(NULL));

    while(true) {
        // reset the timer
        t.reset();

        // generate a random number from 1 to 10
        int r = rand() % 10 + 1;

        // wait for that many seconds
        sleep_for(chrono::seconds(r));

        // turn the LED on / start the timer
        LED = 1;
        t.start();

        // Wait for button press (with debouncing)
        while (Button) {
            sleep_for(10ms); // Debounce fix
        }

        t.stop(); // Stop timer

        // Get reaction time in seconds
        int time = t.read();
        printf("Reaction time: %d seconds\n", time);
    }
}