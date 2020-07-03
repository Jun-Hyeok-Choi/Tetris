#include "Resource.h"

void InterfaceCreate() {
	//이 함수는 Brush Pen Font등을 생성합니다.
	ITFBrush1 = CreateSolidBrush(RGB(150, 150, 150));
	ITFPen1 = CreatePen(PS_SOLID, 1, RGB(150, 150, 150));
	ITFPen2 = CreatePen(PS_DASH, 1, RGB(60, 60, 60));
	ITFFONT1 = CreateFontW(20, 10, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("휴먼둥근헤드라인"));
	ITFFONT2 = CreateFontW(12, 5, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("휴먼둥근헤드라인"));
	ITFFONT3 = CreateFontW(16, 8, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("휴먼둥근헤드라인"));
	ITFFONT4 = CreateFontW(24, 12, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("휴먼둥근헤드라인"));
}

void InterfaceDelete() {
	//메모리 헤제
	DeleteObject(ITFBrush1);
	DeleteObject(ITFPen1);
	DeleteObject(ITFFONT1);
	DeleteObject(ITFFONT2);
	DeleteObject(ITFFONT3);
	DeleteObject(ITFFONT4);
}

void ITFBackGround(HDC hdc) {
	//회색 선들 그리기
	BasicBrush = (HBRUSH)SelectObject(hdc, ITFBrush1);
	BasicPen = (HPEN)SelectObject(hdc, ITFPen1);
	Rectangle(hdc, 0, 0, 25, 650);
	Rectangle(hdc, 0, 0, 500, 25);
	Rectangle(hdc, 475, 0, 500, 650);
	Rectangle(hdc, 0, 625, 500, 650);
	Rectangle(hdc, 325, 0, 350, 650);
	Rectangle(hdc, 350, 95, 500, 105);
	Rectangle(hdc, 350, 275, 500, 285);
	Rectangle(hdc, 350, 415, 500, 425);
	Rectangle(hdc, 350, 530, 500, 540);

	//인터페이스 글자들 그리기
	SelectObject(hdc, ITFFONT1);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(0, 0, 0));
	TextOut(hdc, 390, 35, _T("LEVEL"), 5);
	TextOut(hdc, 400, 90, _T("NEXT"), 4);
	TextOut(hdc, 360, 220, _T("CHANGE"), 6);
	TextOut(hdc, 411, 300, _T("LINE"), 4);
	TextOut(hdc, 383, 360, _T("SCORE"), 5);
	

	SelectObject(hdc, ITFFONT2);
	TextOut(hdc, 370, 435, _T("MOVE : ←,↓,→"), 12);
	TextOut(hdc, 385, 460, _T("ROTATE : ↑"), 10);
	TextOut(hdc, 360, 485, _T("CHANGE : CTRL"), 13);
	TextOut(hdc, 395, 510, _T("QUIT : ESE"), 10);

	SelectObject(hdc, ITFFONT4);
	TextOut(hdc, 365, 550, _T("PAUSE"), 5);
	if (!StartSelect)
		TextOut(hdc, 365, 590, _T("START"), 5);
	else
		TextOut(hdc, 365, 590, _T("RESET"), 5);

	SelectObject(hdc, ITFFONT3);
	//LEVEL 출력
	wchar_t TLevel[4];
	swprintf_s(TLevel, L"%d%d%d", 0, Level / 10, Level % 10);
	TextOut(hdc, 425, 65, TLevel, sizeof(TLevel) / sizeof(wchar_t));

	//CHANGE 출력
	wchar_t TChange[5];
	int Ch = GetChange();
	swprintf_s(TChange, L"%d%d%d%d", Ch / 1000, Ch % 1000 / 100, Ch % 100 / 10, Ch % 10);
	TextOut(hdc, 415, 250, TChange, sizeof(TChange) / sizeof(wchar_t));
	
	//LINE 출력
	wchar_t TLine[5];
	swprintf_s(TLine, L"%d%d%d%d", Line / 1000, Line % 1000 / 100, Line % 100 / 10, Line % 10);
	TextOut(hdc, 415, 330, TLine, sizeof(TLine) / sizeof(wchar_t));
	
	//SCORE 출력
	wchar_t TScore[8];
	swprintf_s(TScore, L"%d%d%d%d%d%d%d", Score / 1000000, Score % 1000000 / 100000, Score % 100000 / 10000, Score % 10000 / 1000, Score % 1000 / 100, Score % 100 / 10, Score % 10);
	TextOut(hdc, 378, 390, TScore, sizeof(TScore) / sizeof(wchar_t));

	SelectObject(hdc,BasicBrush);
	SelectObject(hdc, BasicPen);
	SelectObject(hdc, ITFPen2);

	//게임 블록 라인 그리기
	for (int i = 1; i < 10; i++) {
		MoveToEx(hdc, 25 + i * 30, 25, NULL);
		LineTo(hdc, 25 + i * 30, 625);
	}
	for (int i = 1; i < 20; i++) {
		MoveToEx(hdc, 25, 25 + i * 30, NULL);
		LineTo(hdc, 325, 25 + i * 30);
	}
}

void CreateNumber() {
	//게임 시작할 때 Level, Line, OldLine, Score의 값을 초기화
	Level = 1;
	Line = OldLine = Score = 0;
}

void ScoreSet() {
	//Line의 값을 기준으로 점수를 추가시킨다.
	Score += ((Line - OldLine) * 500) + (111 * (int)pow(3, Line - OldLine - 1));
	//OldLine과 Line값을 같게 해준다.
	OldLine = Line;
}

const bool IsScoreUp() {
	//Line과 OldLine의 차이가 있으면 True반환
	if (Line - OldLine != 0)
		return true;
	return false;
}

void LineUp(const int Up) {
	//BlockBreak에서 파괴된 줄 만큼 Line을 증가시켜준다.
	Line += Up;
}

const bool LevelSet() {
	//Line의 값을 기준으로 레벨을 올린다.
	if (Line / 7 != Level - 1) {
		Level++;
		return true;
	}
	return false;
}

const int GetLevel() {
	//Level값을 얻는다.
	return Level;
}

const int GetScore() {
	//Score값을 얻는다.
	return Score;
}

const int SelectStartButton(int Mx, int My) {
	//Start버튼 클릭을 구현한다.
	//Start버튼을 누르면 Reset으로 변경된다.
	//게임을 패배하면 Reset버튼이 Start버튼으로 바뀐다.

	if (Mx<360 || Mx>475 || My<595 || My>615)
		return 0;

	//Start일때 누를 경우 1로 바꾼다.
	//Reset버튼으로 바뀌게된다.
	if (!StartSelect) {
		ClickStartButton();
		return 1;
	}
	//Reset버튼일때 누를 경우
	else {
		ClickStartButton();
		return 2;
	}
		
}

void ClickStartButton() {
	PlaySound(MAKEINTRESOURCE(IDR_WAVE3), NULL, SND_RESOURCE | SND_ASYNC);
	StartSelect = !StartSelect;
}

const bool SelectPauseButton(int Mx, int My){
	//범위 계산 true/false 반환
	if (Mx < 360 || Mx>475 || My < 555 || My>575)
		return false;
	PlaySound(MAKEINTRESOURCE(IDR_WAVE3), NULL, SND_RESOURCE | SND_ASYNC);
	return true;
}

const bool GetStartSelect() {
	return StartSelect;
}