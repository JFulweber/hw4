#include "Scene.h"
#include "Constant.h"
#include <cmath>
#include <iostream>
using namespace Raytracer148;
using namespace std;
using namespace Eigen;

HitRecord Scene::closestHit(const Ray &ray) {
    HitRecord result;
    result.t = -1;
    bool foundSomething = false;

    for (unsigned int i = 0; i < shapes.size(); i++) {
        HitRecord r = shapes[i]->intersect(ray);
        if (r.t > std::numeric_limits<double>::epsilon() && (!foundSomething || r.t < result.t)) {
            result = r;
            foundSomething = true;
        }
    }
    result.hit = foundSomething;
    return result;
}


double length(Vector3d i, Vector3d j) {
    return sqrt(pow(i.x() - j.x(), 2) + pow(i.y() - j.y(), 2) + pow(i.z() - j.z(), 2));
}

double clamp(double lower, double upper, double val) {
    if (val <= lower) return lower;
    if (val >= upper) return upper;
    return val;
}

Vector3d reflect(Vector3d I, Vector3d N) {
    return I - 2.0 * N.dot(I) * N;
}

Vector3d materialDiffuseColor(.1, .1, .1);
Vector3d specularColor(.1, .1, .1);
double Brightness = 2;
// Returns an RGB color, where R/G/B are each in the range [0,1]
Vector3d Scene::trace(const Ray &ray, int recursionDepth){
    HitRecord r = closestHit(ray);

    Vector3d result;
    result[0] = result[1] = result[2] = .5;

    if (r.t < numeric_limits<double>::epsilon()) return result;
    Vector3d lightDir = (lightPos - r.position).normalized();
    double dot = lightDir.dot(r.normal);
    Vector3d h = lightDir.normalized() - ray.direction.normalized();
    double dist = length(lightPos, r.position);
    Vector3d lightNorm = lightPos.normalized();
    if (dot < 0) dot = 0;
    double cosAlpha = r.normal.dot(h);
    switch (problemNumber) {
        case 1:{
            result = Vector3d(dot,dot,dot);
            break;
        }
        case 3:{
            Ray curRay;
            curRay.direction = (lightPos - r.position).normalized();
            curRay.origin = r.position + curRay.direction * .01;
            HitRecord shadowR = closestHit(curRay);
            if (shadowR.hit) {
                return Vector3d(0, 0, 0);
            }
        }
        case 2:{
            result = r.m.color * dot;
            result += materialDiffuseColor * Brightness * max(0., r.normal.dot(lightDir));
            Vector3d specularTerm = specularColor * Brightness * pow(cosAlpha, r.m.specular);
            result += specularTerm;
            break;
        }
        case 4:{
            Ray curRay;
            curRay.direction = (lightPos - r.position).normalized();
            curRay.origin = r.position + curRay.direction * .01;
            HitRecord shadowR = closestHit(curRay);
            if (shadowR.hit) {
                return Vector3d(0, 0, 0);
            }
            Vector3d specularTerm;
            if (r.m.isGlazed && recursionDepth > 0) {
                // need to figure out reflected direction, then fire a trace off of that
                Vector3d ref = 2 * (r.normal.dot(-ray.direction)) * r.normal - (-ray.direction);
                ref = ref.normalized();
                Ray reflectRay;
                reflectRay.origin = r.position + ref*.01;
                reflectRay.direction = ref;
                specularTerm = trace(reflectRay, recursionDepth - 1);
                specularTerm *= r.m.specular;
            }
            else { //not glazed, normal specular reflection
                specularTerm = specularColor * Brightness * pow(cosAlpha, r.m.specular);
            }
            result = r.m.color;
            result += materialDiffuseColor * Brightness * max(0., r.normal.dot(lightDir));
            result += specularTerm;
            break;
        }
    }
    result[0] = clamp(0, 1, result[0]);
    result[1] = clamp(0, 1, result[1]);
    result[2] = clamp(0, 1, result[2]);
    return result;
}

void Scene::render(Image &image) {
    // We make the assumption that the camera is located at (0,0,0)
    // and that the image plane happens in the square from (-1,-1,1)
    // to (1,1,1).
    cout << "Problem number:" << problemNumber << endl;
    if (problemNumber == 0) problemNumber = 1;
    assert(image.getWidth() == image.getHeight());

    int size = image.getWidth();
    double pixelSize = 2. / size;
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++) {
            Ray curRay;
            curRay.origin[0] = curRay.origin[1] = curRay.origin[2] = 0;

            curRay.direction[0] = (x + 0.5) * pixelSize - 1;
            curRay.direction[1] = 1 - (y + 0.5) * pixelSize;
            curRay.direction[2] = 1;

            Vector3d color = trace(curRay, 3);
            image.setColor(x, y, color[0], color[1], color[2]);
        }
}
