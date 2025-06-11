/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "BusOut.h"
#include "InterruptIn.h"
#include "mbed.h"
#include <arm_acle.h>


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

// Define output LEDs
// red, green, yellow
    BusOut lights(PB_10, PA_8, PA_9);

// Define an InterruptIn for each button
    InterruptIn leftButton(PA_10);
    InterruptIn middleButton(PB_3);
    InterruptIn rightButton(PB_5);

 // Define counters to keep track of the number of times each button is pressed
    int leftPresses, 
        middlePresses, 
        rightPresses;

void compareAndUpdate() {
    int maxPresses = max({leftPresses, middlePresses, rightPresses});
    lights[0] = leftPresses == maxPresses;
    lights[1] = middlePresses == maxPresses;
    lights[2] = rightPresses == maxPresses;
}

// update the button counter
void leftButton_ISR() {
    leftPresses++;
    compareAndUpdate();
}

void middleButton_ISR() {
    middlePresses++;
    compareAndUpdate();
}

void rightButton_ISR() {
    rightPresses++;
    compareAndUpdate();
}

int main()
{
    // Turn off all LEDs initially
    for(int i = 0; i < 3; i++)
        lights[i] = 0;

    // Set all counters to 0
    leftPresses = middlePresses = rightPresses = 0;

    // Attach the addresses of the ISRs to the rising edge of their respective buttons
    leftButton.rise(&leftButton_ISR);
    middleButton.rise(&middleButton_ISR);
    rightButton.rise(&rightButton_ISR);

    while (true) {
        // Sleep on exit feature
        __wfi();

        // - - - Testing - - -
        if(!leftButton)
            printf("left pressed %d times\n", leftPresses);
        if(!middleButton)
            printf("middle pressed %d times\n", middlePresses);
        if(!rightButton)
            printf("right pressed %d times\n", rightPresses);
        // - - - Testing - - -
    }
}