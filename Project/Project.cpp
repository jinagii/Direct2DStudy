#include "pch.h"
#include "Project.h"
#include "../PrjEngine/CEngine.h"
#include "d2d1.h"
#pragma comment(lib, "d2d1")

#define MAX_LOADSTRING 100

// 전역 변수
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

HWND g_hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

// 전반적인 윈도우 생성의 main 함수 
// 윈도우를 생성하고 input을 받음, 메시지 루프를 돔(Peekmessage)  
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	 _In_opt_ HINSTANCE hPrevInstance,
	 _In_ LPWSTR    lpCmdLine,
	 _In_ int       nCmdShow)
{
	 UNREFERENCED_PARAMETER(hPrevInstance);
	 UNREFERENCED_PARAMETER(lpCmdLine);

	 // 전역 문자열을 초기화
	 LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	 LoadStringW(hInstance, IDC_PROJECT, szWindowClass, MAX_LOADSTRING);
	 MyRegisterClass(hInstance);

	 // 애플리케이션 초기화를 수행
	 if (!InitInstance(hInstance, nCmdShow))
	 {
		  return FALSE;
	 }

	 HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT));

	 MSG msg;
	 /////////////////////////////////////////////////////////////////////////////////
	 // 엔진, 키인풋 선언
	 CEngine* pEngine = new CEngine;
	 pEngine->Initialize(g_hWnd);
	 pEngine->LoadResource();

	 CUserInput* pMyKey = new CUserInput;

	 // 오브젝트 선언
	 ICollisionObject* _pMyPlayer = nullptr;
	 ICollisionObject* _pTargetPlayer = nullptr;

	 // 분기를 만들어서, 동적으로 오브젝트를 정의한다는 것의 예시
	 int _testCase = 3;

	 if (_testCase == 0)
	 {
		  _pMyPlayer = new CCircle(500, 500, 150.0f);
		  _pTargetPlayer = new CCircle(300, 300, 150.0f);
	 }
	 else if (_testCase == 1)
	 {
		  _pMyPlayer = new CAABB(300, 300, 400, 400);
		  _pTargetPlayer = new CAABB(100, 200, 200, 300);
	 }
	 else if (_testCase == 2)
	 {
		  _pMyPlayer = new CAABB(300, 300, 400, 400);
		  _pTargetPlayer = new CCircle(300, 300, 150.0f);
	 }
	 else if (_testCase == 3)
	 {
		  _pMyPlayer = new CCircle(300, 300, 150.0f);
		  _pTargetPlayer = new CAABB(300, 300, 400, 400);
	 }

	 // 게임 개발엔 peekmessage
	 while (TRUE)
	 {
		  if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		  {
				if (msg.message == WM_QUIT) break;

				DispatchMessage(&msg);
		  }
		  else
		  {
				// 렌더링 start ---------------------------------------
				pEngine->BeginRender();

				pMyKey->Update(_pMyPlayer);

				//pEngine->SetTransform(CTransform::ScaleMatrix(D2D1::SizeF(2.f, 2.f), D2D1::Point2F(200.f, 200.f)));
				// 대상 그리기

				//pEngine->SetTransform(CTransform::RotateMatrix(30, D2D1::Point2F(300.f,200.f)));
				_pTargetPlayer->Draw(pEngine);

				//pEngine->SetTransform(CTransform::RotateAndScaleMatrix(30, D2D1::SizeF(2.f, 2.f), D2D1::Point2F(200.f, 200.f)));
				_pMyPlayer->Draw(pEngine);

				pEngine->DrawBitmap(0, 2);
				//pEngine->DrawBitmap(1,2);

				// 충돌체크
				_pMyPlayer->CollisionCheck(_pTargetPlayer);

				// 렌더린 end ----------------------------------
				pEngine->EndRender();
		  }
	 }

	 return (int)msg.wParam;
}

// 창 클래스를 등록
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	 WNDCLASSEXW wcex;

	 wcex.cbSize = sizeof(WNDCLASSEX);

	 wcex.style = CS_HREDRAW | CS_VREDRAW;
	 wcex.lpfnWndProc = WndProc;
	 wcex.cbClsExtra = 0;
	 wcex.cbWndExtra = 0;
	 wcex.hInstance = hInstance;
	 wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT));
	 wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	 wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	 wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PROJECT);
	 wcex.lpszClassName = szWindowClass;
	 wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	 return RegisterClassExW(&wcex);
}

// 인스턴스 핸들을 저장하고 주 창을 만듬
// 인스턴스 핸들을 전역 변수에 저장하고 주 프로그램 창을 만든 다음 표시
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	 hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	 g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		  CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	 if (!g_hWnd)
	 {
		  return FALSE;
	 }

	 ShowWindow(g_hWnd, nCmdShow);
	 UpdateWindow(g_hWnd);

	 return TRUE;
}

// 주 창의 메시지를 처리
// 함수 포인터로 메시지를 보냄
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	 switch (message)
	 {
		  case WM_CREATE:
		  {
				///HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
		  }
		  break;

		  case WM_COMMAND:
		  {
				int wmId = LOWORD(wParam);
				// 메뉴 선택을 구문 분석합니다:
				switch (wmId)
				{
					 case IDM_EXIT:
						  DestroyWindow(hWnd);
						  break;
					 default:
						  return DefWindowProc(hWnd, message, wParam, lParam);
				}
		  }
		  break;

		  case WM_PAINT:
		  {

		  }
		  break;

		  case WM_DESTROY:
		  {
				PostQuitMessage(0);
		  }
		  break;
	 }

	 return DefWindowProc(hWnd, message, wParam, lParam);
}




