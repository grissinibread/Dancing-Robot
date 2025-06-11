🤖 Dancing Robot
An expressive robot that dances and shows emotion through animated LED facial expressions and motor movements. Built using an STM32 Nucleo board, this robot combines embedded systems programming with creative physical interaction.

🧠 Overview
This project aims to bring emotion and motion together in a fun and educational robotics build. The Dancing Robot moves around and uses 8x8 LED matrices to simulate expressive eyes and a mouth, reacting with preprogrammed behaviors like happy, mad, sad, and love.

💡 Features
🟢 Animated facial expressions using LED matrices

🛞 Responsive wheeled motion via motor control

🔌 Serial and SPI communication

🛠️ Fully soldered and assembled hardware prototype

🎭 Emotion-based behaviors programmed in C

🧰 Technologies & Tools
STM32 Nucleo-F401RE Board

C programming

Mbed OS

SPI & Serial Communication

8x8 LED Matrices

L293D Motor Driver

Soldering + Circuit Diagrams

🧱 Components
STM32 Nucleo Board

L293D Motor Driver

8x8 LED Matrices (Eyes & Mouth)

Rubber Wheels

12V 3000mAh Battery

Breadboard, jumper wires, cardboard, fur, and other craft materials

🧾 Code Overview
c
Copy
Edit
// Motor control example
DigitalOut motorA1, motorA2;
PwmOut motorSpeed;
void mad() {
    motorA1 = 1;
    motorA2 = 0;
    motorSpeed = 1.0f;
    thread_sleep_for(1000);
}
c
Copy
Edit
// LED display pattern function
void displayPattern(uint8_t* eyePattern, uint8_t* mouthPattern) {
    for (int row = 0; row < 8; row++) {
        writeToEye(row, eyePattern[row]);
        writeToMouth(row, mouthPattern[row]);
    }
}
🚧 Challenges
Daisy-chaining and controlling LED matrices simultaneously

Power source stability and motor wiring

Soldering and constructing hardware with limited prototyping tools

Wheel mounting and physical mobility issues

👥 Team Contributions
Alejandro Navarro: Motor control logic, final integration, soldering

Adria Vargas: Display coding, robot chassis, circuit design

Chris Tran: Soldering assistance, LED animation logic, wiring
