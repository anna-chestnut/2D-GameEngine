#pragma once
#include "Vector3.h"
namespace Engine {

	inline Vector3::Vector3(float i_X, float i_Y, float i_Z) : m_X(i_X), m_Y(i_Y), m_Z(i_Z) {
	}
	inline Vector3::~Vector3() {
	}

	// operators
	inline Vector3& Vector3::operator=(const Vector3& i_rhs)
	{
		m_X = i_rhs.m_X;
		m_Y = i_rhs.m_Y;
		m_Z = i_rhs.m_Z;

		return *this;
	}

	inline float dot(const Vector3& i_lhs, const Vector3& i_rhs)
	{
		__m128 vec0 = { i_lhs.X(), i_lhs.Y(), i_lhs.Z(), 0.0f };
		__m128 vec1 = { i_rhs.X(), i_rhs.Y(), i_rhs.Z(), 0.0f };

		// do the dot product of the first 3 components – the 7 part of 0x71
		// output result to only lower float of output  - the 1 part of 0x71
		__m128 vec2 = _mm_dp_ps(vec0, vec1, 0x71);

		float dot = _mm_cvtss_f32(vec2);

		return dot;

	}

	inline Vector3 cross(const Vector3& i_lhs, const Vector3& i_rhs)
	{
		return Vector3(i_lhs.Y() * i_rhs.Z() - i_lhs.Z() * i_rhs.Y(),
			i_lhs.Z() * i_rhs.X() - i_lhs.X() * i_rhs.Z(),
			i_lhs.X() * i_rhs.Y() - i_lhs.Y() * i_rhs.X());
		//__m128 v1 = { i_lhs.X(), i_lhs.Y(), i_lhs.Z(), 0.0f };
		//__m128 v2 = { i_rhs.X(), i_rhs.Y(), i_rhs.Z(), 0.0f };

		//// v1 cross v2
		//__m128	v1_swiz_op1 = _mm_shuffle_ps(v1, v1, _MM_SHUFFLE(3, 0, 2, 1));
		//__m128	v2_swiz_op1 = _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(3, 1, 0, 2));

		//__m128	v1_swiz_op2 = _mm_shuffle_ps(v1, v1, _MM_SHUFFLE(3, 1, 0, 2));
		//__m128	v2_swiz_op2 = _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(3, 0, 2, 1));

		//__m128	cross_op1 = _mm_mul_ps(v1_swiz_op1, v2_swiz_op1);
		//__m128	cross_op2 = _mm_mul_ps(v1_swiz_op2, v2_swiz_op2);

		//return Vector3(_mm_sub_ps(cross_op1, cross_op2));

		/*return Vector3(_mm_sub_ps(
			_mm_mul_ps(_mm_shuffle_ps(v1, v1, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(3, 1, 0, 2))),

			_mm_mul_ps(_mm_shuffle_ps(v1, v1, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(3, 0, 2, 1)))
		));*/

	}
}
