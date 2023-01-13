#pragma once
#include <array>
#include <math.h>
#include "Vector4.h"
#include "Vector3.h"

namespace Engine {


	class Matrix {
	public:
		Matrix();
		Matrix(float i_00, float i_01, float i_02, float i_03,
			float i_10, float i_11, float i_12, float i_13,
			float i_20, float i_21, float i_22, float i_23,
			float i_30, float i_31, float i_32, float i_33);
		~Matrix();

		// copy constructor & assignment operator
		Matrix(const Matrix &i_other);
		Matrix& operator=(const Matrix& i_other);

		// Useful matrix creators
		static Matrix CreateIdentity(void);
		static Matrix CreateXRotation(float i_degree);
		static Matrix CreateYRotation(float i_degree);
		static Matrix CreateZRotation(float i_degree);

		static Matrix CreateTranslation(Vector3 i_trans);
		static Matrix CreateTranslation(float i_x, float i_y, float i_z);
		static Matrix CreateScale(float i_x, float i_y, float i_z);

		// Invert this instance
		void Invert(void);
		// Return a matrix that is the inverse of this instance but don't modify this instancce
		Matrix GetInverse(void) const;

		// Transpose this instance
		void Transpose(void);
		// return a matrix that is a transpose of this instance but don't modify this instance
		Matrix GetTranspose(void) const;

		// Multiply Matrix * Matrix
		// return *this * i_other
		Matrix operator*(const Matrix& i_other) const;

		// Multiply Vector by Matrix
		// return v * M
		Vector4 MultiplyLeft(const Vector4& i_Vector);
		// return M * v
		Vector4 MultiplyRight(const Vector4& i_Vector);

		bool operator==(const Matrix& i_rhs) const;

		void SetVectorVelue(const size_t i_row, const size_t i_col, float value);

		Vector4 Row(size_t i_row) const;

		Vector4 Col(size_t i_col) const;

		float FindDeterminant() const;
		float threeDeterminant(float i_00, float i_01, float i_02, float i_10, float i_11, float i_12, float i_20, float i_21, float i_22) const;
		Matrix GetAdjugateMat() const;

		// v = M * i_u;
		Vector4 operator*(const Vector4& i_u);

		Matrix operator*(float i_u);

	private:
		std::array<Vector4, DIMENSION> m_rows;
	};
}