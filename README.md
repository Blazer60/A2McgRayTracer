[BallImage]: mainImage.jpg "Red Ball in a room of mirrors"
[VendorFolder]: vendor "vendor"
[GLM]: https://github.com/g-truc/glm "GLM Github page"
[SDL2]: https://github.com/libsdl-org/SDL "SDL Githun page"

# Software Based Ray Tracer | MCG A2 Assignment
![BallImage]
___
A partial implementation of Turner Whitted's Ray Tracing algorithm with Blinn-Phong reflections. The Ray Tracer can
handle shadow casting, multiple lights, multiple objects and reflections. Additionally, a simple 'skybox' allows for
highly reflective materials to be added in open spaces. The following items can be coded into the world:

- Cameras
- Spheres
- Triangles (double sided)
- Point lights
- Directional lights

Additionally, lighting materials can be added to lights, sphere and triangles. Triangles may have lighting materials
applied to the whole surface or per vertex.

## Project Dependencies
The project uses [GLM] and [SDL2] (Both found in [vendor][VendorFolder] file).
**Make sure that you're in x86 mode, otherwise it may not build properly.**

## How to use
Numbers '0', '1' and '2' currently switch between different scenes. Some scenes may take longer to load than others
(since everything is running on a single thread). Both escape and the 'X' button close the program upon finishing a
frame.

0. Is a mirror ball on a flat white surface.
1. Is a RGB Triangle on a flat white surface.
2. Is a mirror room with a Crimson Red ball in the center and a point light from the ceiling.

## References
- Wikipedia, Ray tracing (graphics) [online]. Available from: https://en.wikipedia.org/wiki/Ray_tracing_(graphics) 
  [Accessed 7 March 2021]
- Sebastian Lague, Gamedev Maths: point in triangle [online]. Available from: 
  https://www.youtube.com/watch?v=HYAgJN3x4GA [Accessed 5 April 2021]
- Turner Whitted, 1980, An Improved Illumination Model for Shaded Display [online], Bell Laboratories, Holmdel, New 
  Jersey. Available from: https://www.cs.drexel.edu/~david/Classes/CS586/Papers/p343-whitted.pdf [Accessed 25 March 
  2021]
- Bui Tuong Phong, 1975, Illumination for Computer Generated Pictures [online], University of Utah. Available from: 
  https://users.cs.northwestern.edu/~ago820/cs395/Papers/Phong_1975.pdf [Accessed 28 March 2021]
- Scratchpixel, An overview of the Ray-Tracing Rendering Technique [online]. Available from: 
  https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/light-transport-ray-tracing-whitted 
  [Accessed 25 March 2021]
- Wikipedia, Blinn-Phong Reflection Model [online]. Available from: 
  https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model [Accessed 25 March 2021]
