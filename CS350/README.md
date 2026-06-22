# CS 350 Portfolio Reflection

## Selected Artifacts

For this portfolio submission, I selected my Thermostat Project source code and the Thermostat State Machine Diagram as my primary artifacts. I also included the final project report because it provides additional details about the system design, hardware architecture, and future recommendations for the project.

## Summarize the Project and What Problem It Was Solving

The goal of this project was to create a smart thermostat prototype using a Raspberry Pi 4. The thermostat reads temperature data from an AHT20 sensor, displays information on an LCD screen, and allows the user to switch between off, heat, and cool modes using buttons. The system also sends status updates through UART communication to simulate communication with a remote server. The project was designed to demonstrate how hardware and software can work together in an embedded system.

## What Did You Do Particularly Well?

I think one of the things I did well was troubleshooting. Throughout the project I ran into several issues involving hardware connections, button inputs, the LCD display, and sensor integration. Instead of changing multiple things at once, I learned to test one component at a time and isolate the problem before moving forward. That process saved a lot of frustration and helped me get the system working correctly.

## Where Could You Improve?

If I were to do the project again, I would spend more time planning before I started building. A lot of my development process involved building, testing, troubleshooting, and making adjustments along the way. While that helped me learn, having a more detailed design plan from the beginning probably would have reduced some of the time spent debugging later.

## What Tools and/or Resources Are You Adding to Your Support Network?

The biggest resources I used throughout this course were hardware documentation, Raspberry Pi resources, GitHub, and the course materials. I also learned how valuable it can be to break problems into smaller pieces and test components individually before integrating everything together. That approach is something I will continue using in future projects.

## What Skills From This Project Will Be Particularly Transferable to Other Projects and/or Coursework?

The biggest skill I will take away from this project is troubleshooting. Whether the issue is hardware or software, being able to systematically work through a problem is important. I also gained experience working with sensors, state machines, GPIO, I2C communication, UART communication, and GitHub. Those skills will transfer well into future software engineering and embedded systems projects.

## How Did You Make This Project Maintainable, Readable, and Adaptable?

I tried to keep the project organized by separating functionality into logical sections and using meaningful names for variables, functions, and classes. I also added comments throughout the code so it would be easier to understand later. Using a state machine design made the thermostat easier to follow because each operating mode had a clearly defined purpose and behavior. If additional features were added in the future, the project could be expanded without requiring a complete redesign.

