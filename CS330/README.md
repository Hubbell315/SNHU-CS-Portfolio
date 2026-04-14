# CS 330 Final Project – 3D Train Yard Scene

This project is a 3D recreation of a train yard scene developed using C++ and OpenGL. The objective was to take a 2D reference image and translate it into a fully interactive 3D environment while maintaining a balance between visual accuracy and performance. Instead of relying on complex models, the scene was built using low-polygon geometry constructed from primitive shapes such as boxes, cylinders, planes, and torus meshes. This approach allowed for efficient rendering while still producing recognizable and structured objects.

The scene makes use of modular design by grouping related geometry into reusable functions. Objects such as tank cars, box cars, and the locomotive were not created as one-off models, but instead constructed through functions that combine transformations, materials, and meshes. This makes it possible to reuse the same logic across multiple parts of the scene while maintaining consistency and reducing redundancy in the code.

Texture mapping was applied to several objects, including the ground, buildings, silo, and freight cars, in order to compensate for the simplicity of the underlying geometry. By adjusting UV scaling, textures are distributed evenly across surfaces to avoid stretching and distortion, which helps maintain visual quality throughout the scene.

Lighting was implemented using both a directional light and multiple point lights to ensure the entire scene remains visible from different viewing angles. The Phong shading model was used, incorporating ambient, diffuse, and specular components to give objects depth and material definition. This combination allows the scene to avoid flat shading and better simulate how light interacts with different surfaces.

The camera system allows full navigation of the scene using standard input controls. Movement is handled across all three axes, while mouse input controls camera orientation through pitch and yaw. Scroll input was also implemented to dynamically adjust movement speed, allowing both precise and large-scale navigation. In addition, the scene supports switching between perspective and orthographic projections, allowing the user to view the environment with or without depth distortion while maintaining the same camera position.

Overall, this project demonstrates a structured approach to 3D scene development by combining transformations, lighting, texturing, and interactive controls. The design prioritizes modularity, efficiency, and clarity, reflecting how a real-world graphics application would be developed.

**Author:** Tyler Hubbell
SNHU – Computer Science
