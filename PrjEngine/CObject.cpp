#include "pch.h"
#include "CObject.h"


CObject::CObject(eCollisionType colType)
	: m_collisionType(colType)
{
}

CObject::~CObject()
{
}

void CObject::Initialize(float x, float y, float width, float height)
{



}

 bool CObject::CollisionDetection(CObject* pTarget)
 {
 	if (m_collisionType == eCollisionType::CC)
 	{
 		
 	}
 	else if (m_collisionType == eCollisionType::AABB)
 	{
 
 	}
 
 // 	else if (m_collisionType == eCollisionType::AABB)
 // 	{
 // 
 // 	}
 
 	return true;
 }

void CObject::MoveVertical(float value)
{
	if (m_collisionType == eCollisionType::CC)
	{
		m_position.y += value;
	}
	else if (m_collisionType == eCollisionType::AABB)
	{
		m_rect.top += value;
		m_rect.bottom += value;
	}
}

void CObject::MoveHorizontal(float value)
{
	if (m_collisionType == eCollisionType::CC)
	{
		m_position.x += value;
	}
	else if (m_collisionType == eCollisionType::AABB)
	{
		m_rect.left += value;
		m_rect.right += value;
	}
}

void CObject::Draw(CEngine* pEngine)
{
	if (m_collisionType == eCollisionType::CC)
	{
		pEngine->DrawEllipse(m_position.x, m_position.y, m_radius, pEngine->GetCollision());
	}
	else if (m_collisionType == eCollisionType::AABB)
	{
		pEngine->DrawRectangle(m_position.x, m_position.y, m_width, m_height, pEngine->GetCollision());
	}

	// 	else if (m_collisionType == eCollisionType::AABB)
	// 	{
	// 
	// 	}
}

