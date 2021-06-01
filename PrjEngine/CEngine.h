#pragma once

#include "d2d1.h"
#include <wincodec.h>

#pragma comment(lib, "windowscodecs")

enum MyKeyInput
{
	 UP,
	 DOWN,
	 LEFT,
	 RIGHT,
	 NONE
};

class CCircle;
class CAABB;
class CUserInput;
class CObject;

class CEngine
{
public:
	 CEngine();
	 ~CEngine();

	 ID2D1SolidColorBrush* GetGreenBrush() const { return m_pGreenBrush; }
	 ID2D1HwndRenderTarget* GetRT() const { return m_pRT; }

private:
	 // 팩토리 변수 
	 ID2D1Factory* m_pD2DFactory;
	 // 이미지 팩토리
	 IWICImagingFactory* m_pWICfactory;
	 // 이미지 관련 변수
	 IWICBitmapDecoder* m_pWICDecoder;

	 // 렌더 타겟 - 윈도창 내부...?
	 ID2D1HwndRenderTarget* m_pRT;

	 // Brushes
	 ID2D1SolidColorBrush* m_pRedBrush;
	 ID2D1SolidColorBrush* m_pGreenBrush;
	 ID2D1SolidColorBrush* m_pBlueBrush;
	 ID2D1SolidColorBrush* m_pBlackBrush;

	 // 나만의 입력 클래스
	 CUserInput* m_pUserInput;

	 CCircle* m_Circle1;
	 CCircle* m_Circle2;

	 CAABB* m_Rect1;
	 CAABB* m_Rect2;

	 // object생성
	 CObject* m_pMyPlayer;
	 CObject* m_pTargetPlayer;

public:
	 // 이닛 함수
	 void Initialize(HWND hWnd);

	 // 렌더 함수
	 void BeginRender();
	 void Render();
	 void EndRender();

	 // 사각형 그리기 함수
	 void DrawRectangle(int x, int y, int width, int height, ID2D1SolidColorBrush* brush);
	 void DrawRectangle(int left, int top, int right, int bottom, bool isCollided);
	 void DrawFillRectangle(int x, int y, int width, int height, ID2D1SolidColorBrush* pBrush);

	 // 원 그리기 함수
	 void DrawEllipse(float x, float y, int radius, ID2D1SolidColorBrush* pBrush);
	 void DrawEllipse(float x, float y, int radius, bool isCollided);
	 void DrawFillEllipse(int x, int y, int radius, ID2D1SolidColorBrush* pBrush);

	 //void Update();

	 // 트랜스폼 
	 virtual void SetTransform(const D2D1_MATRIX_3X2_F& transforMatrix);

	 // 이미지 출력 관련
	 HRESULT LoadBitmapFromFile(
		  ID2D1RenderTarget* pRenderTarget,
		  IWICImagingFactory* pIWICFactory,
		  PCWSTR path,
		  UINT destinationWidth,
		  UINT destinationHeight,
		  ID2D1Bitmap** ppBitmap);

	 void LoadResource();
	 void DrawBitmap(int index, int rectIndex);

	 // 다 보내버리는 함수
	 void ReleaseAll();
	 template <class T> void SafeRelease(T** ppT);

public:
	 ID2D1Bitmap* m_pD2Dbitmap[5];
	 ID2D1Bitmap* m_pD2Dbitmap2;
};
