#pragma once

#include<conio.h> 
#include <assert.h>
#include <iostream>
#include <smmintrin.h> 

namespace Engine {

	const size_t DIMENSION = 4;

	class Vector4 {

	public:
		Vector4();
		inline Vector4(float i_X, float i_Y, float i_Z, float i_W);
		~Vector4();

		inline Vector4(const Vector4& i_Other);

		//get
		inline float X() const;
		inline float Y() const;
		inline float Z() const;
		inline float W() const;
		//set
		inline void X(float i_X);
		inline void Y(float i_Y);
		inline void Z(float i_Z);
		inline void W(float i_W);

		bool operator==(const Vector4& i_Other);
		bool operator!=(const Vector4& i_Other);
		Vector4 operator+(const Vector4& i_Other);
		Vector4 operator-(const Vector4& i_Other);
		Vector4 operator*(const float i_Other);
		Vector4 operator/(const float i_Other);
		Vector4 operator-();
		Vector4 operator-=(const Vector4& i_Other);
		Vector4 operator+=(const Vector4& i_Other);
		Vector4 operator*=(const float i_Other);
		Vector4 operator/=(const float i_Other);
		
		//assignment operator
		inline Vector4& operator=(const Vector4& i_other);

		inline static float dot(const Vector4& i_lhs, const Vector4& i_rhs);
		float At(size_t i_index) const;
		void SetValueAt(size_t index, float value);
		Vector4 Normalize();
		float Length();

	private:
		float m_X;
		float m_Y;
		float m_Z;
		float m_W;

	};
	Vector4 operator*(const float i_Other, const Vector4& i_pOther);
}

#include "Vector4.inl"