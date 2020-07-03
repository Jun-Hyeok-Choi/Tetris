#include "Resource.h"

void InterfaceCreate() {
	//�� �Լ��� Brush Pen Font���� �����մϴ�.
	ITFBrush1 = CreateSolidBrush(RGB(150, 150, 150));
	ITFPen1 = CreatePen(PS_SOLID, 1, RGB(150, 150, 150));
	ITFPen2 = CreatePen(PS_DASH, 1, RGB(60, 60, 60));
	ITFFONT1 = CreateFontW(20, 10, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("�޸յձ�������"));
	ITFFONT2 = CreateFontW(12, 5, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("�޸յձ�������"));
	ITFFONT3 = CreateFontW(16, 8, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("�޸յձ�������"));
	ITFFONT4 = CreateFontW(24, 12, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("�޸յձ�������"));
}

void InterfaceDelete() {
	//�޸� ����
	DeleteObject(ITFBrush1);
	DeleteObject(ITFPen1);
	DeleteObject(ITFFONT1);
	DeleteObject(ITFFONT2);
	DeleteObject(ITFFONT3);
	DeleteObject(ITFFONT4);
}

void ITFBackGround(HDC hdc) {
	//ȸ�� ���� �׸���
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

	//�������̽� ���ڵ� �׸���
	SelectObject(hdc, ITFFONT1);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(0, 0, 0));
	TextOut(hdc, 390, 35, _T("LEVEL"), 5);
	TextOut(hdc, 400, 90, _T("NEXT"), 4);
	TextOut(hdc, 360, 220, _T("CHANGE"), 6);
	TextOut(hdc, 411, 300, _T("LINE"), 4);
	TextOut(hdc, 383, 360, _T("SCORE"), 5);
	

	SelectObject(hdc, ITFFONT2);
	TextOut(hdc, 370, 435, _T("MOVE : ��,��,��"), 12);
	TextOut(hdc, 385, 460, _T("ROTATE : ��"), 10);
	TextOut(hdc, 360, 485, _T("CHANGE : CTRL"), 13);
	TextOut(hdc, 395, 510, _T("QUIT : ESE"), 10);

	SelectObject(hdc, ITFFONT4);
	TextOut(hdc, 365, 550, _T("PAUSE"), 5);
	if (!StartSelect)
		TextOut(hdc, 365, 590, _T("START"), 5);
	else
		TextOut(hdc, 365, 590, _T("RESET"), 5);

	SelectObject(hdc, ITFFONT3);
	//LEVEL ���
	wchar_t TLevel[4];
	swprintf_s(TLevel, L"%d%d%d", 0, Level / 10, Level % 10);
	TextOut(hdc, 425, 65, TLevel, sizeof(TLevel) / sizeof(wchar_t));

	//CHANGE ���
	wchar_t TChange[5];
	int Ch = GetChange();
	swprintf_s(TChange, L"%d%d%d%d", Ch / 1000, Ch % 1000 / 100, Ch % 100 / 10, Ch % 10);
	TextOut(hdc, 415, 250, TChange, sizeof(TChange) / sizeof(wchar_t));
	
	//LINE ���
	wchar_t TLine[5];
	swprintf_s(TLine, L"%d%d%d%d", Line / 1000, Line % 1000 / 100, Line % 100 / 10, Line % 10);
	TextOut(hdc, 415, 330, TLine, sizeof(TLine) / sizeof(wchar_t));
	
	//SCORE ���
	wchar_t TScore[8];
	swprintf_s(TScore, L"%d%d%d%d%d%d%d", Score / 1000000, Score % 1000000 / 100000, Score % 100000 / 10000, Score % 10000 / 1000, Score % 1000 / 100, Score % 100 / 10, Score % 10);
	TextOut(hdc, 378, 390, TScore, sizeof(TScore) / sizeof(wchar_t));

	SelectObject(hdc,BasicBrush);
	SelectObject(hdc, BasicPen);
	SelectObject(hdc, ITFPen2);

	//���� ��� ���� �׸���
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
	//���� ������ �� Level, Line, OldLine, Score�� ���� �ʱ�ȭ
	Level = 1;
	Line = OldLine = Score = 0;
}

void ScoreSet() {
	//Line�� ���� �������� ������ �߰���Ų��.
	Score += ((Line - OldLine) * 500) + (111 * (int)pow(3, Line - OldLine - 1));
	//OldLine�� Line���� ���� ���ش�.
	OldLine = Line;
}

const bool IsScoreUp() {
	//Line�� OldLine�� ���̰� ������ True��ȯ
	if (Line - OldLine != 0)
		return true;
	return false;
}

void LineUp(const int Up) {
	//BlockBreak���� �ı��� �� ��ŭ Line�� ���������ش�.
	Line += Up;
}

const bool LevelSet() {
	//Line�� ���� �������� ������ �ø���.
	if (Line / 7 != Level - 1) {
		Level++;
		return true;
	}
	return false;
}

const int GetLevel() {
	//Level���� ��´�.
	return Level;
}

const int GetScore() {
	//Score���� ��´�.
	return Score;
}

const int SelectStartButton(int Mx, int My) {
	//Start��ư Ŭ���� �����Ѵ�.
	//Start��ư�� ������ Reset���� ����ȴ�.
	//������ �й��ϸ� Reset��ư�� Start��ư���� �ٲ��.

	if (Mx<360 || Mx>475 || My<595 || My>615)
		return 0;

	//Start�϶� ���� ��� 1�� �ٲ۴�.
	//Reset��ư���� �ٲ�Եȴ�.
	if (!StartSelect) {
		ClickStartButton();
		return 1;
	}
	//Reset��ư�϶� ���� ���
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
	//���� ��� true/false ��ȯ
	if (Mx < 360 || Mx>475 || My < 555 || My>575)
		return false;
	PlaySound(MAKEINTRESOURCE(IDR_WAVE3), NULL, SND_RESOURCE | SND_ASYNC);
	return true;
}

const bool GetStartSelect() {
	return StartSelect;
}