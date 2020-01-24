#pragma once

static HBRUSH BasicBrush;
static HBRUSH ITFBrush1;

static HPEN BasicPen;
static HPEN ITFPen1;
static HPEN ITFPen2;

static HFONT ITFFONT1;
static HFONT ITFFONT2;
static HFONT ITFFONT3;
static HFONT ITFFONT4;

static int Level;
static int Line, OldLine;
static int Score;
static bool StartSelect = false;

//인터페이스 생성, 구현, 삭제
void InterfaceCreate();
void InterfaceDelete();
void ITFBackGround(HDC hdc);

//Score, Line, Level 관련
void CreateNumber();
void ScoreSet();
const bool IsScoreUp();
void LineUp(const int Up);
const bool LevelSet();
const int GetLevel();
const int GetScore();

//Start및 Pause버튼 구현
const int SelectStartButton(int Mx, int My);
void ClickStartButton();
const bool SelectPauseButton(int Mx, int My);
const bool GetStartSelect();
