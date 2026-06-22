# CS305 - Software Security

## Artifact

**Artemis Financial Practices for Secure Software Report**

This project focused on improving the security of a Spring Boot application for Artemis Financial. The work included identifying security concerns, implementing SHA-256 checksum verification, configuring HTTPS with SSL/TLS, and analyzing dependencies for known vulnerabilities.

## Technologies Used

* Java
* Spring Boot
* Maven
* SHA-256
* SSL/TLS
* HTTPS
* OWASP Dependency-Check
* Java Keytool

## Skills Demonstrated

* Vulnerability Assessment
* Secure Software Development
* Cryptographic Hashing
* Certificate Management
* HTTPS Configuration
* Dependency Analysis
* Security Testing

---

## Reflection

### Client Summary

Artemis Financial is a financial services company that wanted to improve the security of its software application. The goal was to better protect customer information and make sure data could be transmitted securely between the client and server. My task was to review the application, identify security concerns, and implement solutions that improved the overall security of the system.

### Software Security Vulnerabilities

One thing I think I did well was identifying vulnerabilities and understanding how different security controls could help reduce risk. Through this project, I learned that secure coding is not just about writing code that works. It is also about protecting data, reducing security risks, and making sure users can trust the software they are using. Strong security practices can help prevent data breaches and protect both the company and its customers.

### Challenges and Helpful Experiences

The most helpful part of this project was using OWASP Dependency-Check. It showed me that vulnerabilities are not always found in the code written by the developer. Sometimes they exist in third-party libraries that a project depends on. Learning how to review dependency reports and understand the results gave me a better understanding of how software security is evaluated in practice.

### Security Improvements

To improve security, I implemented SHA-256 checksum verification, generated an SSL certificate, configured HTTPS communication, and reviewed project dependencies for known vulnerabilities. Each of these changes added another layer of protection to the application. In future projects, I would continue using dependency scanning tools, vulnerability assessments, and secure coding practices to help identify risks and determine appropriate mitigation strategies.

### Verification and Testing

After making the security improvements, I tested the application to make sure everything still worked correctly. I verified that the SHA-256 checksum functionality was working as expected and confirmed that the application could run successfully over HTTPS. I also reran OWASP Dependency-Check after refactoring the application to make sure the changes did not introduce any new vulnerabilities.

### Resources and Tools

Some of the most useful tools and resources for this project were OWASP Dependency-Check, Java Keytool, Spring Boot documentation, Maven, SSL/TLS certificates, and SHA-256 hashing. These tools helped me better understand how security can be integrated into the software development process.

### Portfolio Value

This project demonstrates my ability to identify software vulnerabilities, implement security improvements, configure secure communications, and verify that an application remains functional after security changes are made. It also shows my experience working with industry security tools and secure software development practices.


