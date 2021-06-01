#pragma once

// 3x3 행렬 사용 위해 만든 클래스
class CMatrix3x3
{
public:
	 CMatrix3x3();
	 CMatrix3x3(
		  float m11, float m12, float m13,
		  float m21, float m22, float m23,
		  float m31, float m32, float m33);
	 ~CMatrix3x3();

	 // 초기값을 0으로 채워 넣음
	 float m_matrix[3][3] = { 0, };

	 CMatrix3x3 operator+(const CMatrix3x3& mat);
	 CMatrix3x3 operator-(const CMatrix3x3& mat);
	 CMatrix3x3 operator*(const float& k);
	 CMatrix3x3 operator*(const CMatrix3x3& mat);
};

