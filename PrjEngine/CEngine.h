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
	 // ���丮 ���� 
	 ID2D1Factory* m_pD2DFactory;
	 // �̹��� ���丮
	 IWICImagingFactory* m_pWICfactory;
	 // �̹��� ���� ����
	 IWICBitmapDecoder* m_pWICDecoder;

	 // ���� Ÿ�� - ����â ����...?
	 ID2D1HwndRenderTarget* m_pRT;

	 // Brushes
	 ID2D1SolidColorBrush* m_pRedBrush;
	 ID2D1SolidColorBrush* m_pGreenBrush;
	 ID2D1SolidColorBrush* m_pBlueBrush;
	 ID2D1SolidColorBrush* m_pBlackBrush;

	 // ������ �Է� Ŭ����
	 CUserInput* m_pUserInput;

	 CCircle* m_Circle1;
	 CCircle* m_Circle2;

	 CAABB* m_Rect1;
	 CAABB* m_Rect2;

	 // object����
	 CObject* m_pMyPlayer;
	 CObject* m_pTargetPlayer;

public:
	 // �̴� �Լ�
	 void Initialize(HWND hWnd);

	 // ���� �Լ�
	 void BeginRender();
	 void Render();
	 void EndRender();

	 // �簢�� �׸��� �Լ�
	 void DrawRectangle(int x, int y, int width, int height, ID2D1SolidColorBrush* brush);
	 void DrawRectangle(int left, int top, int right, int bottom, bool isCollided);
	 void DrawFillRectangle(int x, int y, int width, int height, ID2D1SolidColorBrush* pBrush);

	 // �� �׸��� �Լ�
	 void DrawEllipse(float x, float y, int radius, ID2D1SolidColorBrush* pBrush);
	 void DrawEllipse(float x, float y, int radius, bool isCollided);
	 void DrawFillEllipse(int x, int y, int radius, ID2D1SolidColorBrush* pBrush);

	 //void Update();

	 // Ʈ������ 
	 virtual void SetTransform(const D2D1_MATRIX_3X2_F& transforMatrix);

	 // �̹��� ��� ����
	 HRESULT LoadBitmapFromFile(
		  ID2D1RenderTarget* pRenderTarget,
		  IWICImagingFactory* pIWICFactory,
		  PCWSTR path,
		  UINT destinationWidth,
		  UINT destinationHeight,
		  ID2D1Bitmap** ppBitmap);

	 void LoadResource();
	 void DrawBitmap(int index, int rectIndex);

	 // �� ���������� �Լ�
	 void ReleaseAll();
	 template <class T> void SafeRelease(T** ppT);

public:
	 ID2D1Bitmap* m_pD2Dbitmap[5];
	 ID2D1Bitmap* m_pD2Dbitmap2;
};
