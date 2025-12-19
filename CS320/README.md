# CS 320 – Software Test, Automation QA

This section documents my portfolio artifacts and reflections for CS 320. The included materials demonstrate my ability to design, test, and validate software using automated testing and quality assurance principles.

# How can I ensure that my code, program, or software is functional and secure?

I ensure my software is functional and secure by combining clear requirements, defensive coding practices, and thorough unit testing. In this course, I focused on validating functionality through automated unit tests using JUnit, which allowed me to verify that each service behaved as expected under both normal and edge-case conditions. Writing tests alongside the service logic helped catch errors early and ensured that changes did not introduce regressions.

From a security perspective, I enforced data validation and constraints at the object and service levels. Input values were checked for validity before being accepted, preventing invalid or inconsistent data from entering the system. By limiting direct data manipulation and using controlled service methods, I reduced the risk of unintended behavior.

# How do I interpret user needs and incorporate them into a program?

I interpreted user needs by carefully reviewing requirements and translating them into specific, testable behaviors within the software. In CS 320, the project requirements defined how contacts, tasks, and appointments should be created, updated, and deleted. I used these requirements to guide the design of both the service methods and the unit tests, ensuring that each user expectation was explicitly addressed.

Breaking requirements into smaller functional rules allowed me to implement features incrementally and verify them through testing. This approach ensured the program aligned with user expectations and behaved consistently.

# How do I approach designing software?

I approach software design by emphasizing simplicity, modularity, and testability. I begin by identifying the core responsibilities of each component and separating concerns so that each class or service has a clear purpose. Service classes handle business logic, while data objects focus on maintaining valid state.

Testing plays a key role in my design process. I design software in a way that makes it easy to test individual components independently, improving code quality, maintainability, and long-term reliability.

