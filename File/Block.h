#pragma once

//������ O,I,S,Z,L,J,T

struct BLOCK{
	int Shape = 0;
	POINT Pos[4] = { 0, };
	bool NEmpty[4] = { true, };
	int Rotate = 0;
	bool Create = false;
};
//����� POS�� �߽���ǥ�Դϴ�.
//X,Y���Դϴ�.

static HBRUSH BLBrush[7];
static int Map[21][11];
static int NextShape;
static int Select, NextSelect;
static int Change, MaxChange;

//�ʱ�ȭ, ����, ���� ����
void MapInit();
void BlockColorCreate();
void BlockColorDelete();

//��� ���� ����
void BlockCreate(BLOCK* Block);
void NextBlockCreate(BLOCK* block);
void BlockShapeSetting(BLOCK* Block);

//���� Shape,Select����
void SInit(BLOCK* Block);
void SelectChange(BLOCK* Block);
const int GetSelect();
const int GetNextSelect();

//��� �̵�, ȸ�� ����
bool BlockRotate(BLOCK* Block);
const bool RotateCheck(const BLOCK* Block);
const bool MoveCheck(const BLOCK* Block);
const bool BlockMoveL(BLOCK* Block);
const bool BlockMoveR(BLOCK* Block);
const bool BlockMoveD(BLOCK* Block);

//��� �׸���, �� üũ
void BlockDraw(HDC hdc, const BLOCK* Block);
void MapCheckFirst(const BLOCK* Block);

//��� �ı� ����
const int BlockBreak(BLOCK* Block);
void BlockReset(BLOCK* Block);
void BlockDelete(BLOCK* Block);

//��� ü���� ����
void BlockChange(BLOCK* Block);
void ChangeUp(const int Score);
const int GetChange();




