#pragma once
#include <Eigen/Dense.h>

namespace Raytracer148 {

	class Material {
	public:
		Material() {
			color = Eigen::Vector3d(0, 0, 0);
			specular = 0;
			isGlazed = false;
		}
		Material(Eigen::Vector3d c, double s) {
			color = c;
			specular = s;
			isGlazed = false;
		};
		Material(Eigen::Vector3d c, double s, bool isG) {
			color = c;
			specular = s;
			isGlazed = isG;
		};
		Eigen::Vector3d color;
		double specular;
		bool isGlazed;
	};
}