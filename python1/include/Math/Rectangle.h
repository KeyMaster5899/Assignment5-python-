#ifndef _A3MLRCT_
#define _A3MLRCT_
#include "Vector2.h"
class Rectangle {
public: 
	Vector2 m_X, m_N;

	Rectangle():m_X(Vector2()), m_N(Vector2()){}
	Rectangle(Vector2 max, Vector2 min):m_X(max), m_N(min){}
	Rectangle(Rectangle &other):m_X(other.m_X), m_N(other.m_N){}

	bool Collide(const Rectangle &other);
	static bool Collide(Rectangle &r1, Rectangle &r2);
};
#endif