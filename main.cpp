#include <iostream>
#include "Image.h"
#include "Scene.h"
#include "Sphere.h"
#include "Rectangle.h"
#include "Constant.h"

using namespace std;
using namespace Raytracer148;
using namespace Eigen;

int problemNumber;

int main(int argc, char** argv) {
    problemNumber = atoi(argv[1]);
    cout << "set problem number to" << argv[1] << endl;
    Image im(400, 400);

    Scene scene;

    Vector3d center;
    //center[0] = 0;
    //center[1] = 0;
    //center[2] = 4;
    //scene.addShape(new Sphere(center, 2));

    //center[0] = -.5;
    //center[1] = 1;
    //center[2] = 2.5;
    //scene.addShape(new Sphere(center, .5));

    center[0] = -.5;
    center[1] = 0;
    center[2] = 2.5;
    scene.addShape(new Sphere(center, .5, Material(Vector3d(0, 1, 0), 1, true)));
    center[0] = .5;
    center[1] = 0;
    center[2] = 2.5;
    scene.addShape(new Sphere(center, .5, Material(Vector3d(1, 0, 0), 1, true)));
    scene.addShape(new Rectangle(Vector3d(-.5, 0, 2.5), Vector3d(.5, 5, 2.5), Material(Vector3d(1, 1, .2), 2)));
    Vector3d offset;
    offset[0] = -5;
    offset[1] = -1;
    offset[2] = 0;
    Vector3d minBound;
    minBound[0] = minBound[1] = minBound[2] = 0;
    Vector3d maxBound;
    maxBound[0] = 10;
    maxBound[1] = .5;
    maxBound[2] = 10;
    minBound += offset;
    maxBound += offset;
    Rectangle *r = new Rectangle(minBound, maxBound, Material(Vector3d(.8, 0, .5), 3));
    scene.addShape(r);
    
    scene.render(im);

    im.writePNG("test.png");

    return 0;
}
