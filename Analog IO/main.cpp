#include "mbed_thread.h"
#include <mbed.h>

using namespace mbed;
using namespace std;

AnalogIn pitch(A0);
AnalogIn volume(A1);
PwmOut speaker(D6);

int minFrequency = 500; // 500Hz
int maxFrequency = 4000; // 4KHz

int main(void) {
    int frequency;

    while (true) {
        frequency = minFrequency + pitch.read() * (maxFrequency - minFrequency);

        speaker.period(1.0 / frequency);
        speaker.write(volume.read());

        thread_sleep_for(100);
    }
}