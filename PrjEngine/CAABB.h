#pragma once

class CEngine;

class CAABB : public ICollisionObject
{
public:
	CAABB(float left, float right, float top, float bottom);
	~CAABB();

private:
	D2D1_RECT_F m_rect;

	bool m_isCollided;

public:
	// getter, setter
	void SetCollided(bool val) { m_isCollided = val; }
	D2D1_RECT_F GetRect() const { return m_rect; }

	// 다형성 적용
	virtual void Draw(CEngine* pCEngine);

	virtual void CollisionCheck(ICollisionObject* pTarget);

	virtual void MoveHorizontal(float value);
	virtual void MoveVertical(float value);

	


};

