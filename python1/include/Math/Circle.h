#ifndef _A3MLCRC_
#define _A3MLCRC_
#include "Vector2.h"
class Circle {
public:
	float m_Radius, m_Size;
	Vector2 m_Position;

	Circle():m_Radius(0),m_Size(0),m_Position(Vector2()){}
	Circle(float rad, float sz, Vector2 pos):m_Radius(rad),m_Size(sz),m_Position(pos){}
	Circle(Circle &other):m_Radius(other.m_Radius), m_Size(other.m_Size), m_Position(other.m_Position){}

	bool Collide(const Circle &other);
	static bool Collide(Circle &c1, Circle &c2);
}; 
#endif