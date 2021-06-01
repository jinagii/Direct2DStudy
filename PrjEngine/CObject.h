#pragma once


class CCircle;
class CAABB;
class CTransform;

/// 게임내 존재하는 객체 / 오브첵트 / 개체 / 오브젝트 등의 대상
class CObject  
{
public:
	CObject(eCollisionType colType);
	~CObject();

	// 초기화
	void Initialize(float x, float y, float width, float height);


	// 구성을 정의

private:
	// 충돌감지 
	eCollisionType m_collisionType;

	// 충돌 형태에 따른 충돌영역 (바운딩볼륨)
	float m_radius;
	float m_width;
	float m_height;

	// 위치
	D2D1_POINT_2F m_position;	// CC
	D2D1_RECT_F m_rect;			// AABB

	// 변환담당 클래스
	CTransform* m_pTransform;

	CCircle* m_CC;
	CAABB* m_AABB;
	
	ICollisionObject* m_myObject;

public:
	// 충돌 감지를 하는 클래스	
	bool CollisionDetection(CObject* pTarget);

	// 변환을 담당하는 클래스

	// 움직임 함수
	void MoveVertical(float value) ;
	void MoveHorizontal(float value) ;	// =0 == abstract

	// 물리를 담당하는 클래스

	// 그리기를 담당하는 클래스
	void Draw(CEngine* pEngine);
};

