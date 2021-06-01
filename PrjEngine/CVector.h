#pragma once

// 물리적 용도로 벡터를 사용하기 위한 클래스
class CVector
{
public:
	CVector();
	CVector(float x, float y);
	~CVector();

	float x;
	float y;

	// 연산자 오버로딩
	CVector operator+(const CVector& vec);
	CVector operator-(const CVector& vec);
	CVector operator*(const float& k); // 상수 곱
	CVector operator/(const float& k); // 상수 나눗셈

	float GetVectorMagnitude(); // 벡터 크기
};

