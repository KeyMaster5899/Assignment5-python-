#ifndef _A3MLV3_
#define _A3MLV3_
class Vector3 {
public:
	float x, y, z;

	Vector3():x(0),y(0),z(0){}
	Vector3(const float ax, const float ay, const float az):x(ax),y(ay),z(az){}
	Vector3(const Vector3 &av3):x(av3.x),y(av3.y),z(av3.z){}

	const float Magnitude() const;
	void Normalise();
	bool IsUnit() const;
	const Vector3 GetUnit();
	friend float Distance(const Vector3 &av3a, const Vector3 &av3b);

	float Dot(const Vector3 &av3) const;
	friend float Dot(const Vector3 &av3a, const Vector3 &av3b);
	const Vector3 Cross(Vector3 &av3) const;
	friend const Vector3 Cross(const Vector3 &av3a, const Vector3 &av3b);

	const Vector3 RotateX (const float &ax) const;
	const Vector3 RotateY (const float &ay) const;
	const Vector3 RotateZ (const float &az) const;

	bool operator == (const Vector3 &av3) const;
	bool operator != (const Vector3 &av3) const;
	const Vector3 Vector3::operator - () const;

	inline Vector3 operator + (const float &as) const;
	inline Vector3 operator + (const Vector3 &av3) const;
	inline Vector3& operator += (const float &as);
	inline Vector3& operator += (const Vector3 &av3);
	
	inline Vector3 operator - (const float &as) const;
	inline Vector3 operator - (const Vector3 &av3) const;
	inline Vector3& operator -= (const float &as);
	inline Vector3& operator -= (const Vector3 &av3);
	
	inline Vector3 operator * (const float &as) const;
	inline Vector3 operator * (const Vector3 &av3) const;
	inline friend const Vector3 operator * (const float &as, const Vector3 &av3);
	
	inline Vector3& operator *= (const float &as);
	inline Vector3& operator *= (const Vector3 &av3);
	
	inline Vector3 operator / (const float &as) const;
	inline Vector3 operator / (const Vector3 &av3) const;
	inline Vector3& operator /= (const float &as);
	inline Vector3& operator /= (const Vector3 &av3);
};
#endif