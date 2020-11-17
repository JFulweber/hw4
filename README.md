# Homework 4 / COSC4370
Adair Fulweber/1769169
## Objective
The objective of this assignment is to modify the given ray-tracer and implement the following:
* A new shape (rectangle in my case)
* Blinn-Phong shading / specular reflection + individual materials 
* Shadows
* Mirror-like reflectance
## Environment
This was compiled on Windows using MS's C++ compiler in Visual Studio. The program requires the latest version of the Eigen library, furthermore, the headers need to be renamed to be .h files instead of extensionless - visual studio was not playing nice with extensionless headers for me. I uploaded my own Eigen folder so that you don't need to rename the files since it is annoying. 
## Project Details
In order to run the different 'problems,' I made the problem number a command line argument (default = 1). If you enter a number not within 1-4 it likely will crash. So you need to run "hw4.exe <problem number>". The rectangle takes two parameters, a min bound and a max bound vector. The material takes 3 parameters: a vector3d for color as rgb values between 0-1, a double for the specular coefficient, and a boolean "isGlazed" to determine if it is mirror-like reflection or just blinn-phong specular. Shadows are determined by casting a ray to the light position and determining if there is a hit on the way, similarly reflections are determined recursively with a depth of 5, though that doesn't really make much sense since there's not 5 things a ray could bounce off of. I did move the light source a little bit from it's starting position I believe - I think one unit higher, and maybe one unit to the left, in order to get more notable shadows and reflections, particularly between the two spheres.
## Result
The results can be seen in the attatched pictures.
## Reference
* The slides regarding ray tracing
* The slides regarding blinn-phong shading
* These slides from Cornell http://www.cs.cornell.edu/courses/cs4620/2012fa/lectures/35raytracing.pdf
* This video helped me understand ray-box intersection a bit better https://www.youtube.com/watch?v=4h-jlOBsndU
