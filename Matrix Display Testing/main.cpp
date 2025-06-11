#include "DigitalOut.h"
#include "SerialBase.h"
#include "mbed.h"
#include <string>

SPI spi(PA_7, NC, PA_5);

DigitalOut cs(PB_6);

/*===============================================================
*EYE PATTERNS
================================================================*/
// Heart patterns
const uint8_t heart[8] = {
    0b00000000,
    0b01100110,
    0b11111111,
    0b11111111,
    0b01111110,
    0b00111100,
    0b00011000,
    0b00000000
};

const uint8_t hollowHeart[8] = {
    0b00000000,
    0b01100110,
    0b10111101,
    0b10011001,
    0b01000010,
    0b00100100,
    0b00011000,
    0b00000000
};

//happy/mad eyes
const uint8_t upturnedEyes[8] ={
    0b00000000,
    0b00000000,
    0b00011000,
    0b00111100,
    0b01000010,
    0b00000000,
    0b00000000,
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
    0b00001100,
    0b00110000,
    0b00110000,
    0b00011000,
    0b00011000,
    0b00110000,
    0b00110000,
    0b00001100
};

void writeMax7219(uint8_t reg, uint8_t data) {
    cs = 0;  // Select MAX7219
    spi.write(reg);
    spi.write(data);
    cs = 1;  // Deselect
}

void displayPattern(const uint8_t pattern1[8], const uint8_t pattern2[8], const uint8_t pattern3[8]) {
    for (int row = 0; row < 8; row++) {
        cs = 0;
        spi.write(row + 1); spi.write(pattern1[row]);
        spi.write(row + 1); spi.write(pattern2[row]);
        spi.write(row + 1); spi.write(pattern3[row]);
        cs = 1;
    }
}

void setBrightnessTo(string level) {
    cs = 0;
    spi.write(0x0A);

    if(level == "low") {
        spi.write(0x03);
    } else if(level == "medium") {
        spi.write(0x07);
    } else if(level == "high") {
        spi.write(0x0B);
    } else if(level == "ultra high") {
        spi.write(0x0F);
    }

    cs = 1;
}

void setLedsActive() {
    cs = 0;
    spi.write(0x0B);
    spi.write(0x07);
    cs = 1;
}

int main() {
    // SPI config: 1MHz, mode 0
    spi.format(8, 0);
    spi.frequency(1000000);

    // Initialize MAX7219
    writeMax7219(0x0C, 0x01); // Shutdown register: normal operation
    writeMax7219(0x09, 0x00); // Decode mode: none
    setLedsActive();
    setBrightnessTo("high");
    writeMax7219(0x0F, 0x00); // Display test: off
    writeMax7219(0x0C, 0x01); // Exit shutdown mode again for safety

    // Clear display
    for (int i = 1; i <= 8; i++) {
        writeMax7219(i, 0x00);
    }

    // Display pattern
    while (true) {
        // Light up first digit
        displayPattern(hollowHeart, madMouth, heart);
        ThisThread::sleep_for(500ms);
    }
}