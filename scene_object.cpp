/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements scene_object.h

***********************************************************/

#include <cmath>
#include <iostream>
#include "scene_object.h"

bool UnitSquare::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld ) {
	// DONE: implement intersection code for UnitSquare, which is
	// defined on the xy-plane, with vertices (0.5, 0.5, 0),
	// (-0.5, 0.5, 0), (-0.5, -0.5, 0), (0.5, -0.5, 0), and normal
	// (0, 0, 1).
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point,
	// intersection.normal, intersection.none, intersection.t_value.
	//
	// HINT: Remember to first transform the ray into object space
	// to simplify the intersection test.

	// transform the ray into object space
	Ray3D obj_ray;
	obj_ray.origin = worldToModel * ray.origin;
	obj_ray.dir = worldToModel * ray.dir;

	// case 1: if the ray is in xy-plane, it will not intersect with the unit square
	if(obj_ray.dir[2] == 0)
	{
		return false;
	}

	// case 2: the general case, the ray is not in xy-plane
	double t_value = (-obj_ray.origin[2])/obj_ray.dir[2];
	if(t_value <= 0)
	{
		return false;
	}
	// 1. x componet of the intersection
	double x = obj_ray.origin[0] + t_value * obj_ray.dir[0];
	// 2. y componet of the intersection
	double y = obj_ray.origin[1] + t_value * obj_ray.dir[1];
	// 3. z componet of the intersection
	double z = 0.0;

	if(x < -0.5 || x > 0.5 || y < -0.5 || y > 0.5)
	{
		return false;
	}

	if(ray.intersection.none || t_value < ray.intersection.t_value)
	{
		Point3D intersection = modelToWorld * Point3D(x, y, z);
		Vector3D normal(0, 0, 1);
		normal = transNorm(worldToModel, normal);
		ray.intersection.point = intersection;
		ray.intersection.normal = normal;
		ray.intersection.mat = ray.intersection.mat;
		ray.intersection.t_value = t_value;
		ray.intersection.none = false;
		return true;
	}

}

bool UnitSphere::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld ) {
	// DONE: implement intersection code for UnitSphere, which is centred
	// on the origin.
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point,
	// intersection.normal, intersection.none, intersection.t_value.
	//
	// HINT: Remember to first transform the ray into object space
	// to simplify the intersection test.

	// transform the ray into object space
	Ray3D obj_ray;
	obj_ray.origin = worldToModel * ray.origin;
	obj_ray.dir = worldToModel * ray.dir;

	// referred to the solution at:
	// http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection

	// analytic solution
	Vector3D L = obj_ray.origin - Point3D(0, 0, 0);
	double a = obj_ray.dir.dot(obj_ray.dir);
	double b = 2 * obj_ray.dir.dot(L);
	double c = L.dot(L) - 1.0;

	double discriminant = b * b - 4 * a * c;
	double x, y, z, t_value, t_value1, t_value2;

	// no solution
	if(discriminant < 0)
	{
		return false;
	}

	// 1 solution
	if(discriminant == 0)
	{
		t_value = - 0.5 * b / a;
	}

	// 2 solutions
	if(discriminant > 0)
	{
		float q = (b > 0) ? -0.5 * (b + sqrt(discriminant)) : -0.5 * (b - sqrt(discriminant));
		t_value1 = q / a;
		t_value2 = c / q;
	}

	if (t_value1 < t_value2){
		t_value = t_value1;
	}
	else{
		t_value = t_value2;
	}

	if(ray.intersection.none || t_value < ray.intersection.t_value)
	{
		// 1. x componet of the intersection
		double x = obj_ray.origin[0] + t_value * obj_ray.dir[0];
		// 2. y componet of the intersection
		double y = obj_ray.origin[1] + t_value * obj_ray.dir[1];
		// 3. z componet of the intersection
		double z = obj_ray.origin[2] + t_value * obj_ray.dir[2];

		Point3D intersection = modelToWorld * Point3D(x, y, z);
		Vector3D normal(x, y, z);
		normal = transNorm(worldToModel, normal);
		normal.normalize();

		ray.intersection.point = intersection;
		ray.intersection.normal = normal;
		ray.intersection.mat = ray.intersection.mat;
		ray.intersection.t_value = t_value;
		ray.intersection.none = false;
		return true;
	}
}
