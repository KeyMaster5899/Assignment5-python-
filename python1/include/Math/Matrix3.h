#ifndef _A3MLM3_
#define _A3MLM3_
#include "MathLibrary.h"
class Matrix3 {
public:
	float m11,m12,m13;
	float m21,m22,m23;
	float m31,m32,m33;

	Matrix3();
	Matrix3(	float a11, float a12, float a13,
		float a21, float a22, float a23,
		float a31, float a32, float a33);
	Matrix3(const Matrix3 &am3);

	Matrix3 Transpose();
	Matrix3 Identity(){return Matrix3(1,0,0,0,1,0,0,0,1);}
	friend Matrix3 Identity(){return Matrix3(1,0,0,0,1,0,0,0,1);}

	Matrix3 RotationX(const float &an){
		float c = cos(an), s = sin(an);
		return Matrix3(1,0,0,0,c,-s,0,s,c);
	}
	Matrix3 RotationY(const float &an){
		float c = cos(an), s = sin(an);
		return Matrix3(c,0,s,0,1,0,-s,0,c);
	}
	Matrix3 RotationZ(const float &an){
		float c = cos(an), s = sin(an);
		return Matrix3(c,-s,0,s,c,0,0,0,1);
	}

	Matrix3 Translation2D(const Vector3 &v){
		return Matrix3(	1,0,v.x,
						0,1,v.y,
						0,0,1);
	}
	Vector3 TransformV(const Vector3 &av3) const{
		float x = av3.x * m11 + av3.y * m21 + av3.z * m31;
		float y = av3.x * m12 + av3.y * m22 + av3.z * m32;
		float z = av3.x * m13 + av3.y * m23 + av3.z * m33;
		return Vector3(x,y,z);
	}

	const Vector3 operator *(const Vector3 &av3) {
		Vector3 t(av3);
		t.x = m11 * av3.x + m12 * av3.y + m13 * av3.z;
		t.y = m21 * av3.x + m22 * av3.y + m23 * av3.z;
		t.z = m31 * av3.x + m32 * av3.y + m33 * av3.z;
		return t;
	}
	Vector3 operator *=(const Vector3 &av3){
		return ((*this) * av3);
	}
	bool operator== (const Matrix3 &am3) const;
	bool operator!= (const Matrix3 &am3) const;
	const Matrix3 operator- () const{
		return Matrix3(	-m11,-m12,-m13,
						-m21,-m22,-m23,
						-m31,-m32,-m33);
	}
	const Matrix3 operator *(Matrix3 &am3);
	Matrix3 operator *=(Matrix3 &am3){
		return ((*this) * am3);
	}
};
#endif