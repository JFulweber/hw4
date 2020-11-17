#include "Rectangle.h"
#include <limits>
#include <iostream>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord Rectangle::intersect(const Ray& ray) {
    HitRecord result;
    result.t = -1;
    double txmin = (bounds[0].x() - ray.origin.x()) / ray.direction.x();
    double tymin = (bounds[0].y() - ray.origin.y()) / ray.direction.y();
    double tzmin = (bounds[0].z() - ray.origin.z()) / ray.direction.z();
    double txmax = (bounds[1].x() - ray.origin.x()) / ray.direction.x();
    double tymax = (bounds[1].y() - ray.origin.y()) / ray.direction.y();
    double tzmax = (bounds[1].z() - ray.origin.z()) / ray.direction.z();
    
    // all t*min will be closest to ray startt
    if (txmax < txmin) swap(txmax, txmin);
    if (tymax < tymin) swap(tymax, tymin);
    if (tzmax < tzmin) swap(tzmax, tzmin);

    // get greatest min, smallest max
    double tMin = (txmin > tymin) ? txmin : tymin;
    double tMax = (txmax < tymax) ? txmax : tymax;
    // if the x minimum is greater than y maximum, or vice  versa, no hit
    if (txmin > tymax || tymin > txmax) return result;
    if (tMin > tzmax || tzmin > tMax) return result; 
    if (tzmin > tMin) tMin = tzmin;
    if (tzmax < tMax) tMax = tzmax;
    result.position =  ray.origin + ray.direction * tMin;
    Vector3d hit = result.position;
    result.t = tMin;

    //normal calculation
    Vector3d norm;
    if (abs(hit.x() - bounds[0].x()) < std::numeric_limits<double>::epsilon()){
        norm.x() = -1;
        norm.y() = 0;
        norm.z() = 0;
    }
    else if (abs(hit.y() - bounds[0].y()) < std::numeric_limits<double>::epsilon()) {
        norm.x() = 0;
        norm.y() = -1;
        norm.z() = 0;
    }
    else if (abs(hit.z() - bounds[0].z()) < std::numeric_limits<double>::epsilon()) {
        norm.x() = 0;
        norm.y() = 0;
        norm.z() = -1;
    }
    else if (abs(hit.x() - bounds[1].x()) < std::numeric_limits<double>::epsilon()) {
        norm.x() = 1;
        norm.y() = 0;
        norm.z() = 0;
    }
    else if (abs(hit.y() - bounds[1].y()) < std::numeric_limits<double>::epsilon()) {
        norm.x() = 0;
        norm.y() = 1;
        norm.z() = 0;
    }
    else if (abs(hit.z() - bounds[1].z()) < std::numeric_limits<double>::epsilon()) {
        norm.x() = 0;
        norm.y() = 0;
        norm.z() = 1;
    }
    result.normal = norm;
    result.m = mat;
    return result;
}
