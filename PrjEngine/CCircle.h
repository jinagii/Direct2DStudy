#pragma once

class CEngine;

class CCircle : public ICollisionObject
{
public:
	CCircle(float x, float y, int radius);
	~CCircle();

private:
	// 원의 중점
	D2D1_POINT_2F m_circlePos;
	int m_radius;	// 원 반지름
	bool m_isCollided;	// 충돌했는가?
	
public:
	// getter, setter
	D2D1_POINT_2F GetCirclePos() const { return m_circlePos; }
	int GetRadius() const { return m_radius; }

	void SetCollided(bool val) { m_isCollided = val; }
	
	// 동작 관련
	virtual void MoveHorizontal(float value);
	virtual void MoveVertical(float value);

	// 충돌 관련
	virtual void CollisionCheck(ICollisionObject* pTarget);
	
	// 그리기
	virtual void Draw(CEngine* pEngine);
};

