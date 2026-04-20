# CS 330 Final Project – 3D Train Yard Scene

This project is a 3D recreation of a train yard scene developed using C++ and OpenGL. The objective was to take a 2D reference image and translate it into a fully interactive 3D environment while maintaining a balance between visual accuracy and performance. Instead of relying on complex models, the scene was built using low-polygon geometry constructed from primitive shapes such as boxes, cylinders, planes, and torus meshes. This approach allowed for efficient rendering while still producing recognizable and structured objects.

The scene makes use of modular design by grouping related geometry into reusable functions. Objects such as tank cars, box cars, and the locomotive were not created as one-off models, but instead constructed through functions that combine transformations, materials, and meshes. This makes it possible to reuse the same logic across multiple parts of the scene while maintaining consistency and reducing redundancy in the code.

Texture mapping was applied to several objects, including the ground, buildings, silo, and freight cars, in order to compensate for the simplicity of the underlying geometry. By adjusting UV scaling, textures are distributed evenly across surfaces to avoid stretching and distortion, which helps maintain visual quality throughout the scene.

Lighting was implemented using both a directional light and multiple point lights to ensure the entire scene remains visible from different viewing angles. The Phong shading model was used, incorporating ambient, diffuse, and specular components to give objects depth and material definition. This combination allows the scene to avoid flat shading and better simulate how light interacts with different surfaces.

The camera system allows full navigation of the scene using standard input controls. Movement is handled across all three axes, while mouse input controls camera orientation through pitch and yaw. Scroll input was also implemented to dynamically adjust movement speed, allowing both precise and large-scale navigation. In addition, the scene supports switching between perspective and orthographic projections, allowing the user to view the environment with or without depth distortion while maintaining the same camera position.

Overall, this project demonstrates a structured approach to 3D scene development by combining transformations, lighting, texturing, and interactive controls. The design prioritizes modularity, efficiency, and clarity, reflecting how a real-world graphics application would be developed.

## Reflection

### How do I approach designing software?
When I approach designing software, I usually start with a general idea of what I want the final result to look like and then break it down into smaller parts. For this project, I focused on building the overall scene first and then refining object placement, scale, and detail over time.

### What new design skills has this project helped me develop?
This project helped me improve how I think about spatial relationships in a 3D environment. I learned how important scaling, positioning, and consistency are when trying to make a scene look realistic.

### What design process did I follow?
I followed an iterative approach where I started simple and gradually added more detail. Instead of trying to build everything at once, I made small improvements throughout each milestone.

### How can this design approach be used in the future?
This approach can be applied to future projects by breaking down complex systems into smaller steps and improving them over time instead of trying to perfect everything at once.

### How do I approach developing programs?
When developing programs, I focus on getting a working base first and then building on top of it. I prefer to make sure something functions before improving or optimizing it.

### What new development strategies did I use?
I focused more on modular design by separating logic into reusable functions. This made it easier to manage and update different parts of the program.

### How did iteration factor into your development?
Iteration was a big part of my process. I continuously tested and adjusted the scene, especially with lighting, textures, and positioning.

### How has your approach to coding evolved?
My approach has become more structured. I now focus more on organization and readability instead of just getting something to work.

### How can computer science help me reach my goals?
Computer science allows me to build real applications and projects that I can use in my portfolio, which helps prepare me for professional work.

### How do graphics/visualizations help in education?
This project helped me better understand how math, logic, and programming come together to create interactive visual environments.

### How do graphics/visualizations help professionally?
These skills can be applied in areas like game development, simulations, and visualization tools, and they improve problem-solving and technical thinking.

**Author:** Tyler Hubbell
SNHU – Computer Science
