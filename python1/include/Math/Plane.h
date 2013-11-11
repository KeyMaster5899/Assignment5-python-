#ifndef _A3MLPLN_
#define _A3MLPLN_
#include "Vector3.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Ray.h"
class Plane {
public:
	float a,b,c,d;

	Plane():a(0),b(0),c(0),d(0){}
	Plane(float aa, float ab, float ac, float ad):a(aa),b(ab),c(ac),d(ad){}

	void Create(Vector3 &t1, Vector3 &t2, Vector3 &t3);

	bool AABBPlaneCollision(Rectangle &Box);
	bool CirclePlaneCollision(Circle &Circle);
	bool RayPlaneCollision(Ray &aRay);

	float GetDistance(Vector2 &position, float z);
	
};

#endif