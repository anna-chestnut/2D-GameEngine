#include "Point2D.h"

namespace Engine {

	Point2D::Point2D(){
		m_X = 0;
		m_Y = 0;
	}
	Point2D::Point2D(int i_X, int i_Y) : m_X(i_X), m_Y(i_Y) {
	}
	Point2D::~Point2D() {
	}

	int Point2D::X() { return m_X; }
	int Point2D::Y() { return m_Y; }

	void Point2D::X(int i_X) {
		m_X = i_X;
	}
	void Point2D::Y(int i_Y) {
		m_Y = i_Y;
	}

	bool Point2D::operator==(const Point2D& i_Other) {
		return (m_X == i_Other.m_X) && (m_Y == i_Other.m_Y);
	}

	bool Point2D::operator!=(const Point2D& i_Other) {
		return (m_X != i_Other.m_X) || (m_Y != i_Other.m_Y);
	}

	Point2D Point2D::operator+(const Point2D& i_Other) {
		return Point2D(m_X + i_Other.m_X, m_Y + i_Other.m_Y);
	}

	Point2D Point2D::operator-(const Point2D& i_Other) {
		return Point2D(m_X - i_Other.m_X, m_Y - i_Other.m_Y);
	}

	Point2D Point2D::operator*(const int i_Other) {
		return Point2D(m_X * i_Other, m_Y * i_Other);
	}

	Point2D Point2D::operator/(const int i_Other) {
		return Point2D(m_X / i_Other, m_Y / i_Other);
	}

	Point2D Point2D::operator-() {
		return Point2D(-m_X, -m_Y);
	}


	Point2D Point2D::operator-=(const Point2D& i_Other) {
		this->m_X -= i_Other.m_X;
		this->m_Y -= i_Other.m_Y;
		return *this;
	}

	Point2D Point2D::operator+=(const Point2D& i_Other) {
		this->m_X += i_Other.m_X;
		this->m_Y += i_Other.m_Y;
		return *this;
	}

	Point2D Point2D::operator*=(const int i_Other) {
		this->m_X *= i_Other;
		this->m_Y *= i_Other;
		return *this;
	}

	Point2D Point2D::operator/=(const int i_Other) {
		this->m_X /= i_Other;
		this->m_Y /= i_Other;
		return *this;
	}

	Point2D  operator*(const int i_Other, const Point2D& i_pOther) {
		Point2D p = i_pOther;
		int x = p.X();
		int y = p.Y();
		return Point2D(i_Other * x, i_Other * y);
	}
}