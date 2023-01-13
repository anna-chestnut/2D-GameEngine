#include "Vector3.h"

namespace Engine {

	Vector3::Vector3() {
		m_X = 0;
		m_Y = 0;
		m_Z = 0;
	}
	
	/*Vector3::Vector3(const __m128 i_vec) :
		m_vec(i_vec)
	{}*/

	float Vector3::X() const { return m_X; }
	float Vector3::Y() const { return m_Y; }
	float Vector3::Z() const { return m_Z; }

	void Vector3::X(float i_X) {
		m_X = i_X;
	}
	void Vector3::Y(float i_Y) {
		m_Y = i_Y;
	}
	void Vector3::Z(float i_Z) {
		m_Z = i_Z;
	}

	bool Vector3::operator==(const Vector3& i_Other) {
		return (m_X == i_Other.m_X) && (m_Y == i_Other.m_Y) && (m_Z == i_Other.m_Z);
	}

	bool Vector3::operator!=(const Vector3& i_Other) {
		return (m_X != i_Other.m_X) || (m_Y != i_Other.m_Y) || (m_Z != i_Other.m_Z);
	}

	Vector3 Vector3::operator+(const Vector3& i_Other) {
		return Vector3(m_X + i_Other.m_X, m_Y + i_Other.m_Y, m_Z + i_Other.m_Z);
	}

	Vector3 Vector3::operator-(const Vector3& i_Other) {
		return Vector3(m_X - i_Other.m_X, m_Y - i_Other.m_Y, m_Z - i_Other.m_Z);
	}

	Vector3 Vector3::operator*(const float i_Other) {
		return Vector3(m_X * i_Other, m_Y * i_Other, m_Z * i_Other);
	}

	Vector3 Vector3::operator/(const float i_Other) {
		return Vector3(m_X / i_Other, m_Y / i_Other, m_Z / i_Other);
	}

	Vector3 Vector3::operator-() {
		return Vector3(-m_X, -m_Y, -m_Z);
	}


	Vector3 Vector3::operator-=(const Vector3& i_Other) {
		this->m_X -= i_Other.m_X;
		this->m_Y -= i_Other.m_Y;
		this->m_Z -= i_Other.m_Z;
		return *this;
	}

	Vector3 Vector3::operator+=(const Vector3& i_Other) {
		this->m_X += i_Other.m_X;
		this->m_Y += i_Other.m_Y;
		this->m_Z += i_Other.m_Z;
		return *this;
	}

	Vector3 Vector3::operator*=(const float i_Other) {
		this->m_X *= i_Other;
		this->m_Y *= i_Other;
		this->m_Z *= i_Other;
		return *this;
	}

	Vector3 Vector3::operator/=(const float i_Other) {
		this->m_X /= i_Other;
		this->m_Y /= i_Other;
		this->m_Z /= i_Other;
		return *this;
	}

	Vector3  operator*(const float i_Other, const Vector3& i_pOther) {
		Vector3 p = i_pOther;
		float x = p.X();
		float y = p.Y();
		float z = p.Z();
		return Vector3(i_Other * x, i_Other * y, i_Other * z);
	}

	float Vector3::Length() {
		return sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
	}
}