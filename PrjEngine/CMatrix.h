#pragma once

// 3x3 ��� ��� ���� ���� Ŭ����
class CMatrix3x3
{
public:
	 CMatrix3x3();
	 CMatrix3x3(
		  float m11, float m12, float m13,
		  float m21, float m22, float m23,
		  float m31, float m32, float m33);
	 ~CMatrix3x3();

	 // �ʱⰪ�� 0���� ä�� ����
	 float m_matrix[3][3] = { 0, };

	 CMatrix3x3 operator+(const CMatrix3x3& mat);
	 CMatrix3x3 operator-(const CMatrix3x3& mat);
	 CMatrix3x3 operator*(const float& k);
	 CMatrix3x3 operator*(const CMatrix3x3& mat);
};

