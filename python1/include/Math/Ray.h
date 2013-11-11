#ifndef _A3MLRAY_
#define _A3MLRAY_
#include "Vector3.h"
class Ray{
public:
	Vector3 m_Origin;
	Vector3 m_Direction;

	Ray():m_Origin(Vector3()),m_Direction(Vector3()){}
	Ray(Vector3 org, Vector3 dir):m_Origin(org),m_Direction(dir.GetUnit()){}
	Ray(Ray &other):m_Origin(other.m_Origin), m_Direction(other.m_Direction){}

};
#endif