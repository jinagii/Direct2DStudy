#pragma once

// ������ �뵵�� ���͸� ����ϱ� ���� Ŭ����
class CVector
{
public:
	CVector();
	CVector(float x, float y);
	~CVector();

	float x;
	float y;

	// ������ �����ε�
	CVector operator+(const CVector& vec);
	CVector operator-(const CVector& vec);
	CVector operator*(const float& k); // ��� ��
	CVector operator/(const float& k); // ��� ������

	float GetVectorMagnitude(); // ���� ũ��
};

