# CS305 - Software Security

## Artifact

**Artemis Financial Practices for Secure Software Report**

This project focused on improving the security of a Spring Boot application for Artemis Financial through vulnerability assessment, secure coding practices, cryptographic hashing, HTTPS implementation, and dependency analysis.

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
* Risk Mitigation

---

## Reflection

### Client Summary

Artemis Financial is a financial services company that wanted to improve the security of its software application. The organization needed a solution that would better protect sensitive customer information, verify data integrity, and secure communications between clients and servers. The primary objective was to identify vulnerabilities and implement security controls that reduced risk while maintaining application functionality.

### Software Security Vulnerabilities

One area I performed well in was identifying vulnerabilities and implementing practical security improvements. Secure coding is important because software vulnerabilities can expose sensitive information, disrupt business operations, and damage customer trust. Strong software security helps organizations reduce risk, protect customer data, maintain compliance requirements, and strengthen their overall security posture.

### Challenges and Helpful Experiences

The most helpful part of the project was learning how to use OWASP Dependency-Check to analyze third-party libraries for known vulnerabilities. It demonstrated that security risks do not always originate from application code and that dependency management is an important part of secure software development. Reviewing vulnerability reports and understanding how security tools identify risks provided valuable hands-on experience.

### Security Improvements

Several layers of security were added during the project. SHA-256 hashing was implemented to verify data integrity, SSL certificates were generated to support secure communications, HTTPS was configured to encrypt client-server traffic, and dependency analysis was performed to identify known vulnerabilities. In future projects, I would continue using vulnerability scanners, dependency analysis tools, secure coding standards, and security testing methodologies to assess risks and determine appropriate mitigation strategies.

### Verification and Testing

To ensure the application remained functional and secure, I performed both functional testing and security testing after implementing the security enhancements. The application was verified to run successfully using HTTPS, and the SHA-256 checksum functionality was tested to confirm correct operation. After refactoring the application, OWASP Dependency-Check was executed again to verify that no additional vulnerabilities were introduced and that the software continued to operate as intended.

### Resources and Tools

Resources and tools used throughout this project included Java Keytool, Spring Boot, Maven, SHA-256 hashing, SSL/TLS certificates, HTTPS configuration, OWASP Dependency-Check, and secure software development best practices. These tools provided practical experience with implementing and evaluating software security controls.

### Portfolio Value

This project demonstrates my ability to evaluate software security risks, implement secure coding practices, configure encrypted communications, perform dependency analysis, and verify application security through testing. Future employers can use this project as evidence of my understanding of secure software development principles and my ability to apply industry-standard security techniques within a real-world software application.

