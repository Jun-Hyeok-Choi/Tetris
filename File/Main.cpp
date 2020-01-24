#pragma once
#include "Resource.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	HWND hwnd;
	MSG msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Tetris");
	RegisterClass(&WndClass);
	hwnd = CreateWindowW(
		L"Tetris",
		L"Tetris Game",
		WS_OVERLAPPEDWINDOW,
		WindowPosX,
		WindowPosY,
		WindowX, 	//테트리스 300 + 여백 200
		WindowY,  	//테트리스 600 + 여백 50
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc, mem1DC, mem2DC;
	HBITMAP Bitmap, OldBitMap;
	PAINTSTRUCT ps;
	static BLOCK* block = new BLOCK[201];
	int Mx, My;
	switch (iMsg)
	{
	case WM_CREATE:
		srand((unsigned)time(NULL));
		InterfaceCreate();
		BlockColorCreate();
		break;
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = WindowX;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = WindowY;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = WindowX;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = WindowY;
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_LEFT:
			BlockMoveL(&block[GetSelect()]);
			break;
		case VK_RIGHT:
			BlockMoveR(&block[GetSelect()]);
			break;
		case VK_DOWN:
			BlockMoveD(&block[GetSelect()]);
			break;
		case VK_UP:
			if (BlockRotate(&block[GetSelect()]))
				PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC);
			break;
		case VK_CONTROL:
			BlockChange(&block[GetNextSelect()]);
			break;
		case VK_ESCAPE:
			exit(0);
			break;
		}
		InvalidateRgn(hwnd, NULL, FALSE);
		break;
	case WM_LBUTTONDOWN:
		Mx = LOWORD(lParam);
		My = HIWORD(lParam);
		//Start,Reset버튼 실행
		switch (SelectStartButton(Mx, My)) {
		case 1:
			MapInit();
			SInit(block);
			CreateNumber();
			SetTimer(hwnd, GetLevel(), 1000 - (GetLevel()-1 * 50), NULL);
			break;
		case 2:
			BlockReset(block);
			KillTimer(hwnd, GetLevel());
			break;
		}
		//Pause버튼 실행
		if (SelectPauseButton(Mx, My) && GetLevel() && GetStartSelect()) {
			KillTimer(hwnd, GetLevel());
			if (MessageBox(hwnd, _T("Do you want to Start?"), _T("Pause"), MB_OK))
				SetTimer(hwnd, GetLevel(), 1000 - (GetLevel()-1 * 50), NULL);
		}
		InvalidateRgn(hwnd, NULL, FALSE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		mem1DC = CreateCompatibleDC(hdc);
		mem2DC = CreateCompatibleDC(mem1DC);
		Bitmap = CreateCompatibleBitmap(hdc, WindowX, WindowY);
		OldBitMap = (HBITMAP)SelectObject(mem1DC, Bitmap);
		BitBlt(mem1DC, 0, 0, WindowX, WindowY, mem2DC, 0, 0, SRCCOPY);

		//더블 버퍼링으로 그려지는 부분
		ITFBackGround(mem1DC);
		BlockDraw(mem1DC, block);

		BitBlt(hdc, 0, 0, WindowX, WindowY, mem1DC, 0, 0, SRCCOPY);
		SelectObject(mem1DC, OldBitMap);
		DeleteObject(Bitmap);
		DeleteDC(mem1DC);
		DeleteDC(mem2DC);
		EndPaint(hwnd, &ps);
		break;
	case WM_TIMER:
		hdc = GetDC(hwnd);
		//선택된 블록이 더이상 움직이지 않는지 체크후 선택된 블록 다음으로 교체
		SelectChange(block);

		//게임 패배 구현
		if (!MoveCheck(&block[GetSelect()])) {
			KillTimer(hwnd, GetLevel());
			MessageBox(hwnd, _T("Your Defeat"), _T("End"), MB_OK);
			BlockReset(block);
			ClickStartButton();
		}

		//파괴된 줄이 있으면 LINE을 증가시켜준다.
		LineUp(BlockBreak(block));

		//Line을 기준으로 스코어를 더한다.
		if (IsScoreUp()) {
			PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
			ScoreSet();
			ChangeUp(GetScore());
		}

		//Level을 세팅한다. Line7당 Level1업씩.
		if (LevelSet()) {
			KillTimer(hwnd, GetLevel() - 1);
			SetTimer(hwnd, GetLevel(), 1000 - (GetLevel()-1 * 50), NULL);
		}

		//게임 승리 구현
		if (GetLevel()>20) {
			KillTimer(hwnd, GetLevel());
			CreateNumber();
			MessageBox(hwnd, _T("Your Win"), _T("End"), MB_OK);
			BlockReset(block);
			ClickStartButton();
		}

		//만약 block의 NEmpty값이 모두 false라면 그 블록을 지워준다.
		BlockDelete(block);
		InvalidateRgn(hwnd, NULL, FALSE);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_DESTROY:
		delete[] block;
		InterfaceDelete();
		BlockColorDelete();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}