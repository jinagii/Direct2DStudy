#include "pch.h"

//#include "CEngine.h"

//#include "CTime.h"

//#include "../PrjEngine/CUserInput.h"
//#pragma comment(lib, "../Debug/PrjEngine")
//#include <stdio.h>

CEngine::CEngine()
	 : m_pUserInput(nullptr), m_pMyPlayer(nullptr), m_pTargetPlayer(nullptr), m_pWICfactory(nullptr)
{
}

CEngine::~CEngine()
{
	 ReleaseAll();
}

void CEngine::Initialize(HWND hWnd)
{
	 RECT rc;

	 HRESULT _hResult = CoInitialize(NULL);

	 GetClientRect(hWnd, &rc);

	 HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

	 // Create a Direct2D render target
	 m_pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		  D2D1::HwndRenderTargetProperties(hWnd,
				D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)), &m_pRT);

	 if (SUCCEEDED(hr))
	 {
		  hr = CoCreateInstance(
				CLSID_WICImagingFactory, NULL,
				CLSCTX_INPROC_SERVER,
				IID_IWICImagingFactory,
				reinterpret_cast<void**>(&m_pWICfactory));
	 }

	 // pick brush
	 if (SUCCEEDED(hr));
	 {
		  m_pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &m_pRedBrush);
		  m_pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &m_pGreenBrush);
		  m_pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &m_pBlueBrush);
		  m_pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBlackBrush);
	 }
}

void CEngine::BeginRender()
{
	 m_pRT->BeginDraw();

	 m_pRT->SetTransform(D2D1::Matrix3x2F::Identity());

	 m_pRT->Clear(D2D1::ColorF(1, 1, 0, 0));
}

void CEngine::Render()
{
	 m_pRT->BeginDraw();
	 ///////////////////////////////////////////////////////////////////BeginDraw
	 m_pRT->Clear(D2D1::ColorF(0, 0, 0, 0));

	 ///////////////////////////////////////////////////////////////////EndDraw
	 m_pRT->EndDraw();
}

void CEngine::EndRender()
{
	 m_pRT->EndDraw();
}

void CEngine::DrawRectangle(int x, int y, int width, int height, ID2D1SolidColorBrush* pBrush)
{
	 m_pRT->DrawRectangle(D2D1::RectF(x - width / 2, y - height / 2, x + width / 2, y + height / 2),
		  pBrush);
}

void CEngine::DrawRectangle(int left, int top, int right, int bottom, bool isCollided)
{
	 if (isCollided == true)
	 {
		  m_pRT->DrawRectangle(D2D1::RectF(left, top, right, bottom), m_pRedBrush);
	 }
	 else
	 {
		  m_pRT->DrawRectangle(D2D1::RectF(left, top, right, bottom), m_pGreenBrush);
	 }
}

void CEngine::DrawFillRectangle(int x, int y, int width, int height, ID2D1SolidColorBrush* pBrush)
{
	 m_pRT->FillRectangle(D2D1::RectF(x - width / 2, y - height / 2, x + width / 2, y + height / 2),
		  pBrush);
}

void CEngine::DrawEllipse(float x, float y, int radius, ID2D1SolidColorBrush* pBrush)
{
	 D2D1_POINT_2F center;
	 center.x = x;
	 center.y = y;
	 m_pRT->DrawEllipse(D2D1::Ellipse(center, radius, radius), pBrush);
}

void CEngine::DrawEllipse(float x, float y, int radius, bool isCollided)
{
	 D2D1_POINT_2F center;
	 center.x = x;
	 center.y = y;

	 if (isCollided == true)
	 {
		  m_pRT->DrawEllipse(D2D1::Ellipse(center, radius, radius), m_pRedBrush);
	 }
	 else
	 {
		  m_pRT->DrawEllipse(D2D1::Ellipse(center, radius, radius), m_pGreenBrush);
	 }
}

void CEngine::DrawFillEllipse(int x, int y, int radius, ID2D1SolidColorBrush* pBrush)
{
	 D2D1_POINT_2F center;
	 center.x = x;
	 center.y = y;
	 m_pRT->FillEllipse(D2D1::Ellipse(center, radius, radius), pBrush);
}

void CEngine::ReleaseAll()
{
	 SafeRelease(&m_pD2DFactory);
	 SafeRelease(&m_pBlueBrush);
	 SafeRelease(&m_pGreenBrush);
	 SafeRelease(&m_pRedBrush);
	 SafeRelease(&m_pBlackBrush);
	 SafeRelease(&m_pRT);
}

void CEngine::SetTransform(const D2D1_MATRIX_3X2_F& transforMatrix)
{
	 m_pRT->SetTransform(transforMatrix);
}

HRESULT CEngine::LoadBitmapFromFile(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR path, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
	 HRESULT hr = S_OK;

	 IWICBitmapDecoder* _pDecoder = nullptr;
	 IWICBitmapFrameDecode* _pSource = nullptr;
	 IWICFormatConverter* _pConverter = nullptr;
	 IWICBitmapScaler* _pScaler = nullptr;

	 hr = pIWICFactory->CreateDecoderFromFilename(
		  path, NULL, GENERIC_READ,
		  WICDecodeMetadataCacheOnLoad,
		  &_pDecoder);

	 if (SUCCEEDED(hr))
	 {
		  hr = _pDecoder->GetFrame(0, &_pSource);
	 }

	 if (SUCCEEDED(hr))
	 {
		  hr = pIWICFactory->CreateFormatConverter(&_pConverter);
	 }

	 if (SUCCEEDED(hr))
	 {
		  if (destinationWidth != 0 || destinationHeight != 0)
		  {
				UINT originalWidth, originalHeight;
				hr = _pSource->GetSize(&originalWidth, &originalHeight);
				if (SUCCEEDED(hr))
				{
					 if (destinationWidth == 0)
					 {
						  FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
						  destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
					 }
					 else if (destinationHeight == 0)
					 {
						  FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
						  destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
					 }

					 hr = pIWICFactory->CreateBitmapScaler(&_pScaler);
					 if (SUCCEEDED(hr))
					 {
						  hr = _pScaler->Initialize(
								_pSource,
								destinationWidth,
								destinationHeight,
								WICBitmapInterpolationModeCubic);
					 }

					 if (SUCCEEDED(hr))
					 {
						  hr = _pConverter->Initialize(
								_pScaler,
								GUID_WICPixelFormat32bppPBGRA,
								WICBitmapDitherTypeNone,
								NULL,
								0.f,
								WICBitmapPaletteTypeMedianCut);
					 }
				}
		  }

		  else
		  {
				hr = _pConverter->Initialize(
					 _pSource,
					 GUID_WICPixelFormat32bppPBGRA,
					 WICBitmapDitherTypeNone,
					 NULL,
					 0.f,
					 WICBitmapPaletteTypeMedianCut
				);
		  }
	 }

	 if (SUCCEEDED(hr))
	 {
		  hr = pRenderTarget->CreateBitmapFromWicBitmap(
				_pConverter,
				NULL,
				ppBitmap
		  );
	 }

	 SafeRelease(&_pDecoder);
	 SafeRelease(&_pSource);
	 SafeRelease(&_pConverter);
	 SafeRelease(&_pScaler);

	 return hr;

}

void CEngine::LoadResource()
{
	 HRESULT hr = LoadBitmapFromFile(m_pRT, m_pWICfactory, L"../PrjEngine/Data/gundam.png", 200, 200, &m_pD2Dbitmap[0]);
	 //hr = LoadBitmapFromFile(m_pRT, m_pWICfactory, L"../PrjEngine/Data/test.png", 200, 200, &m_pD2Dbitmap[1]);
}

void CEngine::DrawBitmap(int index, int rectIndex)
{
	 // 	D2D1_RECT_F rect;
	 // 	rect.left = 0;
	 // 	rect.top = 0;
	 // 	rect.right = 50;
	 // 	rect.bottom = 50;

	 D2D1_RECT_F rect;
	 D2D1_SIZE_F originalSize = m_pD2Dbitmap[index]->GetSize();

	 int width = originalSize.width;
	 int height = originalSize.height;

	 rect.left = 0;
	 rect.top = 0;
	 rect.right = width;
	 rect.bottom = height;

	 // 위치에 따른 스프라이트 출력 시도중
	 D2D1_RECT_F dest;
	 dest.left = 0;
	 dest.top = 0;
	 dest.right = width;
	 dest.bottom = height;

	 m_pRT->DrawBitmap(m_pD2Dbitmap[index], dest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rect);
}

template <class T> void CEngine::SafeRelease(T** ppT)
{
	 if (*ppT)
	 {
		  (*ppT)->Release();
		  *ppT = NULL;
	 }
}
