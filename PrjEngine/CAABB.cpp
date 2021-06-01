#include "pch.h"

CAABB::CAABB(float left, float top, float right, float bottom)
	: m_rect(D2D1::RectF(left, top, right, bottom))
{
	/*m_rect.left = left;
	m_rect.top = top;
	m_rect.right = right;
	m_rect.bottom = bottom;
	*/
	m_isCollided = false;
}

CAABB::~CAABB()
{
}

void CAABB::Draw(CEngine* pCEngine)
{
	pCEngine->DrawRectangle(m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, m_isCollided);
}

void CAABB::CollisionCheck(ICollisionObject* pTarget)
{
	// 이 시점에 다형적 동작이 깨져야함
	// RTTI (Run-Time Type Identification) !!!
	CAABB* pTargetAABB = dynamic_cast<CAABB*>(pTarget);

	if (pTargetAABB != nullptr)
	{
		if (m_rect.right > pTargetAABB->GetRect().left &&
			pTargetAABB->GetRect().top < m_rect.bottom &&
			m_rect.left < pTargetAABB->GetRect().right &&
			pTargetAABB->GetRect().bottom > m_rect.top)
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

	/// pTarget이 AABB가 아니면?!
	// 타겟이 원이면 
	CCircle* pTargetCircle = dynamic_cast<CCircle*>(pTarget);

	if (pTargetCircle != nullptr)
	{
		// 사각형을 원으로 변환?!
		float _posX = (m_rect.left + m_rect.right) / 2.0f;	// 사각형의 원점을 재정의
		float _posY = (m_rect.top + m_rect.bottom) / 2.0f;	
		float _tempRadius = m_rect.right - m_rect.left;		// 사각형의 가짜반지름

		float _x = pTargetCircle->GetCirclePos().x - _posX;	// 사각형과 타겟의 x거리
		float _y = pTargetCircle->GetCirclePos().y - _posY;	// 사각형과 타겟의 y거리
		float _radiusDistance = pTargetCircle->GetRadius() + _tempRadius; // 가짜반지름 + 타겟 반지름

		float _distanceSquare = (_x * _x) + (_y * _y);		// 피타고라스 정리에 의한 거리확인
		float _radiusSqure = _radiusDistance * _radiusDistance;

		if (_radiusSqure > _distanceSquare)
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
}

void CAABB::MoveHorizontal(float value)
{
	m_rect.left += value;
	m_rect.right += value;
}

void CAABB::MoveVertical(float value)
{
	m_rect.top += value;
	m_rect.bottom += value;
}
