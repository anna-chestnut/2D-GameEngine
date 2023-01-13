#pragma once

#include<conio.h> 
#include <iostream>

namespace Engine {
	class Point2D {

	public:
		Point2D();
		Point2D(int i_X, int i_Y);
		~Point2D();

		//get
		int X();
		int Y();
		//set
		void X(int i_X);
		void Y(int i_Y);

		bool operator==(const Point2D& i_Other);
		bool operator!=(const Point2D& i_Other);
		Point2D operator+(const Point2D& i_Other);
		Point2D operator-(const Point2D& i_Other);
		Point2D operator*(const int i_Other);
		Point2D operator/(const int i_Other);
		Point2D operator-();
		Point2D operator-=(const Point2D& i_Other);
		Point2D operator+=(const Point2D& i_Other);
		Point2D operator*=(const int i_Other);
		Point2D operator/=(const int i_Other);
	private:
		int m_X;
		int m_Y;

	};
	Point2D operator*(const int i_Other, const Point2D& i_pOther);
}
