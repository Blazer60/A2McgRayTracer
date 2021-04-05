Software Based Ray Tracer | MCG A2 Assignment


A partial implementation of Turner Whitted Ray Tracing algorithm with Blinn-Phong reflections. The Ray Tracer can
handle shadow casting, multiple lights, multiple objects and reflections. Additionally, a simple 'skybox' allows for
highly reflective materials to be added in open spaces. The following items can be coded into the world:

    - Cameras
    - Spheres
    - Triangles (double sided)
    - Point lights
    - Directional lights

Additionally, lighting materials can be added to lights, sphere and triangles. Triangles may have lighting materials
applied to the whole surface or per vertex.

How to use:

Numbers '0', '1' and '2' currently switch between different scenes. Some scenes may take longer to load than others
(since everything is running on a single thread). Both escape and the 'X' button close the program upon finishing a
frame.

    0. Is a mirror ball on a flat white surface.
    1. Is a RGB Triangle on a flat white surface.
    2. Is a mirror room with a Crimson Red ball in the center and a point light from the ceiling.
