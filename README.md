# An Ogre3D implementation of Rigid Body Collisions using Oriented Bounding Boxes (OBB)

A simple implementation of a 3D rigid body collision engine with support for cuboid colliders built with OGRE 3D. It was built as my final project for a course on Fundamentals of Physics-Based Animation, and is a partial implementation of the paper "Dynamic collision detection using oriented bounding boxes" (2008, D Eberly) which is based on the SIGGRAPH paper "OBBTree: A Hierarchical Structure for Rapid Interference Detection" (1996, Gottschalk et al.). 

*Note: I published this code for demonstrative purposes only. There's a more complete implementation of OBB collisions in https://github.com/RandyGaul/qu3e which does what I was expecting from this project (after 4 years of work).*

[![Simulation Youtube video](https://img.youtube.com/vi/-T7ay-Wlm1U/0.jpg)](https://www.youtube.com/watch?v=-T7ay-Wlm1U)

*(click image for youtube video)*

For an in-depth technical report on this project, please download the **[Project Final Report](https://github.com/danyalejandro/ogre3d-collisions/blob/master/computer-animation-project.pdf)**.

## Lessons learned

I initially proposed skipping the implementation of a collider entity separate from the actual mesh, by reusing the mesh (brick) vertices for collision detection. However, after learning about manual 3D mesh creation on the implementation phase of this project, I discovered that creating the cuboid mesh requires 24 vertices for 12 triangles, each one with their own UV coordinates and normals, in a non-trivial order. This made evident the need of **implementing colliders separately**, specially with collision calculations in mind.

In technical terms, a **Collider** class is used to store the body's mass, velocity, acceleration and forces in both linear and angular terms, as well as a flag to make it "fixed" in space when we want it to ignore external forces (e.g. the floor cuboid). To keep track of rotation I use a quaternion, which already comes implemented in the Ogre3D graphics engine along with their math-related functionality. This object has a mesh attached to it's center so we can reflect all changes into visible objects, by updating the mesh's position and orientation after the frame's calculations are over.

To detect the occurrence of a collision between 2 colliders, I implement a **Separating-Axis test (SAT)**, which can work not only for boxes but convex polyhedra as well. In simplified terms, the SAT is based on the separating hyperplane problem, which states that given two convex vertex sets A and B, either the two sets are intersecting or there exists a separating hyperplane P such that A is on one side of P and B is on the other. The SAT leverages this concept by stating that if 2 bodies are not intersecting, the separating hyperplane exists.

The basic **collision response** is to apply an **impulse force** to both bodies at the point of contact in opposite direction to their speed. Obtaining the intersection point is complex because after a timestep there can be multiple points of intersection (which enters the realm of solid geometry computation). However, if we focus on the first time of intersection, we know that at most cases (vertex-to-vertex, vertex-to-edge, vertex-to-face and edge-to-edge) this point is unique. Eberly (2008) in his paper leverages this fact to present a detailed table with the coefficients needed to produce the unique points of intersection depending on the particular collision detection test that was fired first; the paper proposes to keep track of the time at which each of the intersection tests trigger for the first time to find the first one fired, but for this project we managed to obtain approximate results by just considering the first intersection test triggered when evaluating all of them in the order they appear in the table.

After obtaining an approximate collision point, I apply a simple impulse to both colliders to serve as collision respons, which in turn introduces both a rotational and displacement component to the force vectors of each body. For this project, I'm only applying an impulse of magnitude computed as a factor of the speed of both colliders (obtained empirically).

## Building and running

The project was created using Ogre 1.10.9 (cloned from github and built using CMake-GUI) and the CLion IDE on Ubuntu Linux (I was unable to build the same OGRE3D project on mac, despite great efforts). CLion makes it easier to edit the CMakeLists.txt configuration file commonly used in OGRE3D projects. I based my code on the basic examples included in the OGRE3D source code (Samples/Tutorials and Samples/Bootstrap) since the official tutorials are currently outdated. Lines are drawn by creating and updating an Ogre ManualObject.

If you want to build and run this project, make sure you're able to build and run a simple Ogre3D project (I recommend linux & CLion IDE for this purpose) first. This might involve building Ogre3D in your system from scratch as there are a few outdated compiled versions you can download but they might not work out of the box.

If you're able to run Ogre3D projects in your system, open the folder as a new project in CLion and review the contents of CMakeLists.txt so it matches your own system configuration (there's a couple paths you need to change there). That's usually enough to run the simulation.
