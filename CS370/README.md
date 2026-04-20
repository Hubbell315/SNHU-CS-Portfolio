
# CS 370 – Artificial Intelligence

## Project: Pirate Intelligent Agent (Treasure Hunt)

### Project Summary
In this project, I implemented a deep Q-learning intelligent agent to solve a treasure hunt maze problem. The goal of the agent was to navigate an environment and consistently reach the treasure while avoiding obstacles and inefficient paths.

The initial codebase provided core environment components, including the TreasureMaze class and GameExperience replay memory system. These handled the maze structure, rewards, penalties, and experience storage.

I developed the reinforcement learning logic myself, including:
- The deep Q-learning training loop (`qtrain`)
- Epsilon-greedy decision-making (balancing exploration vs exploitation)
- Neural network training using experience replay
- Q-value updates and reward propagation
- Win tracking and performance evaluation

Through iterative improvements, I refined the agent’s ability to learn optimal paths and consistently reach the goal.

---

## Learning Reflection

### What do computer scientists do, and why does it matter?
Computer scientists design systems that solve complex problems through logic, data, and automation. In this project, I built an intelligent system capable of learning from experience and improving over time without being explicitly programmed for every scenario.

This work matters because intelligent systems are increasingly used in real-world applications such as robotics, transportation, recommendation systems, and automation. The ability to design systems that can learn and adapt is a critical part of modern technology.

---

### How do I approach a problem as a computer scientist?
I approach problems by breaking them down into smaller, manageable components. For this project, I analyzed the environment, defined how the agent interacts with it, and then built a learning system step by step.

I focus on:
- Understanding the problem requirements
- Designing a structured solution
- Iteratively testing and improving performance
- Debugging based on observed behavior

This systematic approach allows me to handle complex problems more effectively.

---

### What are my ethical responsibilities to users and organizations?
As a developer of intelligent systems, I have a responsibility to ensure that the systems I build behave reliably, transparently, and safely.

This includes:
- Preventing unintended or harmful behavior
- Ensuring fairness and avoiding bias
- Protecting user data and privacy
- Clearly communicating system limitations

In reinforcement learning systems specifically, it is important to ensure that reward structures do not unintentionally encourage harmful or unethical behavior.

---

## Repository Contents
- `TreasureHuntGame.ipynb` – Jupyter Notebook containing the intelligent agent implementation
