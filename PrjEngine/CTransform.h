#pragma once

// 파이값과 각도 계산
#define Pi 3.1415f 
#define DegreeToRad(x) (x * Pi / 180.0f)

// 주로 object 회전을 하기위한 함수를 담아둔 클래스
class CTransform
{
public:
	CTransform();
	~CTransform();

	// D2D_MATRIX_3X2_F 를 반환

	// 회전 매트릭스
	static D2D_MATRIX_3X2_F RotateMatrix(float angle, D2D1_POINT_2F center);
	// 원점에서의 회전
	static D2D1_MATRIX_3X2_F RotateMatrixOrigin(float angle);

	// 스케일 조정
	static D2D_MATRIX_3X2_F ScaleMatrix(D2D1_SIZE_F size, D2D1_POINT_2F center);
	// 원점에서의 스케일
	static D2D_MATRIX_3X2_F ScaleMatrixOrigin(D2D1_SIZE_F size);

	// 평행이동 
	static D2D_MATRIX_3X2_F TranslateMatrix(D2D1_SIZE_F size);

	// 회전과 스케일 동시에
	static D2D1_MATRIX_3X2_F RotateAndScaleMatrix(float angle, D2D1_SIZE_F size, D2D_POINT_2F center);
};

