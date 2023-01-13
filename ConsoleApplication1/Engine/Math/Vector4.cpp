#include "Vector4.h"

namespace Engine {

	Vector4::Vector4() {
		m_X = 0;
		m_Y = 0;
		m_Z = 0;
		m_W = 0;
	}
	
	Vector4::~Vector4() {
	}

	
	bool Vector4::operator==(const Vector4& i_Other) {
		return (m_X == i_Other.m_X) && (m_Y == i_Other.m_Y) && (m_Z == i_Other.m_Z) && (m_W == i_Other.m_W);
	}

	bool Vector4::operator!=(const Vector4& i_Other) {
		return (m_X != i_Other.m_X) || (m_Y != i_Other.m_Y) || (m_Z != i_Other.m_Z) || (m_W != i_Other.m_W);
	}

	Vector4 Vector4::operator+(const Vector4& i_Other) {
		return Vector4(m_X + i_Other.m_X, m_Y + i_Other.m_Y, m_Z + i_Other.m_Z, m_W + i_Other.m_W);
	}

	Vector4 Vector4::operator-(const Vector4& i_Other) {
		return Vector4(m_X - i_Other.m_X, m_Y - i_Other.m_Y, m_Z - i_Other.m_Z, m_W - i_Other.m_W);
	}

	Vector4 Vector4::operator*(const float i_Other) {
		return Vector4(m_X * i_Other, m_Y * i_Other, m_Z * i_Other, m_W * i_Other);
	}

	Vector4 Vector4::operator/(const float i_Other) {
		return Vector4(m_X / i_Other, m_Y / i_Other, m_Z / i_Other, m_W / i_Other);
	}

	Vector4 Vector4::operator-() {
		return Vector4(-m_X, -m_Y, -m_Z, -m_W);
	}


	Vector4 Vector4::operator-=(const Vector4& i_Other) {
		this->m_X -= i_Other.m_X;
		this->m_Y -= i_Other.m_Y;
		this->m_Z -= i_Other.m_Z;
		this->m_W -= i_Other.m_W;
		return *this;
	}

	Vector4 Vector4::operator+=(const Vector4& i_Other) {
		this->m_X += i_Other.m_X;
		this->m_Y += i_Other.m_Y;
		this->m_Z += i_Other.m_Z;
		this->m_W += i_Other.m_W;
		return *this;
	}

	Vector4 Vector4::operator*=(const float i_Other) {
		//assert(!IsNAN(i_Other));

		this->m_X *= i_Other;
		this->m_Y *= i_Other;
		this->m_Z *= i_Other;
		this->m_W *= i_Other;
		return *this;
	}

	Vector4 Vector4::operator/=(const float i_Other) {

		//assert(!IsNAN(i_Other));

		this->m_X /= i_Other;
		this->m_Y /= i_Other;
		this->m_Z /= i_Other;
		this->m_W /= i_Other;
		return *this;
	}


	

	/*float Vector4::dot(const Vector4& i_lhs, const Vector4& i_rhs) {
		return i_lhs.m_X * i_rhs.m_X + i_lhs.m_Y * i_rhs.m_Y + i_lhs.m_Z * i_rhs.m_Z + i_lhs.m_W * i_rhs.m_W;
	}*/

	float Vector4::At(size_t i_index) const {
		assert(i_index < DIMENSION && i_index >= 0);
		return i_index == 0 ? m_X : i_index == 1 ? m_Y : i_index == 2 ? m_Z : m_W;
	}

	void Vector4::SetValueAt(size_t i_index, float value) {

		assert(i_index < DIMENSION && i_index >= 0);
		
		if (i_index == 0)
			X(value);
		else if (i_index == 1)
			Y(value);
		else if (i_index == 2)
			Z(value);
		else
			W(value);
	}

	Vector4  operator*(const float i_Other, const Vector4& i_pOther) {
		Vector4 p = i_pOther;
		float x = p.X();
		float y = p.Y();
		float z = p.Z();
		float w = p.W();
		return Vector4(i_Other * x, i_Other * y, i_Other * z, i_Other * w);
	}

	float Vector4::Length() {
		return sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W * m_W);
	}

	Vector4 Vector4::Normalize() {

		float length = Length();
		return Vector4(m_X / length, m_Y / length, m_Z / length, m_W / length);
	}

}