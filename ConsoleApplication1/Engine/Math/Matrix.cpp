#include "Matrix.h"

namespace Engine {

	Matrix::Matrix() : m_rows({ Vector4(0, 0, 0, 0),
			Vector4(0, 0, 0, 0),
			Vector4(0, 0, 0, 0),
			Vector4(0, 0, 0, 0) }) {

	}
	Matrix::Matrix(
		float i_00, float i_01, float i_02, float i_03,
		float i_10, float i_11, float i_12, float i_13,
		float i_20, float i_21, float i_22, float i_23,
		float i_30, float i_31, float i_32, float i_33) :
		m_rows({ Vector4(i_00, i_01, i_02, i_03),
			Vector4(i_10, i_11, i_12, i_13),
			Vector4(i_20, i_21, i_22, i_23),
			Vector4(i_30, i_31, i_32, i_33) })
	{

	}

	Matrix::Matrix(const Matrix& i_other) {
		m_rows[0] = i_other.m_rows[0];
		m_rows[1] = i_other.m_rows[1];
		m_rows[2] = i_other.m_rows[2];
		m_rows[3] = i_other.m_rows[3];
	}

	Matrix::~Matrix() {

	}

	Matrix& Matrix::operator=(const Matrix& i_other) {

		m_rows[0] = i_other.Row(0);
		m_rows[1] = i_other.Row(1);
		m_rows[2] = i_other.Row(2);
		m_rows[3] = i_other.Row(3);

		return *this;
	}

	Matrix Matrix::CreateIdentity(void) {

		Matrix indentityMat;
		indentityMat.m_rows[0] = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
		indentityMat.m_rows[1] = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
		indentityMat.m_rows[2] = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
		indentityMat.m_rows[3] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

		return indentityMat;
	}

	Matrix Matrix::CreateXRotation(float i_degree) {

		return Matrix(
			1, 0, 0, 0,
			0, cos(i_degree), -sin(i_degree), 0,
			0, sin(i_degree), cos(i_degree), 0,
			0, 0, 0, 1
		);
	}

	Matrix Matrix::CreateYRotation(float i_degree) {

		return Matrix(
			cos(i_degree), 0, sin(i_degree), 0,
			0, 1, 0, 0,
			-sin(i_degree), 0, cos(i_degree), 0,
			0, 0, 0, 1
		);
	}

	Matrix Matrix::CreateZRotation(float i_degree) {

		return Matrix(
			cos(i_degree), -sin(i_degree), 0, 0,
			sin(i_degree), cos(i_degree), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}


	Matrix Matrix::CreateTranslation(Vector3 i_trans) {
		Matrix transMat;
		transMat = CreateIdentity();
		transMat.SetVectorVelue(0, 3, i_trans.X());
		transMat.SetVectorVelue(1, 3, i_trans.Y());
		transMat.SetVectorVelue(2, 3, i_trans.Z());
		return transMat;
	}

	Matrix Matrix::CreateTranslation(float i_x, float i_y, float i_z) {
		Matrix transMat;
		transMat.CreateIdentity();
		transMat.SetVectorVelue(0, 3, i_x);
		transMat.SetVectorVelue(1, 3, i_y);
		transMat.SetVectorVelue(2, 3, i_z);
		return transMat;
	}

	Matrix Matrix::CreateScale(float i_x, float i_y, float i_z) {
		
		Matrix scaleMat;
		scaleMat.CreateIdentity();
		scaleMat.SetVectorVelue(0, 0, i_x);
		scaleMat.SetVectorVelue(1, 1, i_y);
		scaleMat.SetVectorVelue(2, 2, i_z);

		return scaleMat;
	}

	void Matrix::SetVectorVelue(const size_t i_row, const size_t i_col, float value) {
		assert(i_col < DIMENSION&& i_col >= 0);
		assert(i_row < DIMENSION&& i_row >= 0);

		switch (i_col)
		{
		case 0:
			m_rows[i_row].X(value);
			break;
		case 1:
			m_rows[i_row].Y(value);
			break;
		case 2:
			m_rows[i_row].Z(value);
			break;
		case 3:
			m_rows[i_row].W(value);
			break;
		default:
			break;
		}
	}

	void Matrix::Invert(void) {
		float determinant = FindDeterminant();
		Matrix adjugateMat = GetAdjugateMat();
		
		Matrix inverseMatrix = adjugateMat * (1 / determinant);
		m_rows[0] = inverseMatrix.Row(0);
		m_rows[1] = inverseMatrix.Row(1);
		m_rows[2] = inverseMatrix.Row(2);
		m_rows[3] = inverseMatrix.Row(3);
	}

	Matrix Matrix::GetInverse(void) const{

		float determinant = FindDeterminant();
		Matrix adjugateMat = GetAdjugateMat();



		return adjugateMat * (1 / determinant);
	}

	void Matrix::Transpose(void) {

		for (size_t i = 0; i < DIMENSION - 1; i++) {
			for (size_t j = i + 1; j < DIMENSION; j++) {
				float tmp = m_rows[i].At(j);
				m_rows[i].SetValueAt(j, m_rows[j].At(i));
				m_rows[j].SetValueAt(i, tmp);
			}
		}
	}

	Matrix Matrix::GetTranspose(void) const {

		Matrix transposeMat;
		for (size_t i = 0; i < DIMENSION - 1; i++) {
			for (size_t j = i + 1; j < DIMENSION; j++) {
				transposeMat.Row(i).SetValueAt(j, m_rows[j].At(i));
			}
		}

		return transposeMat;
	}

	Matrix Matrix::operator*(const Matrix& i_other) const {

		return Matrix(
			Vector4::dot(m_rows[0], i_other.Col(0)), Vector4::dot(m_rows[0], i_other.Col(1)), Vector4::dot(m_rows[0], i_other.Col(2)), Vector4::dot(m_rows[0], i_other.Col(3)),
			Vector4::dot(m_rows[1], i_other.Col(0)), Vector4::dot(m_rows[1], i_other.Col(1)), Vector4::dot(m_rows[1], i_other.Col(2)), Vector4::dot(m_rows[1], i_other.Col(3)),
			Vector4::dot(m_rows[2], i_other.Col(0)), Vector4::dot(m_rows[2], i_other.Col(1)), Vector4::dot(m_rows[2], i_other.Col(2)), Vector4::dot(m_rows[2], i_other.Col(3)),
			Vector4::dot(m_rows[3], i_other.Col(0)), Vector4::dot(m_rows[3], i_other.Col(1)), Vector4::dot(m_rows[3], i_other.Col(2)), Vector4::dot(m_rows[3], i_other.Col(3))
		);
		
	}

	// return v * M
	Vector4 Matrix::MultiplyLeft(const Vector4& i_Vector) {
		return Vector4(Vector4::dot(Col(0), i_Vector), Vector4::dot(Col(1), i_Vector), Vector4::dot(Col(2), i_Vector), Vector4::dot(Col(3), i_Vector));
	}
	// return M * v
	Vector4 Matrix::MultiplyRight(const Vector4& i_Vector) {
		return Vector4(Vector4::dot(m_rows[0], i_Vector), Vector4::dot(m_rows[1], i_Vector), Vector4::dot(m_rows[2], i_Vector), Vector4::dot(m_rows[3], i_Vector));
	}

	bool Matrix::operator==(const Matrix& i_rhs) const{

		for (size_t i = 0; i < DIMENSION - 1; i++) {
			for (size_t j = 0; j < DIMENSION; j++) {
				if (m_rows[i].At(j) != i_rhs.m_rows[i].At(j))
					return false;
			}
		}

		return true;
	}

	float Matrix::FindDeterminant() const {
		return m_rows[0].X() * threeDeterminant(
			m_rows[1].Y(), m_rows[1].Z(), m_rows[1].W(),
			m_rows[2].Y(), m_rows[2].Z(), m_rows[2].W(),
			m_rows[3].Y(), m_rows[3].Z(), m_rows[3].W()
		) - m_rows[1].X() * threeDeterminant(
			m_rows[0].Y(), m_rows[0].Z(), m_rows[0].W(),
			m_rows[2].Y(), m_rows[2].Z(), m_rows[2].W(),
			m_rows[3].Y(), m_rows[3].Z(), m_rows[3].W()
		) + m_rows[2].X() * threeDeterminant(
			m_rows[0].Y(), m_rows[0].Z(), m_rows[0].W(),
			m_rows[1].Y(), m_rows[1].Z(), m_rows[1].W(),
			m_rows[3].Y(), m_rows[3].Z(), m_rows[3].W()
		) - m_rows[3].X() * threeDeterminant(
			m_rows[0].Y(), m_rows[0].Z(), m_rows[0].W(),
			m_rows[1].Y(), m_rows[1].Z(), m_rows[1].W(),
			m_rows[2].Y(), m_rows[2].Z(), m_rows[2].W()
		);
	}

	float Matrix::threeDeterminant(float i_00, float i_01, float i_02, float i_10, float i_11, float i_12, float i_20, float i_21, float i_22) const {
		return i_00 * (i_11 * i_22 - i_21 * i_12) - i_10 * (i_01 * i_22 - i_21 * i_02) + i_20 * (i_01 * i_12 - i_11 * i_02);
	}

	Matrix Matrix::GetAdjugateMat() const {
		return Matrix(

			// row 0
			// -----
			
			//M11
			threeDeterminant(
				m_rows[1].Y(), m_rows[1].Z(), m_rows[1].W(),
				m_rows[2].Y(), m_rows[2].Z(), m_rows[2].W(),
				m_rows[3].Y(), m_rows[3].Z(), m_rows[3].W()
			),
			//M21
			-threeDeterminant(
				m_rows[0].Y(), m_rows[0].Z(), m_rows[0].W(),
				m_rows[2].Y(), m_rows[2].Z(), m_rows[2].W(),
				m_rows[3].Y(), m_rows[3].Z(), m_rows[3].W()
			),
			//M31
			threeDeterminant(
				m_rows[0].Y(), m_rows[0].Z(), m_rows[0].W(),
				m_rows[1].Y(), m_rows[1].Z(), m_rows[1].W(),
				m_rows[3].Y(), m_rows[3].Z(), m_rows[3].W()
			),
			//M41
			-threeDeterminant(
				m_rows[0].Y(), m_rows[0].Z(), m_rows[0].W(),
				m_rows[1].Y(), m_rows[1].Z(), m_rows[1].W(),
				m_rows[2].Y(), m_rows[2].Z(), m_rows[2].W()
			),

			
			// row 1
			// -----
			
			//M12
			-threeDeterminant(
				m_rows[1].X(), m_rows[1].Z(), m_rows[1].W(),
				m_rows[2].X(), m_rows[2].Z(), m_rows[2].W(),
				m_rows[3].X(), m_rows[3].Z(), m_rows[3].W()
			),
			
			//M22
			threeDeterminant(
				m_rows[0].X(), m_rows[0].Z(), m_rows[0].W(),
				m_rows[2].X(), m_rows[2].Z(), m_rows[2].W(),
				m_rows[3].X(), m_rows[3].Z(), m_rows[3].W()
			),

			//M32
			-threeDeterminant(
				m_rows[0].X(), m_rows[0].Z(), m_rows[0].W(),
				m_rows[1].X(), m_rows[1].Z(), m_rows[1].W(),
				m_rows[3].X(), m_rows[3].Z(), m_rows[3].W()
			),

			//M42
			threeDeterminant(
				m_rows[0].X(), m_rows[0].Z(), m_rows[0].W(),
				m_rows[1].X(), m_rows[1].Z(), m_rows[1].W(),
				m_rows[2].X(), m_rows[2].Z(), m_rows[2].W()
			),

			// row 2
			// -----

			//M13
			threeDeterminant(
				m_rows[1].X(), m_rows[1].Y(), m_rows[1].W(),
				m_rows[2].X(), m_rows[2].Y(), m_rows[2].W(),
				m_rows[3].X(), m_rows[3].Y(), m_rows[3].W()
			),

			//M23
			-threeDeterminant(
				m_rows[0].X(), m_rows[0].Y(), m_rows[0].W(),
				m_rows[2].X(), m_rows[2].Y(), m_rows[2].W(),
				m_rows[3].X(), m_rows[3].Y(), m_rows[3].W()
			),

			//M33
			threeDeterminant(
				m_rows[0].X(), m_rows[0].Y(), m_rows[0].W(),
				m_rows[1].X(), m_rows[1].Y(), m_rows[1].W(),
				m_rows[3].X(), m_rows[3].Y(), m_rows[3].W()
			),

			//M43
			-threeDeterminant(
				m_rows[0].X(), m_rows[0].Y(), m_rows[0].W(),
				m_rows[1].X(), m_rows[1].Y(), m_rows[1].W(),
				m_rows[2].X(), m_rows[2].Y(), m_rows[2].W()
			),


			// row 3
			// -----

			//M14
			-threeDeterminant(
					m_rows[1].X(), m_rows[1].Y(), m_rows[1].Z(),
					m_rows[2].X(), m_rows[2].Y(), m_rows[2].Z(),
					m_rows[3].X(), m_rows[3].Y(), m_rows[3].Z()
				),

			//M24
			threeDeterminant(
				m_rows[0].X(), m_rows[0].Y(), m_rows[0].Z(),
				m_rows[2].X(), m_rows[2].Y(), m_rows[2].Z(),
				m_rows[3].X(), m_rows[3].Y(), m_rows[3].Z()
			),
			
			//M34
			-threeDeterminant(
				m_rows[0].X(), m_rows[0].Y(), m_rows[0].Z(),
				m_rows[1].X(), m_rows[1].Y(), m_rows[1].Z(),
				m_rows[3].X(), m_rows[3].Y(), m_rows[3].Z()
			),

			//M44
			threeDeterminant(
				m_rows[0].X(), m_rows[0].Y(), m_rows[0].Z(),
				m_rows[1].X(), m_rows[1].Y(), m_rows[1].Z(),
				m_rows[2].X(), m_rows[2].Y(), m_rows[2].Z()
			)
		);
	}

	Vector4 Matrix::Row(size_t i_row) const {
		assert(i_row < DIMENSION&& i_row >= 0);
		return m_rows[i_row];
	}

	Vector4 Matrix::Col(size_t i_col) const {
		assert(i_col < DIMENSION && i_col >= 0);
		return Vector4(m_rows[0].At(i_col), m_rows[1].At(i_col), m_rows[2].At(i_col), m_rows[3].At(i_col));
	}

	Vector4 Matrix::operator*(const Vector4& i_u) {
		
		return Vector4(
			Vector4::dot(Row(0), i_u),
			Vector4::dot(Row(1), i_u),
			Vector4::dot(Row(2), i_u),
			Vector4::dot(Row(3), i_u)
		);
	}

	Matrix Matrix::operator*(float i_u) {

		for (size_t i = 0; i < DIMENSION; i++) {
			for (size_t j = 0; j < DIMENSION; j++) {
				m_rows[i].SetValueAt(j, m_rows[i].At(j) * i_u);
			}
		}

		return *this;
	}

	
}