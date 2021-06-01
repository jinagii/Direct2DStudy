#pragma once


class CCircle;
class CAABB;
class CTransform;

/// ���ӳ� �����ϴ� ��ü / ����ýƮ / ��ü / ������Ʈ ���� ���
class CObject  
{
public:
	CObject(eCollisionType colType);
	~CObject();

	// �ʱ�ȭ
	void Initialize(float x, float y, float width, float height);


	// ������ ����

private:
	// �浹���� 
	eCollisionType m_collisionType;

	// �浹 ���¿� ���� �浹���� (�ٿ������)
	float m_radius;
	float m_width;
	float m_height;

	// ��ġ
	D2D1_POINT_2F m_position;	// CC
	D2D1_RECT_F m_rect;			// AABB

	// ��ȯ��� Ŭ����
	CTransform* m_pTransform;

	CCircle* m_CC;
	CAABB* m_AABB;
	
	ICollisionObject* m_myObject;

public:
	// �浹 ������ �ϴ� Ŭ����	
	bool CollisionDetection(CObject* pTarget);

	// ��ȯ�� ����ϴ� Ŭ����

	// ������ �Լ�
	void MoveVertical(float value) ;
	void MoveHorizontal(float value) ;	// =0 == abstract

	// ������ ����ϴ� Ŭ����

	// �׸��⸦ ����ϴ� Ŭ����
	void Draw(CEngine* pEngine);
};

