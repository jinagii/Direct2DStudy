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
	// �� ������ ������ ������ ��������
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

	/// pTarget�� AABB�� �ƴϸ�?!
	// Ÿ���� ���̸� 
	CCircle* pTargetCircle = dynamic_cast<CCircle*>(pTarget);

	if (pTargetCircle != nullptr)
	{
		// �簢���� ������ ��ȯ?!
		float _posX = (m_rect.left + m_rect.right) / 2.0f;	// �簢���� ������ ������
		float _posY = (m_rect.top + m_rect.bottom) / 2.0f;	
		float _tempRadius = m_rect.right - m_rect.left;		// �簢���� ��¥������

		float _x = pTargetCircle->GetCirclePos().x - _posX;	// �簢���� Ÿ���� x�Ÿ�
		float _y = pTargetCircle->GetCirclePos().y - _posY;	// �簢���� Ÿ���� y�Ÿ�
		float _radiusDistance = pTargetCircle->GetRadius() + _tempRadius; // ��¥������ + Ÿ�� ������

		float _distanceSquare = (_x * _x) + (_y * _y);		// ��Ÿ��� ������ ���� �Ÿ�Ȯ��
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
