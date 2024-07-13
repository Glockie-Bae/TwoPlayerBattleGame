#pragma once
#include<cmath>


class Vector2D {
public:
	float m_X = 0;
	float m_Y = 0;

public:
	Vector2D() {};
	~Vector2D() {};

	Vector2D(float x, float y) {
		m_X = x;
		m_Y = y;
	}

	void Reset() {
		m_X = 0;
		m_Y = 0;
	}
	void operator=(const Vector2D& vec) {
		m_X = vec.m_X;
		m_Y = vec.m_Y;
	}

	Vector2D operator+(const Vector2D& vec) const {
		return Vector2D(m_X + vec.m_X, m_Y + vec.m_Y);
	}

	void operator+=(const Vector2D& vec) {
		m_X += vec.m_X;
		m_Y += vec.m_Y;
	}

	Vector2D operator-(const Vector2D& vec) const {
		return Vector2D(m_X - vec.m_X, m_Y - vec.m_Y);
	}

	void operator-=(const Vector2D& vec) {
		m_X -= vec.m_X;
		m_Y -= vec.m_Y;
	}

	float operator*(const Vector2D& vec) const {
		return m_X * vec.m_X + m_Y * vec.m_Y;
	}

	Vector2D operator*(float val) const {
		return Vector2D(m_X * val, m_Y * val);
	}
	
	void operator*=(float val) {
		m_X = m_X * val;
		m_Y = m_Y * val;
	}

	float length() {
		return sqrt(m_X * m_X + m_Y * m_Y);
	}

	Vector2D normalize() {
		float len = length();

		if (len == 0)
			return Vector2D(0, 0);

		return Vector2D(m_X / len, m_Y / len);
	}
};