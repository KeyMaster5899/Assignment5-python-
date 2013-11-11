#ifndef _A3ML_
#define _A3ML_

#include <string>
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix3.h"
#include "Math/Matrix4.h"
#include "Math/Rectangle.h"
#include "Math/Circle.h"
#include "Math/Ray.h"
#include "Math/Plane.h"

const float	PI		= 3.14159265358979323846f;
const float	DEG2RAD = 0.01745329251994329577f;
const float	RAD2DEG = 57.2957795130823208768f; 

inline float	DegreeToRadian(const float &a_D){
	return (a_D * PI / 180);
}
inline float	RadianToDegree(const float &a_R){
	return (a_R * 180 / PI);
}
inline int		next_p2(int a){
	int rval = 1;
	while(rval<a) rval<<=1;
	return rval;
}
inline float	clamp (float x, float a, float b){ 
	return (x < a) ? a : (x > b ? b : x);
}

using std::string;
	unsigned long long HEX2DEC(string HEX);
	string HEX2BIN (string HEX); 

	string DEC2HEX(unsigned long long DEC);
	string DEC2BIN(unsigned long long DEC);

	string BIN2HEX(string BIN);
	unsigned long long BIN2DEC(string BIN);

	string BITAND(string BIN, string BIN2);
	string BITOR (string BIN, string BIN2);
	string BITNOR(string BIN, string BIN2);
	string BITNOT(string BIN);
	string BITXOR(string BIN, string BIN2);

	string BITSHIFT(string BIN, int shift);

#endif