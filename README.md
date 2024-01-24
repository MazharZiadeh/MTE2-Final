Project Title: 3D Particle Collision Simulation
------------------------------------------------------------------------------------------
Introduction:
------------------------------------------------------------------------------------------
The simulation is designed to demonstrate the physics of elastic collisions in a 3D environment. Each particle is represented as a sphere, and the container is also a larger sphere. The particles move freely within the container, and when they collide with each other or the container, they bounce back due to the elastic nature of the collision.

Installation:
------------------------------------------------------------------------------------------
To install the project, you need to have a C++ compiler and OpenGL installed on your machine. Clone the repository and compile the Main.cpp file.

Usage:
------------------------------------------------------------------------------------------
After compiling the project, run the executable. The simulation will start, and you will see particles moving and colliding within the container sphere.
camera uses the mouse to rotate around, and WASD keys to move in the scene, 

F: Refresh particles

G: Decrease the number of particles by 1, with a minimum of 1

H : Increase the number of particles by 1

J : Reset the number of particles to 10

O : Toggle wireframe mode

P : Toggle pause

I : Toggle background gradient

Known Issues:
------------------------------------------------------------------------------------------
Currently, there is a known issue where the main container sphere is not visible. We are aware of this issue and are working on a fix. However, this does not affect the functionality of the particle collisions.

Elastic Collision:
------------------------------------------------------------------------------------------
In this project, an elastic collision is one where the total kinetic energy of the system (the particles and the container) is conserved before and after the collision. This means that no energy is lost to heat, sound, or any other form of energy. In the context of this simulation, it means that when two particles collide, they will bounce off each other and continue moving, their combined energy remaining constant.

Sphere Generation:
------------------------------------------------------------------------------------------
The spheres in this simulation, both the particles and the container, are generated mathematically using the equation of a sphere in 3D space. This equation is x² + y² + z² = r², where (x, y, z) are the coordinates of any point on the sphere, and r is the radius of the sphere. By varying the radius and the center point, we can generate spheres of different sizes and at different positions.

Please note that this README is a general guide. For specific details about the code and its implementation, refer to the comments in the Main.cpp file.

