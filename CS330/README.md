# CS 330 Final Project – 3D Train Yard Scene

This project is a 3D recreation of a train yard scene developed using C++ and OpenGL. The objective was to take a 2D reference image and translate it into a fully interactive 3D environment while maintaining a balance between visual accuracy and performance. Instead of relying on complex models, the scene was built using low-polygon geometry constructed from primitive shapes such as boxes, cylinders, planes, and torus meshes. This approach allowed for efficient rendering while still producing recognizable and structured objects.

The scene makes use of modular design by grouping related geometry into reusable functions. Objects such as tank cars, box cars, and the locomotive were not created as one-off models, but instead constructed through functions that combine transformations, materials, and meshes. This makes it possible to reuse the same logic across multiple parts of the scene while maintaining consistency and reducing redundancy in the code.

Texture mapping was applied to several objects, including the ground, buildings, silo, and freight cars, in order to compensate for the simplicity of the underlying geometry. By adjusting UV scaling, textures are distributed evenly across surfaces to avoid stretching and distortion, which helps maintain visual quality throughout the scene.

Lighting was implemented using both a directional light and multiple point lights to ensure the entire scene remains visible from different viewing angles. The Phong shading model was used, incorporating ambient, diffuse, and specular components to give objects depth and material definition. This combination allows the scene to avoid flat shading and better simulate how light interacts with different surfaces.

The camera system allows full navigation of the scene using standard input controls. Movement is handled across all three axes, while mouse input controls camera orientation through pitch and yaw. Scroll input was also implemented to dynamically adjust movement speed, allowing both precise and large-scale navigation. In addition, the scene supports switching between perspective and orthographic projections, allowing the user to view the environment with or without depth distortion while maintaining the same camera position.

Overall, this project demonstrates a structured approach to 3D scene development by combining transformations, lighting, texturing, and interactive controls. The design prioritizes modularity, efficiency, and clarity, reflecting how a real-world graphics application would be developed.

Reflection
How do I approach designing software?

When I approach designing software, I usually start with a rough idea of what I want the final result to look like and then build toward that step by step. For this project, I focused on recreating a train yard scene, so I spent a lot of time thinking about placement, scale, and how everything would fit together visually. Instead of trying to make everything perfect right away, I built a base scene and then kept refining it as I went.

What new design skills has this project helped me develop?

This project helped me get better at thinking in 3D space. Before this, I didn’t really think about how object size, spacing, and alignment affect how realistic something looks. I also learned how important consistency is when repeating objects like train cars and tracks.

What design process did I follow?

I followed an iterative process where I added objects one at a time and constantly adjusted them. I would build something, test it, then go back and tweak positioning, scaling, or lighting until it looked right.

How can this design approach be used in the future?

This approach can be used in future projects by breaking larger problems into smaller parts and improving them over time instead of trying to build everything perfectly in one pass.

How do I approach developing programs?

When developing programs, I focus on getting something working first, then improving it. I’d rather have a basic version that runs than try to build something complex all at once and get stuck.

What new development strategies did I use?

One of the biggest things I used in this project was modular design. I created reusable functions for objects like train cars instead of rewriting the same code multiple times, which made everything easier to manage.

How did iteration factor into your development?

Iteration was a big part of this project. I was constantly testing changes, especially with lighting, textures, and camera movement, and adjusting things until they looked right.

How has your approach to coding evolved?

Earlier on, I focused mostly on getting things to work, but now I focus more on keeping code organized and readable. Breaking things into functions made a big difference.

How can computer science help me reach my goals?

Computer science allows me to build real projects like this that I can add to my portfolio. That’s important because it shows actual work instead of just theory.

How do graphics/visualizations help in education?

This project helped me understand how math and programming work together to create something visual and interactive instead of just numbers on a screen.

How do graphics/visualizations help professionally?

These skills can be used in areas like game development, simulations, or visualization tools. It also improves problem-solving because you have to think about both logic and visuals at the same time.

**Author:** Tyler Hubbell
SNHU – Computer Science
