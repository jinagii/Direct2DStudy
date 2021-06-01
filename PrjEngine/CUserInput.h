#pragma once

class ICollisionObject;
class CEngine;

class CUserInput
{
public:
	CUserInput();
	~CUserInput();


	void InitializeInput();

	void KeyInput();

	void Update(ICollisionObject* pMyObject);


private:

	ICollisionObject* m_pMyCollisionObject;

	D2D1_POINT_2F m_position; //?

};

