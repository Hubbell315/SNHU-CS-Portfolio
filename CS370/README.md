# CS 370 - Artificial Intelligence  
## Pirate Intelligent Agent (Treasure Hunt)

This project centers on building an intelligent agent capable of solving a pathfinding problem within a maze-based environment. The goal was to train a pirate agent that could reliably navigate the maze and reach the treasure using reinforcement learning, rather than relying on predefined paths or hardcoded decisions. Over time, the agent improves by interacting with the environment and learning from the outcomes of its actions.

The starting point included a partially implemented codebase that handled the environment and experience tracking. The TreasureMaze class defined the maze layout along with its reward and penalty structure, while the GameExperience component stored past interactions for replay during training. From there, I focused on implementing the core learning system that allows the agent to make decisions and improve over time.

Most of my work went into developing the deep Q-learning training process. This involved building the training loop, implementing an epsilon-greedy strategy to balance exploration and exploitation, and integrating a neural network to approximate Q-values. As the agent explored the maze, it stored experiences and used them to refine its decision-making. Through repeated training and adjustment, the agent became more consistent and efficient in reaching the goal.

Working through this project gave me a much better understanding of how computer scientists approach complex problems using intelligent systems. Instead of trying to manually define every possible outcome, the focus shifts toward designing systems that can learn, adapt, and improve on their own. That idea shows up everywhere in modern computing, especially in areas like automation, robotics, and large-scale decision systems.

My approach to solving this problem was very iterative. I started by understanding how the environment worked and what the agent needed to accomplish, then broke the problem down into smaller parts. From there, I focused on building and testing each piece, especially the learning loop and decision-making logic. Reinforcement learning doesn’t just work on the first try, so a lot of the process involved observing behavior, adjusting parameters, and refining the system until the results were stable.

This project also reinforced how important it is to think about the behavior of the systems we build. With reinforcement learning, the agent is driven entirely by the reward structure, which means poorly designed rewards can lead to unintended behavior. Because of that, there’s a responsibility to design systems that are not only effective but also predictable and aligned with their intended purpose. That includes thinking about fairness, reliability, and how the system might behave in edge cases.

Overall, this project pushed me to think beyond just writing code and focus more on how systems learn and make decisions. It ties directly into real-world applications where systems need to operate in dynamic environments and adapt over time, which is something I’m interested in continuing to build on.
