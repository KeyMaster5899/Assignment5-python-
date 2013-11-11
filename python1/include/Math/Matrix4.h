#ifndef _A3MLM4_
#define _A3MLM4_
#include "Vector3.h"
#include "Vector4.h"
class Matrix4{
public:
	union {
		struct{
			float m[4][4];
		};
		struct {
			float f[16];
		};
		struct {
			float m11,m12,m13,m14;
			float m21,m22,m23,m24;
			float m31,m32,m33,m34;
			float m41,m42,m43,m44;
		};

	};



	Matrix4();
	Matrix4(	float a11, float a12, float a13, float a14,
		float a21, float a22, float a23, float a24,
		float a31, float a32, float a33, float a34,
		float a41, float a42, float a43, float a44
		);
	Matrix4(const Matrix4 &a_M4);

	void OrthoProjection(float a_l,float a_r,float a_t,float a_b,float a_n,float a_f);

	Matrix4 Translate(Vector3 v);
	Matrix4 Rotate(float rotation, Vector3 axis);

	const Vector4 operator *(const Vector4 &a_Vector4);
	Vector4 operator *=(const Vector4 &a_Vector4);

	bool operator == (const Matrix4 &a_matrix4) const;
	bool operator != (const Matrix4 &a_matrix4) const;
	const Matrix4 operator -() const;

	const Matrix4 operator *(Matrix4 &a_Matrix4);
	Matrix4 operator *=(Matrix4 &a_Matrix4);

};
#endif