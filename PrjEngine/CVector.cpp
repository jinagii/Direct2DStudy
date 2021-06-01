#include "pch.h"

CVector::CVector()
{
}

CVector::CVector(float x, float y)
{
	this->x = x;
	this->y = y;
}

CVector::~CVector()
{
}

CVector CVector::operator+(const CVector& vec)
{
	CVector _resultVec;
	_resultVec.x = this->x + vec.x;
	_resultVec.y = this->y + vec.y;

	return _resultVec;
}

CVector CVector::operator-(const CVector& vec)
{
	CVector _resultVec;
	_resultVec.x = this->x - vec.x;
	_resultVec.y = this->y - vec.y;

	return _resultVec;
}

CVector CVector::operator*(const float& k)
{
	CVector _resultVec;
	_resultVec.x = this->x * k;
	_resultVec.y = this->y * k;

	return _resultVec;
}

CVector CVector::operator/(const float& k)
{
	CVector _resultVec;
	_resultVec.x = this->x / k;
	_resultVec.y = this->y / k;

	return _resultVec;
}

float CVector::GetVectorMagnitude()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

