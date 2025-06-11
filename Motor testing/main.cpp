#include "Thread.h"
#include "mbed.h"

// Motor A control
DigitalOut motorA_in1(D4);
DigitalOut motorA_in2(D2);
PwmOut motorA_pwm(D3); // EN1

// Motor B control
DigitalOut motorB_in3(D8);
DigitalOut motorB_in4(D7);
PwmOut motorB_pwm(D6); // EN2

void stop() {
    while(true) {
        ThisThread::sleep_for(150ms);

        // Stop both motors
        motorA_in1 = 0;
        motorA_in2 = 0;
        motorA_pwm.write(0.0f);

        motorB_in3 = 0;
        motorB_in4 = 0;
        motorB_pwm.write(0.0f);

        ThisThread::sleep_for(100ms);
    }
}

void mad() {
     // Set PWM period                                                                                                     
    motorA_pwm.period_ms(10);  // 100 Hz
    motorB_pwm.period_ms(10);

    // Set speed
    motorA_pwm.write(1.0f);  // 60% speed
    motorB_pwm.write(1.0f);  // 80% speed

    
    motorA_in1 = 0;
    motorA_in2 = 1;

    motorB_in3 = 0;
    motorB_in4 = 1;

    stop();
}

void happy() {
    motorA_pwm.period_ms(10);  // 100 Hz
    motorB_pwm.period_ms(10);

    while (true) {
        // Turn Left: Left motor backward, right motor forward
        motorA_in1 = 0;  // Left motor reverse
        motorA_in2 = 1;
        motorB_in3 = 1;  // Right motor forward
        motorB_in4 = 0;

        motorA_pwm.write(0.2f);
        motorB_pwm.write(0.2f);
        ThisThread::sleep_for(500ms);

        // Turn Right: Left motor forward, right motor backward
        motorA_in1 = 1;  // Left motor forward
        motorA_in2 = 0;
        motorB_in3 = 0;  // Right motor reverse
        motorB_in4 = 1;

        motorA_pwm.write(0.3f);
        motorB_pwm.write(0.3f);
        ThisThread::sleep_for(500ms);
    }
}



void sad() {
    // Set PWM period                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  1                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
        motorA_pwm.period_ms(10);  // 100 Hz
        motorB_pwm.period_ms(10);

        motorA_pwm.write(0.28f);
        motorB_pwm.write(0.28f);
        
        motorA_in1 = 1;
        motorA_in2 = 0;

        motorB_in3 = 0;
        motorB_in4 = 1;

        motorA_in1 = !motorA_in1;
        motorA_in2 = !motorA_in2;
        motorB_in3 = !motorB_in3;
        motorB_in4 = !motorB_in4;

        while(true) {
            ThisThread::sleep_for(2s);

            // Stop both motors
            motorA_in1 = 0;
            motorA_in2 = 0;
            motorA_pwm.write(0.0f);

            motorB_in3 = 0;
            motorB_in4 = 0;
            motorB_pwm.write(0.0f);

            ThisThread::sleep_for(100ms);
        }
}

int main() {
    happy();
}
