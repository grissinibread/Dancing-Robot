#include "ThisThread.h"
#include "mbed.h"
//#include "LEDS.h"
#include <cstdint>

BufferedSerial pc(D1, D0, 9600); //to read user input
SPI spi(PA_7, NC, PA_5); //MOSI(D11), MISO, SCK(D13)
DigitalOut eye(PB_6); //D10
DigitalOut mouth(PB_4); //D5 

// Motor A control
DigitalOut motorA_in1(D4);
DigitalOut motorA_in2(D2);
PwmOut motorA_pwm(D3); // EN1

// Motor B control
DigitalOut motorB_in3(D8);
DigitalOut motorB_in4(D7);
PwmOut motorB_pwm(D6); // EN2

void stop() {
        ThisThread::sleep_for(150ms);
        motorA_in1 = 0;
        motorA_in2 = 0;
        motorA_pwm.write(0.0f);

        motorB_in3 = 0;
        motorB_in4 = 0;
        motorB_pwm.write(0.0f);

        ThisThread::sleep_for(2s);
}

void mad() {
     // Set PWM period
    motorA_pwm.period_ms(10);  // 100 Hz
    motorB_pwm.period_ms(10);

    // Set speed
    motorA_pwm.write(1.0f);
    motorB_pwm.write(1.0f);

    
    motorA_in1 = 0;
    motorA_in2 = 1;

    motorB_in3 = 0;
    motorB_in4 = 1;

    ThisThread::sleep_for(150ms);

    stop();
}

void sad() {
    // Set PWM period            
        motorA_pwm.period_ms(10);  // 100 Hz
        motorB_pwm.period_ms(10);

        motorA_pwm.write(0.4f);
        motorB_pwm.write(0.4f);
        
        motorA_in1 = 0;
        motorA_in2 = 1;

        motorB_in3 = 1;
        motorB_in4 = 0;

        ThisThread::sleep_for(2s);

        stop();
}

void love() {
    motorA_pwm.period_ms(10);  // 100 Hz
    motorB_pwm.period_ms(10);

    for(int i = 0; i < 5; i++) {
        // Turn Left: Left motor backward, right motor forward
        motorA_in1 = 0;  // Left motor reverse
        motorA_in2 = 1;
        motorB_in3 = 1;  // Right motor forward
        motorB_in4 = 0;

        motorA_pwm.write(0.3f);
        motorB_pwm.write(0.3f);
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

    stop();
}

void happy() {
    motorA_pwm.period_ms(10);  // 100 Hz
    motorB_pwm.period_ms(10);

    for(int i = 0; i < 5; i++) {
        // Turn Left: Left motor backward, right motor forward
        motorA_in1 = 0;  // Left motor reverse
        motorA_in2 = 1;
        motorB_in3 = 0;  // Right motor forward
        motorB_in4 = 1;

        motorA_pwm.write(0.2f);
        motorB_pwm.write(0.2f);
        ThisThread::sleep_for(500ms);

        // Turn Right: Left motor forward, right motor backward
        motorA_in1 = 1;  // Left motor forward
        motorA_in2 = 0;
        motorB_in3 = 1;  // Right motor reverse
        motorB_in4 = 0;

        motorA_pwm.write(0.15f);
        motorB_pwm.write(0.15f);
        ThisThread::sleep_for(500ms);
    }

    stop();
}

/*===============================================================
*EYE PATTERNS
================================================================*/
// Heart patterns
const uint8_t heart[8] = {
    0b00110000,
    0b01111000,
    0b01111100,
    0b00111110,
    0b00111110,
    0b01111100,
    0b01111000,
    0b00110000
};

const uint8_t hollowHeart[8] = {
    0b00110000,
    0b01001000,
    0b01000100,
    0b00100010,
    0b00100010,
    0b01000100,
    0b01001000,
    0b00110000
};

//happy/mad eyes
const uint8_t upturnedEyes[8] ={
  //0b12345678
    0b00000000,
    0b00001000,
    0b00010000,
    0b00110000,
    0b00110000,
    0b00010000,
    0b00001000,
    0b00000000,
};

//sad eyes
const uint8_t downturnedEyes[8] = {
  //0b12345678
    0b00000000,
    0b00010000,
    0b00001000,
    0b00001100,
    0b00001100,
    0b00001000,
    0b00010000,
    0b00000000
};

/*===============================================================
*MOUTH PATTERNS
================================================================*/
// lips 
const uint8_t lips[8] = {
    0b00010000,
    0b00111000,
    0b01111100,
    0b00101100,
    0b00101100,
    0b01111100,
    0b00111000,
    0b00010000
};

// smile 
const uint8_t smile[8] = {
  //0b12345678
    0b00100000,
    0b00011000,
    0b00001100,
    0b00001100,
    0b00001100,
    0b00001100,
    0b00011000,
    0b00100000
};

// mad 
const uint8_t madMouth[8] = {
  //0b12345678
    0b00000100,
    0b00011000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00110000,
    0b00011000,
    0b00000100
};

const uint8_t frown[8] = {
  //0b12345678
    0b00001100,
    0b00110000,
    0b00110000,
    0b00011000,
    0b00011000,
    0b00110000,
    0b00110000,
    0b00001100
};

void writeToEyeDisplay(uint8_t reg, uint8_t data) {
    eye = 0;
    spi.write(reg); 
    spi.write(data);
    eye = 1;
}

void writeToMouthDisplay(uint8_t reg, uint8_t data) {
    mouth = 0;
    spi.write(reg);
    spi.write(data);
    mouth = 1;
}

void clearDisplay() {
    for (int i = 1; i <= 8; i++) {
        writeToEyeDisplay(i, 0x00);
        writeToMouthDisplay(i, 0x00);
    }
}

void displayPattern(const uint8_t pattern1[8], const uint8_t pattern2[8]) {
    for (int row = 0; row < 8; row++) {
        writeToEyeDisplay(row + 1, pattern1[row]);
        writeToEyeDisplay(row + 1, pattern1[row]);
        writeToMouthDisplay(row + 1, pattern2[row]);
    }
}

int main() {
    // SPI configuration
    spi.format(8, 0);
    spi.frequency(1000000);

    // MAX7219 initialization
    //for eyes
    writeToEyeDisplay(0x0C, 0x01);  // Normal operation
    writeToEyeDisplay(0x09, 0x00);  // No decode mode
    writeToEyeDisplay(0x0B, 0x07);  // Scan limit: all digits
    writeToEyeDisplay(0x0A, 0x0F);  // Maximum brightness
    writeToEyeDisplay(0x0F, 0x00);  // Display test off
    //for mouth
    writeToMouthDisplay(0x0C, 0x01);  // Normal operation
    writeToMouthDisplay(0x09, 0x00);  // No decode mode
    writeToMouthDisplay(0x0B, 0x07);  // Scan limit: all digits
    writeToMouthDisplay(0x0A, 0x0F);  // Maximum brightness
    writeToMouthDisplay(0x0F, 0x00);  // Display test off

    clearDisplay();

    char input;
    while (true) {
        if(pc.readable()){
        pc.read(&input, 1); //read 1 char

            if(input == 'L' || input == 'l'){ //love
                displayPattern(heart, lips);
                ThisThread::sleep_for(500ms);
                love();
                clearDisplay();
            } else if(input == 'H' || input == 'h'){ //happy
                displayPattern(upturnedEyes, smile);
                ThisThread::sleep_for(500ms);
                happy();
            } else if(input == 'M' || input == 'm'){ //mad
                displayPattern(upturnedEyes, madMouth);
                ThisThread::sleep_for(500ms);
                mad();
            } else if (input == 'S' || input == 's') {
                displayPattern(downturnedEyes, frown);
                ThisThread::sleep_for(500ms);
                sad();
            }
        }
    }
}