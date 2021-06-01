#pragma once

class CEngine;

// 나중을 위해...?!
enum class eCollisionType
{
	CC,
	AABB
};

/// 모든 충돌 가능한 오브젝트의 부모
/// 충돌 감지용 오브젝트를 추상화
class ICollisionObject //abstract
{
public:
	// 동작 관련 함수
	virtual void MoveVertical(float value) abstract;
	virtual void MoveHorizontal(float value) = 0; // == abstract
	// 충돌감지
	virtual void CollisionCheck(ICollisionObject* pTarget) abstract;
	// 그리기 함수
	virtual void Draw(CEngine* pEngint) abstract;
	
private:
	
};

