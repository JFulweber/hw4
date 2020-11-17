#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

namespace Raytracer148 {
    class Rectangle : public Shape {
    public:
        Rectangle(Eigen::Vector3d& vmin, Eigen::Vector3d &vmax, Material m): Shape(m) {
            bounds[0] = vmin;
            bounds[1] = vmax;
        }
        Eigen::Vector3d bounds[2];
        virtual HitRecord intersect(const Ray& ray);

    private:
    };
}

#endif
