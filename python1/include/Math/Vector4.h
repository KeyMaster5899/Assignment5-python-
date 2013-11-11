#ifndef _A3MLV4_
#define _A3MLV4_
#include <string>
class Vector4 {
public:
	float x, y, z, w;
	Vector4():x(0),y(0),z(0),w(0){}
	Vector4(const float ax, const float ay, const float az): x(ax),y(ay),z(az),w(0){}
	Vector4(const float ax, const float ay, const float az, const float aw): x(ax),y(ay),z(az),w(aw){}
	Vector4(const Vector4 &av4): x(av4.x), y(av4.y), z(av4.z), w(av4.w){}
	Vector4(std::string HEX);

	float Magnitude();
	void Normalise();
	Vector4 GetUnit();

	bool operator == (const Vector4 &av4) const;
	bool operator != (const Vector4 &av4) const;
	const Vector4 operator - () const;
};
#endif