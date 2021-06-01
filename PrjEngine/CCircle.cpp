#include "pch.h"

CCircle::CCircle(float x, float y, int radius)
{
	m_circlePos.x = x;
	m_circlePos.y = y;
	m_radius = radius;
	m_isCollided = false;
}

CCircle::~CCircle()
{
}

void CCircle::MoveHorizontal(float value)
{
	m_circlePos.x += value;
}

void CCircle::MoveVertical(float value)
{
	m_circlePos.y += value;
}

void CCircle::Draw(CEngine* pEngine)
{
	pEngine->DrawEllipse(m_circlePos.x, m_circlePos.y, m_radius, m_isCollided);
}

void CCircle::CollisionCheck(ICollisionObject* pTarget)
{
	/// 인자로 받은 pTarget이 실제 CC객체인 경우 처리 
	CCircle* pTargetCircle = dynamic_cast<CCircle*>(pTarget);

	if (pTargetCircle != nullptr)
	{
		int _x = pTargetCircle->GetCirclePos().x - m_circlePos.x;
		int _y = pTargetCircle->GetCirclePos().y - m_circlePos.y;
		int _distanceSquare = (_x * _x) + (_y * _y);
		int _radiusDistance = m_radius + pTargetCircle->GetRadius();
		int _radiusSquare = _radiusDistance * _radiusDistance;

		if (_radiusSquare > _distanceSquare)
		{
			m_isCollided = true;
			pTargetCircle->SetCollided(true);
		}
		else
		{
			m_isCollided = false;
			pTargetCircle->SetCollided(false);
		}
	}

	/// pTarget이 Circle이 아니면
	CAABB* pTargetAABB = dynamic_cast<CAABB*>(pTarget);

	if (pTargetAABB != nullptr)
	{
		float _left = m_circlePos.x - m_radius;
		float _top = m_circlePos.y - m_radius;
		float _right = m_circlePos.x + m_radius;
		float _bottom = m_circlePos.y + m_radius;

		if (_right > pTargetAABB->GetRect().left &&
			_left < pTargetAABB->GetRect().right &&
			_top <pTargetAABB->GetRect().bottom &&
			_bottom > pTargetAABB->GetRect().top)
		{
			m_isCollided = true;
			pTargetAABB->SetCollided(true);
		}
		else
		{
			m_isCollided = false;
			pTargetAABB->SetCollided(false);
		}
	}
}
