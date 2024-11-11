# Atmega324-Robot

Robot designed as part of the INF1900 - Initial Embedded Systems Project course at Polytechnique Montréal.

---

## Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Hardware Connections](#hardware-connections)
- [Installation](#installation)
- [Usage](#usage)

---

## Project Overview
This project involves developing two autonomous robots using the ATmega324PA microcontroller. Each robot is programmed to perform a distinct set of tasks:
1. **Robot R1**: Navigates to the center of a box from a random starting point using distance sensors.
2. **Robot R2**: Follows a line path, detects segments, and communicates the mapped route to Robot R1 via infrared transmission.

## Features
### Robot R1:
- **Distance Sensing**: Detects boundaries within a confined space and centers itself.
- **Infrared Communication**: Receives map data from Robot R2 and provides visual feedback via LEDs.

### Robot R2:
- **Line Following**: Detects and follows a line on the ground using multiple sensors.
- **Mapping and Transmission**: Maps its path and transmits data to Robot R1 using infrared communication.

### Shared Functionalities:
- **Autonomous Navigation**: Embedded decision-making for obstacle avoidance and path tracking.
- **Real-Time Communication**: Implements RS232 and infrared for inter-robot data transfer.

## Hardware Connections
The detailed hardware connections for both Robot R1 and Robot R2 can be found in the file `ListeDesBranchements.txt`.

## Installation
1. **Clone the Repository**:
   ```bash
   git clone <repository_url>
2. **Build the Libraries** :
    ```bash
    cd ./projet/lib
    make clean
    make
3. **Install Programs on the Microcontrollers (ensure microcontrollers are connected)**:
   ```bash
    cd ./projet/app1
    make clean
    make
    make install
    cd ./projet/app2
    make clean
    make
    make install
## Usage
1. **After installing the programs onto the AVR microcontrollers, power each robot** :
   
   -  Motherboard: 9V battery
   -  H-Bridge: 6 AA batteries.
3. **Place Robot R1 in the designated box for autonomous navigation.**
4. **Position Robot R2 at the start of the line path for line-following.**
5. **Observe LED indicators and sound feedback**:
   - Robot R1: LEDs indicate position and communication status.
   - Robot R2: LED turns red upon path completion.
---
This project demonstrates core principles of embedded systems design, emphasizing autonomous navigation, mapping, and inter-robot communication.
