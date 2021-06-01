#pragma once

class CEngine;

class CCircle : public ICollisionObject
{
public:
	CCircle(float x, float y, int radius);
	~CCircle();

private:
	// ���� ����
	D2D1_POINT_2F m_circlePos;
	int m_radius;	// �� ������
	bool m_isCollided;	// �浹�ߴ°�?
	
public:
	// getter, setter
	D2D1_POINT_2F GetCirclePos() const { return m_circlePos; }
	int GetRadius() const { return m_radius; }

	void SetCollided(bool val) { m_isCollided = val; }
	
	// ���� ����
	virtual void MoveHorizontal(float value);
	virtual void MoveVertical(float value);

	// �浹 ����
	virtual void CollisionCheck(ICollisionObject* pTarget);
	
	// �׸���
	virtual void Draw(CEngine* pEngine);
};

