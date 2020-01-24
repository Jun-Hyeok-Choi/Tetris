#pragma once

//순서는 O,I,S,Z,L,J,T

struct BLOCK{
	int Shape = 0;
	POINT Pos[4] = { 0, };
	bool NEmpty[4] = { true, };
	int Rotate = 0;
	bool Create = false;
};
//참고로 POS는 중심좌표입니다.
//X,Y순입니다.

static HBRUSH BLBrush[7];
static int Map[21][11];
static int NextShape;
static int Select, NextSelect;
static int Change, MaxChange;

//초기화, 시작, 종료 관련
void MapInit();
void BlockColorCreate();
void BlockColorDelete();

//블록 생성 관련
void BlockCreate(BLOCK* Block);
void NextBlockCreate(BLOCK* block);
void BlockShapeSetting(BLOCK* Block);

//변수 Shape,Select관련
void SInit(BLOCK* Block);
void SelectChange(BLOCK* Block);
const int GetSelect();
const int GetNextSelect();

//블록 이동, 회전 관련
bool BlockRotate(BLOCK* Block);
const bool RotateCheck(const BLOCK* Block);
const bool MoveCheck(const BLOCK* Block);
const bool BlockMoveL(BLOCK* Block);
const bool BlockMoveR(BLOCK* Block);
const bool BlockMoveD(BLOCK* Block);

//블록 그리기, 맵 체크
void BlockDraw(HDC hdc, const BLOCK* Block);
void MapCheckFirst(const BLOCK* Block);

//블록 파괴 관련
const int BlockBreak(BLOCK* Block);
void BlockReset(BLOCK* Block);
void BlockDelete(BLOCK* Block);

//블록 체인지 관련
void BlockChange(BLOCK* Block);
void ChangeUp(const int Score);
const int GetChange();




