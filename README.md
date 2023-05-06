# Ration Distribution System

This project is a ration distribution system that uses an Arduino microcontroller, RFID technology, an LCD module, a matrix keypad 4x3, weight sensors, LED lights, servo motors, and a flow sensing system to control the dispensing of kerosene.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Materials](#materials)
- [Circuit Diagram](#circuit-diagram)
- [Installation and Setup](#installation-and-setup)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The ration distribution system is designed to replace the old paper ration card system with a more secure and efficient system that uses RFID technology for user verification. The system is easy to use and provides a convenient way for users to receive their rations. In addition to dispensing rice, the system also includes a flow sensing system to control the dispensing of kerosene.

## Features

- Secure user verification using RFID technology
- Easy-to-use matrix keypad 4x3 for user input
- LCD module for displaying important information
- Weight sensors to measure the amount of rice dispensed
- LED lights to indicate the status of the system
- Servo motors to control the rice container valve
- Flow sensing system to control the dispensing of kerosene

## Materials

The following materials are needed to build the ration distribution system:

- Arduino microcontroller
- RFID reader
- RFID tags
- LCD module
- Matrix keypad 4x3
- Weight sensors
- LED lights
- Servo motors
- Flow sensing system

## Circuit Diagram

Here is the circuit diagram for the ration distribution system:

![Circuit Diagram](Circuit%20design.jpeg)

## Installation and Setup

1. Clone the repository using `git clone https://github.com/anasnazz/Ration-Distribution-System.git`
2. Upload the code to the Arduino microcontroller
3. Connect the RFID reader, LCD module, matrix keypad 4x3, weight sensors, LED lights, servo motors, and flow sensing system according to the circuit diagram
4. Power on the system and wait for the LCD to display "Please swipe your RFID tag"

## Usage

To use the ration distribution system, follow these steps:

1. Swipe your RFID tag on the RFID reader
2. Enter passcode
3. Select the item you want using the matrix keypad 4x3
4. Enter the amount of item
5. Wait for the LED lights to indicate that the system is ready
6. Place your container under the valve
7. The system will dispense the requested amount

## User Credentials

User credentials are currently stored in the code. For larger deployments, it is recommended to replace this system with a database.

## Contributing

Contributions are welcome! Please create a pull request if you have any improvements or bug fixes.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
