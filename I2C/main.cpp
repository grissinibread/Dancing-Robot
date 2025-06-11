#include "I2C.h"
#include "mbed.h"
#include "platform/mbed_thread.h"

I2C temperatureSensor(D14, D15); // SDA, SCL
Serial pc(D1, D0);               // TX, RX

#define TS_ADDR 0x90             // 7-bit address shifted (mbed expects 8-bit here)

int main() {

    char tempRead[2];
    char startConvertT[1] = {0x51};
    char readTemp[1] = {0xAA};

    temperatureSensor.write(TS_ADDR, startConvertT, 1);
    int16_t tempRaw;
    float temperature;

    while (true) {
        thread_sleep_for(1000);

        temperatureSensor.write(TS_ADDR, readTemp, 1);

        temperatureSensor.read(TS_ADDR, tempRead, 2);

        tempRaw = (tempRead[0] << 8) | tempRead[1];

        temperature = tempRaw / 256.0f;

        pc.printf("Temperature: %.2f C\n", temperature);
    }
}