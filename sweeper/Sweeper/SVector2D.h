#ifndef S2DVECTOR_H
#define S2DVECTOR_H

#include <math.h>
struct SVector2D{
	double x, y;
	
	SVector2D(double a = 0.0f, double b = 0.0f):x(a),y(b){}

	SVector2D &operator+=(const SVector2D &rhs){
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	SVector2D &operator-=(const SVector2D &rhs){
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	SVector2D &operator*=(const double &rhs){
		x *= rhs;
		y *= rhs;
		return *this;
	}

	SVector2D &operator/=(const double &rhs){
		x /= rhs;
		y /= rhs;
		return *this;
	}
};

inline SVector2D operator*(const SVector2D &lhs, double rhs){
	SVector2D result(lhs);//复制构造函数是自带的么？
	result *= rhs;
	return result;
}

inline SVector2D operator*(double lhs, const SVector2D &rhs){
	SVector2D result(rhs);
	result *= lhs;
	return result;
}

inline SVector2D operator-(const SVector2D &lhs, const SVector2D &rhs){
	SVector2D result(lhs);
	result.x -= rhs.x;
	result.y -= rhs.y;
	return result;
}

inline double Vec2DLength(const SVector2D &v){
	return sqrt(v.x * v.x + v.y * v.y);
}

inline void Vec2DNormalize(SVector2D &v){
	double vector_length = Vec2DLength(v);
	v.x = v.x / vector_length;
	v.y = v.y / vector_length;
}

inline double Vec2DDot(SVector2D &v1, SVector2D &v2){
	return v1.x * v2.x + v1.y * v2.y;
}

inline int Vec2DSign(SVector2D &v1, SVector2D &v2){
	if(v1.y*v2.x > v1.x*v2.y)
		return 1;
	else
		return -1;
}

#endif