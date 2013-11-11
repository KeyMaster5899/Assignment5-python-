#ifndef _A3MLV2_
#define _A3MLV2_
class Vector2 {
public:
	float x, y;

	Vector2():x(0),y(0){}
	Vector2(const float ax, const float ay):x(ax),y(ay){}
	Vector2(const Vector2 &av2):x(av2.x),y(av2.y){}

	const float Magnitude() const;
	void Normalise();
	bool IsUnit() const;
	const Vector2 GetUnit();
	friend float Distance(const Vector2 &av2a, const Vector2 &av2b);

	float Dot(const Vector2 &av2) const;
	friend float Dot(const Vector2 &av2a, const Vector2 &av2b);
	const float Cross(Vector2 &av2) const;
	friend const float Cross(const Vector2 &av2a, const Vector2 &av2b);

	////////////////////////////////////////
	///// Lerp
	////////////////////////////////////////
	static Vector2 v2Lerp(const Vector2 v2a, const Vector2 v2b, const float t);
	static Vector2 v2Lerp2(const Vector2 v2a, const Vector2 v2b, const float t);
	////////////////////////////////////////
	///// Bezier
	////////////////////////////////////////
	static Vector2 v2Bezier(const Vector2 v2a, const Vector2 v2b, const Vector2 v2c, const float t);
	Vector2 Bezier(const Vector2 v2b, const Vector2 v2c, const float t);
	////////////////////////////////////////
	///// Hermite
	////////////////////////////////////////
	static Vector2 Hermite(Vector2& a_p1, Vector2& a_p2, Vector2& a_t1, Vector2& a_t2, float a_fS);


	bool operator == (const Vector2 &av2) const;
	bool operator != (const Vector2 &av2) const;
	const Vector2 operator - () const;

	Vector2 operator + (const float &as) const;
	Vector2 operator + (const Vector2 &av2) const;
	Vector2& operator += (const float &as);
	Vector2& operator += (const Vector2 &av2);

	Vector2 operator - (const float &as) const;
	Vector2 operator - (const Vector2 &av2) const;
	Vector2& operator -= (const float &as);
	Vector2& operator -= (const Vector2 &av2);

	Vector2 operator * (const float &as) const;
	Vector2 operator * (const Vector2 &av2) const;
	friend const Vector2 operator * (const float &as, const Vector2 &av2);
	Vector2& operator *= (const float &as);
	Vector2& operator *= (const Vector2 &av2);

	Vector2 operator / (const float &as) const;
	Vector2 operator / (const Vector2 &av2) const;
	Vector2& operator /= (const float &as);
	Vector2& operator /= (const Vector2 &av2);
};
#endif