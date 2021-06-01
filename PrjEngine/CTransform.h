#pragma once

// ���̰��� ���� ���
#define Pi 3.1415f 
#define DegreeToRad(x) (x * Pi / 180.0f)

// �ַ� object ȸ���� �ϱ����� �Լ��� ��Ƶ� Ŭ����
class CTransform
{
public:
	CTransform();
	~CTransform();

	// D2D_MATRIX_3X2_F �� ��ȯ

	// ȸ�� ��Ʈ����
	static D2D_MATRIX_3X2_F RotateMatrix(float angle, D2D1_POINT_2F center);
	// ���������� ȸ��
	static D2D1_MATRIX_3X2_F RotateMatrixOrigin(float angle);

	// ������ ����
	static D2D_MATRIX_3X2_F ScaleMatrix(D2D1_SIZE_F size, D2D1_POINT_2F center);
	// ���������� ������
	static D2D_MATRIX_3X2_F ScaleMatrixOrigin(D2D1_SIZE_F size);

	// �����̵� 
	static D2D_MATRIX_3X2_F TranslateMatrix(D2D1_SIZE_F size);

	// ȸ���� ������ ���ÿ�
	static D2D1_MATRIX_3X2_F RotateAndScaleMatrix(float angle, D2D1_SIZE_F size, D2D_POINT_2F center);
};

