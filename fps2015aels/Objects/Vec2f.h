#ifndef VEC2F_H_INCLUDED
#define VEC2F_H_INCLUDED

#include <GL/glut.h>
#include <iostream>

class Vec2f
{
private:
	GLfloat v[2];
public:
			Vec2f();
			Vec2f(float x, float y);
	float		&operator[](int index);
	float		operator[](int index) const;
	Vec2f		operator*(float scale) const;
	Vec2f		operator/(float scale) const;
	Vec2f		operator+(const Vec2f &other) const;
	Vec2f		operator-(const Vec2f &other) const;
	Vec2f		operator-() const;
	const		Vec2f &operator*=(float scale);
	const		Vec2f &operator/=(float scale);
	const		Vec2f &operator+=(const Vec2f &other);
	const		Vec2f &operator-=(const Vec2f &other);
	float		magnitude() const;
	float		magnitudeSquared() const;
	Vec2f		normalize() const;
	float		dot(const Vec2f &other) const;
};

Vec2f operator*(float scale, const Vec2f &v);
std::ostream &operator<<(std::ostream &output, const Vec2f &v);

#endif

