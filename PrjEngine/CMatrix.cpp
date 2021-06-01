#include "pch.h"

CMatrix3x3::CMatrix3x3()
{
}

CMatrix3x3::CMatrix3x3(float m11, float m12, float m13,
	 float m21, float m22, float m23,
	 float m31, float m32, float m33)
{
	 m_matrix[0][0] = m11; m_matrix[0][1] = m12; m_matrix[0][2] = m13;
	 m_matrix[1][0] = m21; m_matrix[1][1] = m22; m_matrix[1][2] = m23;
	 m_matrix[2][0] = m31; m_matrix[2][1] = m32; m_matrix[2][2] = m33;
}

CMatrix3x3::~CMatrix3x3()
{
}

CMatrix3x3 CMatrix3x3::operator+(const CMatrix3x3& mat)
{
	 CMatrix3x3 matResult;

	 for (int y = 0; y < 3; y++)
	 {
		  for (int x = 0; x < 3; x++)
		  {
				matResult.m_matrix[y][x] = m_matrix[y][x] + mat.m_matrix[y][x];
		  }
	 }

	 return matResult;
}

CMatrix3x3 CMatrix3x3::operator-(const CMatrix3x3& mat)
{
	 CMatrix3x3 matResult;

	 for (int y = 0; y < 3; y++)
	 {
		  for (int x = 0; x < 3; x++)
		  {
				matResult.m_matrix[y][x] = m_matrix[y][x] - mat.m_matrix[y][x];
		  }
	 }

	 return matResult;
}

CMatrix3x3 CMatrix3x3::operator*(const float& k)
{
	 CMatrix3x3 matResult;

	 for (int y = 0; y < 3; y++)
	 {
		  for (int x = 0; x < 3; x++)
		  {
				matResult.m_matrix[y][x] = k * m_matrix[y][x];
		  }
	 }

	 return matResult;
}

CMatrix3x3 CMatrix3x3::operator*(const CMatrix3x3& mat)
{
	 CMatrix3x3 matResult;

	 for (int y = 0; y < 3; y++)
	 {
		  for (int x = 0; x < 3; x++)
		  {
				for (int i = 0; i < 3; i++)
				{
					 //[0][0]*mat.[0][0] + [0][1]*mat.[1][0] + [0][2]*mat.[2][0]
					 matResult.m_matrix[y][x] = m_matrix[y][i] * mat.m_matrix[i][x];
				}
		  }
	 }

	 return matResult;
}
