#include "pch.h"

CTransform::CTransform()
{
}

CTransform::~CTransform()
{
}

D2D_MATRIX_3X2_F CTransform::RotateMatrix(float angle, D2D1_POINT_2F center)
{
	D2D1_MATRIX_3X2_F _translateToCenter = TranslateMatrix(D2D1::Size(center.x, center.y));
	D2D1_MATRIX_3X2_F _rotateOnOrigin = RotateMatrixOrigin(angle);
	D2D1_MATRIX_3X2_F _translateToOrigin = TranslateMatrix(D2D1::Size(-center.x, -center.y));

	D2D1_MATRIX_3X2_F _resultMatrix = _translateToOrigin * _rotateOnOrigin * _translateToCenter;

	return _resultMatrix;
}

D2D1_MATRIX_3X2_F CTransform::RotateMatrixOrigin(float angle)
{
	float _rad = DegreeToRad(angle);

	D2D1_MATRIX_3X2_F _rotate;

	_rotate._11 = cos(_rad);	_rotate._12 = sin(_rad);
	_rotate._21 = -sin(_rad);	_rotate._22 = cos(_rad);
	_rotate._31 = 0.f;			_rotate._32 = 0.f;

	return _rotate;
}

D2D_MATRIX_3X2_F CTransform::ScaleMatrix(D2D1_SIZE_F size, D2D1_POINT_2F center)
{
	D2D1_MATRIX_3X2_F _translateToCenter = TranslateMatrix(D2D1::Size(center.x, center.y));
	D2D1_MATRIX_3X2_F _scaleOnOrigin = ScaleMatrixOrigin(size);
	D2D1_MATRIX_3X2_F _translateToOrigin = TranslateMatrix(D2D1::Size(-center.x, -center.y));

	D2D1_MATRIX_3X2_F _resultMatrix = _translateToOrigin * _scaleOnOrigin * _translateToCenter;

	return _resultMatrix;
}

D2D_MATRIX_3X2_F CTransform::ScaleMatrixOrigin(D2D1_SIZE_F size)
{
	D2D1_MATRIX_3X2_F _scale;

	_scale._11 = size.width * 1.f;	_scale._12 = 0.f;
	_scale._21 = 0.f;				_scale._22 = size.width * 1.f;
	_scale._31 = 0.f;				_scale._32 = 0.f;

	return _scale;
}

D2D_MATRIX_3X2_F CTransform::TranslateMatrix(D2D1_SIZE_F dist)
{
	D2D1_MATRIX_3X2_F _trans;

	_trans._11 = 1.f;			_trans._12 = 0.f;
	_trans._21 = 0.f;			_trans._22 = 1.f;
	_trans._31 = dist.width;	_trans._32 = dist.height;

	return _trans;
}

D2D1_MATRIX_3X2_F CTransform::RotateAndScaleMatrix(float angle, D2D1_SIZE_F size, D2D_POINT_2F center)
{
	D2D1_MATRIX_3X2_F _translateToCenter = TranslateMatrix(D2D1::Size(center.x, center.y));
	D2D1_MATRIX_3X2_F _scaleOnOrigin = ScaleMatrixOrigin(size);
	D2D1_MATRIX_3X2_F _rotateOnOrigin = RotateMatrixOrigin(angle);
	D2D1_MATRIX_3X2_F _translateToOrigin = TranslateMatrix(D2D1::Size(-center.x, -center.y));

	// 원점으로 이동 -> 스케일 조절 -> 회전 -> 원래 포지션으로 이동
	D2D1_MATRIX_3X2_F _resultMatrix = _translateToOrigin * _scaleOnOrigin *_rotateOnOrigin* _translateToCenter;

	return _resultMatrix;
}
