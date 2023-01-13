#pragma once

#include<conio.h> 
#include <iostream>
#include <smmintrin.h> 

namespace Engine {
	class Vector3 {

	public:
		Vector3();
		//Vector3(const __m128 i_vec);
		inline Vector3(float i_X, float i_Y, float i_Z);
		inline ~Vector3();

		//get
		float X() const;
		float Y() const;
		float Z() const;
		//set
		void X(float i_X);
		void Y(float i_Y);
		void Z(float i_Z);

		// assignment operator
		inline Vector3& operator=(const Vector3& i_rhs);

		bool operator==(const Vector3& i_Other);
		bool operator!=(const Vector3& i_Other);
		Vector3 operator+(const Vector3& i_Other);
		Vector3 operator-(const Vector3& i_Other);
		Vector3 operator*(const float i_Other);
		Vector3 operator/(const float i_Other);
		Vector3 operator-();
		Vector3 operator-=(const Vector3& i_Other);
		Vector3 operator+=(const Vector3& i_Other);
		Vector3 operator*=(const float i_Other);
		Vector3 operator/=(const float i_Other);

		float Length();
	private:
		float m_X;
		float m_Y;
		float m_Z;
		//__m128 	m_vec;
	};

	Vector3 operator*(const float i_Other, const Vector3& i_pOther);

	inline float dot(const Vector3& i_lhs, const Vector3& i_rhs);
	inline Vector3 cross(const Vector3& i_lhs, const Vector3& i_rhs);
}


#include "Vector3.inl"