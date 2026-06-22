# CS 350 Portfolio Reflection

## Artifacts

For this portfolio submission, I selected my Thermostat Project source code and Thermostat State Machine Diagram as my primary artifacts. I also included the final project report because it provides additional information about the system architecture, design decisions, and recommendations for future development.

## Reflection

The thermostat project was designed to demonstrate how hardware and software can work together in an embedded system. Using a Raspberry Pi 4, I created a smart thermostat prototype that reads temperature data from an AHT20 sensor, displays information on an LCD screen, allows user interaction through buttons, and sends status updates through UART communication. The thermostat operates in three states: off, heat, and cool, with LEDs providing visual feedback based on the current operating mode.

Looking back on the project, I think troubleshooting was one of my strongest areas. Throughout development I ran into several issues involving hardware connections, button inputs, LCD functionality, and sensor integration. Instead of making multiple changes at once, I learned to isolate the problem and test individual components before integrating everything together. That approach made debugging much easier and helped me work through problems more efficiently.

One area where I could improve would be spending more time planning before implementation. A lot of my development process involved building, testing, troubleshooting, and then making adjustments as new issues appeared. While that taught me a lot about debugging, a more detailed design plan at the beginning would likely have reduced some of the troubleshooting required later in the project.

The resources I relied on most throughout the course were Raspberry Pi documentation, hardware documentation, GitHub, and the course materials. More importantly, I learned the value of breaking larger problems into smaller pieces and testing each component individually before combining them into a complete system. That approach is something I plan to continue using in future projects.

The biggest skill I will take away from this project is troubleshooting. Whether the issue is hardware or software, being able to work through a problem methodically is important. I also gained experience working with sensors, state machines, GPIO, I2C communication, UART communication, and GitHub. These are skills that will transfer well to future software engineering and embedded systems projects.

To keep the project maintainable and readable, I organized the code into logical sections, used descriptive names for variables and functions, and added comments throughout the project. The state machine design also helped keep the system organized because each operating mode had a clearly defined purpose and behavior. If additional functionality were added in the future, the project could be expanded without requiring major changes to the overall design.
