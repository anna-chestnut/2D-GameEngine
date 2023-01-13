#pragma once
#include "Vector4.h"

namespace Engine {

	inline Vector4::Vector4(float i_X, float i_Y, float i_Z, float i_W) : m_X(i_X), m_Y(i_Y), m_Z(i_Z), m_W(i_W) {

	}

	inline Vector4::Vector4(const Vector4& i_Other) :
		m_X(i_Other.m_X),
		m_Y(i_Other.m_Y),
		m_Z(i_Other.m_Z),
		m_W(i_Other.m_W)
	{
		
	}

	inline float Vector4::X() const { return m_X; }
	inline float Vector4::Y() const { return m_Y; }
	inline float Vector4::Z() const { return m_Z; }
	inline float Vector4::W() const { return m_W; }

	inline void Vector4::X(float i_X) {
		m_X = i_X;
	}
	inline void Vector4::Y(float i_Y) {
		m_Y = i_Y;
	}
	inline void Vector4::Z(float i_Z) {
		m_Z = i_Z;
	}
	inline void Vector4::W(float i_W) {
		m_W = i_W;
	}

	inline Vector4& Vector4::operator=(const Vector4& i_Other) {
		
		m_X = i_Other.m_X;
		m_Y = i_Other.m_Y;
		m_Z = i_Other.m_Z;
		m_W = i_Other.m_W;

		return *this;
	}

	inline float Vector4::dot(const Vector4& i_lhs, const Vector4& i_rhs) {

		//return i_lhs.m_X * i_rhs.m_X + i_lhs.m_Y * i_rhs.m_Y + i_lhs.m_Z * i_rhs.m_Z + i_lhs.m_W * i_rhs.m_W;
	
		__m128 vec0 = { i_lhs.X(), i_lhs.Y(), i_lhs.Z(), 0.0 };
		__m128 vec1 = { i_rhs.X(), i_rhs.Y(), i_rhs.Z(), 0.0 };

		// do the dot product of the first 3 components – the 7 part of 0x71
		// output result to only lower float of output  - the 1 part of 0x71
		__m128 vec2 = _mm_dp_ps(vec0, vec1, 0x71);

		float dot = _mm_cvtss_f32(vec2);

		return dot + i_lhs.W() * i_rhs.W();
	}
}