#include "pch.h"

CUserInput::CUserInput()
{
}

CUserInput::~CUserInput()
{
}

void CUserInput::InitializeInput()
{

}

void CUserInput::KeyInput()
{

}

void CUserInput::Update(ICollisionObject* pMyObject)
{
	 if (GetAsyncKeyState(VK_UP))
	 {
		  pMyObject->MoveVertical(-5);
	 }
	 if (GetAsyncKeyState(VK_DOWN))
	 {
		  pMyObject->MoveVertical(5);
	 }
	 if (GetAsyncKeyState(VK_LEFT))
	 {
		  pMyObject->MoveHorizontal(-5);
	 }
	 if (GetAsyncKeyState(VK_RIGHT))
	 {
		  pMyObject->MoveHorizontal(5);
	 }
}