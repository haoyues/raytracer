/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements light_source.h

***********************************************************/

#include <cmath>
#include "light_source.h"

void PointLight::shade( Ray3D& ray ) {
	// DONE: implement this function to fill in values for ray.col
	// using phong shading.  Make sure your vectors are normalized, and
	// clamp colour values to 1.0.
	//
	// It is assumed at this point that the intersection information in ray
	// is available.  So be sure that traverseScene() is called on the ray
	// before this function.

    // For Phong shading model, need:
    // 1. normal at the intersection point
    // 2. intersection to light point vector
    // 3. incident light vector
    // 4. intersection to camera center vector

    // 1. normal at the intersection point
    Vector3D normal = ray.intersection.normal;
    normal.normalize();

    // 2. light to intersection point vector
    Vector3D s = _pos - ray.intersection.point;
    s.normalize();

    // 3. incident light vector
    Vector3D b = -s + 2 * (s.dot(normal)) * normal;
    b.normalize();

    // 4. intersection point to camera center vector
    Vector3D r = ray.origin - ray.intersection.point;
    r.normalize();

    // ambient component
    Colour ambient = ray.intersection.mat->ambient * _col_ambient;

    // diffuse component
    Colour diffuse = (s.dot(normal) > 0.0? s.dot(normal):0.0)
                        * ray.intersection.mat->diffuse
                        * _col_diffuse;

    // specular component
    Colour specular = (r.dot(b) > 0.0? pow(r.dot(b), ray.intersection.mat->specular_exp):0.0)
                        * ray.intersection.mat->specular
                        * _col_specular;

    // adding all components together
    ray.col = ambient + diffuse + specular;

	ray.col.clamp();
}
