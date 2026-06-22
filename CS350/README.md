# Smart Thermostat Prototype

## Overview

This project was developed as the final project for CS 350: Emerging Systems Architectures and Technologies at Southern New Hampshire University.

The goal was to design and implement a smart thermostat prototype using a Raspberry Pi 4. The system monitors room temperature through an AHT20 temperature sensor, displays information on a 16x2 LCD screen, allows user interaction through push buttons, and communicates status updates through UART communication.

The thermostat operates in three states:

* Off
* Heat
* Cool

LED indicators provide visual feedback for the active operating mode, while the LCD displays the current temperature, thermostat state, date, time, and setpoint temperature.

## Technologies Used

* Python
* Raspberry Pi 4
* GPIO
* I2C Communication
* UART Communication
* AHT20 Temperature Sensor
* LCD Display
* State Machines
* GitHub

## Included Artifacts

* Thermostat.py
* Thermostat State Machine Diagram
* Final Thermostat Report

## Reflection

This project gave me hands-on experience integrating hardware and software into a functional embedded system. One of the biggest lessons I learned was the importance of troubleshooting and testing components individually before integrating them into a larger system. Throughout development I encountered issues involving hardware connections, button inputs, LCD functionality, and sensor integration. Working through those problems taught me how to isolate issues, verify assumptions, and approach debugging in a more systematic way.

If I were to improve the project, I would spend more time planning and documenting the overall design before implementation. While the iterative approach helped me learn, a more detailed design phase would likely have reduced some of the troubleshooting required later in development.

The skills developed during this project, including debugging, hardware and software integration, GPIO programming, I2C communication, UART communication, and state machine design, will transfer directly to future software engineering and embedded systems projects. To improve maintainability and readability, the project was organized into logical sections with descriptive naming conventions, comments, and a state machine architecture that clearly separates each operating mode and its behavior.
