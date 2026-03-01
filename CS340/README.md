## CS 340 - Dashboard Application and Database Integration
### Project Overview and Client Needs

The application developed in this course is a data dashboard designed to support Grazioso Salvare in managing and analyzing rescue animal data. The primary objective was to create a system capable of retrieving, filtering, and displaying relevant database information in a structured and accessible format. The project addressed a real-world client requirement: transforming raw database records into meaningful visual insights that assist with operational decision-making. By focusing on clarity, accuracy, and reliability, the dashboard provides an efficient way to navigate complex datasets without overwhelming the user.

### Modular Design and Maintainability

A major emphasis of this project was designing software that is maintainable, readable, and adaptable. In Project One, I developed a standalone CRUD Python module to manage interactions with the MongoDB database. Rather than embedding database queries directly into the dashboard application in Project Two, I reused this module to separate data access from presentation logic.

This modular approach provided significant advantages. It improved readability by isolating database operations in a single, organized file. It also enhanced adaptability, as any changes to database structure or query logic could be handled within the CRUD module without disrupting the dashboard interface. This structure reflects professional software engineering practices and ensures scalability for future enhancements.

The CRUD module could easily be repurposed in future projects that require database integration, including APIs, reporting systems, analytics tools, or web applications. Designing reusable components reduces redundancy and promotes long-term maintainability.

### Problem-Solving Approach and System Design

Approaching this project as a computer scientist required analyzing client requirements and translating them into technical solutions. I began by identifying the necessary data filters and determining how to structure database queries to meet Grazioso Salvare’s needs efficiently. From there, I focused on ensuring that each dashboard widget retrieved only relevant information, minimizing unnecessary database operations.

This project differed from earlier coursework because it required integrating multiple components into a cohesive system rather than solving isolated programming exercises. I had to think about data flow, modular architecture, and system-level organization. In future database-driven projects, I would continue applying a structured methodology: clearly defining requirements, designing database schemas intentionally, separating backend logic from user interface code, and validating each component before full integration.

### The Role of Computer Science in Organizational Impact

Computer scientists develop systems that transform data into actionable insights. In this project, the dashboard enables Grazioso Salvare to efficiently analyze rescue animal data and identify patterns that support operational decisions. Instead of manually sorting through database entries, users can quickly filter and visualize relevant information.

Projects like this demonstrate the practical impact of structured programming and thoughtful database design. By building tools that improve efficiency and accuracy, software solutions directly enhance an organization’s ability to serve its mission. This experience highlights how computer science extends beyond writing code, it involves designing systems that solve real problems and create measurable value.

Coursework and projects completed for CS 340
