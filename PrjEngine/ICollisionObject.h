#pragma once

class CEngine;

// ������ ����...?!
enum class eCollisionType
{
	CC,
	AABB
};

/// ��� �浹 ������ ������Ʈ�� �θ�
/// �浹 ������ ������Ʈ�� �߻�ȭ
class ICollisionObject //abstract
{
public:
	// ���� ���� �Լ�
	virtual void MoveVertical(float value) abstract;
	virtual void MoveHorizontal(float value) = 0; // == abstract
	// �浹����
	virtual void CollisionCheck(ICollisionObject* pTarget) abstract;
	// �׸��� �Լ�
	virtual void Draw(CEngine* pEngint) abstract;
	
private:
	
};

