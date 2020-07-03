#include "Resource.h"

void MapInit() {
	//Map을 -1로 초기화한다.
	//Map은 각 칸에 몇번째 블록이 있는지 저장되어있는 배열이다.
	memset(Map, -1, sizeof(Map));
}

void BlockColorCreate() {
	BLBrush[0] = CreateSolidBrush(RGB(250, 237, 125));
	BLBrush[1] = CreateSolidBrush(RGB(179, 235, 244));
	BLBrush[2] = CreateSolidBrush(RGB(183, 240, 177));
	BLBrush[3] = CreateSolidBrush(RGB(255, 167, 167));
	BLBrush[4] = CreateSolidBrush(RGB(255, 193, 158));
	BLBrush[5] = CreateSolidBrush(RGB(178, 204, 255));
	BLBrush[6] = CreateSolidBrush(RGB(255, 178, 245));
}

void BlockColorDelete() {
	for(int i=0; i<7; i++)
		DeleteObject(BLBrush[i]);
}

void BlockCreate(BLOCK* Block) {
	
	Block->Shape = NextShape;
	Block->Pos[0] = { 190,40 };
	Block->Pos[1] = { 190,70 };
	for (int i = 0; i < 4; i++)
		Block->NEmpty[i] = true;
	Block->Rotate = 0;
	Block->Create = true;
	BlockShapeSetting(Block);
}

void NextBlockCreate(BLOCK* Block) {
	Block->Shape = NextShape;
	//Select별로 Pos값과 Rotate값을 따로 배정해줘야한다.
	//안그러면 너무 안이쁜데
	if (Block->Shape == 2) {
		Block->Pos[0] = { 427,130 };
		Block->Pos[1] = { 427,160 };
	}
	else if (Block->Shape == 6)
		Block->Pos[0] = { 427,160 };
	else if (Block->Shape == 1)
		Block->Pos[0] = { 430,150 };
	else
		Block->Pos[0] = { 400,160 };
	for (int i = 0; i < 4; i++)
		Block->NEmpty[i] = true;
	Block->Rotate = 1;
	Block->Create = true;
	BlockShapeSetting(Block);
}

void BlockShapeSetting(BLOCK* Block) {
	//블록 모양 설정
	//블록 생성할때 블록 회전할때등 사용된다.
	switch (Block->Shape) {
	case 1:
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++) {
				Block->Pos[i * 2 + j].y = Block->Pos[0].y + i * 30;
				Block->Pos[i * 2 + j].x = Block->Pos[0].x - j * 30;
			}
		break;
	case 2:
		if (Block->Rotate % 2 == 0) {
			Block->Pos[0].y = Block->Pos[1].y - 30;
			Block->Pos[2].y = Block->Pos[1].y + 30;
			Block->Pos[3].y = Block->Pos[2].y + 30;
			Block->Pos[0].x = Block->Pos[2].x = Block->Pos[3].x = Block->Pos[1].x;
		}
		else {
			Block->Pos[0].x = Block->Pos[1].x + 30;
			Block->Pos[2].x = Block->Pos[1].x - 30;
			Block->Pos[3].x = Block->Pos[2].x - 30;
			Block->Pos[0].y = Block->Pos[2].y = Block->Pos[3].y = Block->Pos[1].y;
		}
		break;
	case 3:
		if (Block->Rotate%2 == 0) {
			Block->Pos[1].x = Block->Pos[0].x + 30;
			Block->Pos[2].x = Block->Pos[0].x;
			Block->Pos[3].x = Block->Pos[0].x - 30;
			Block->Pos[1].y = Block->Pos[0].y;
			Block->Pos[2].y = Block->Pos[3].y = Block->Pos[0].y + 30;
		}
		else {
			Block->Pos[1].x = Block->Pos[0].x;
			Block->Pos[2].x = Block->Pos[3].x = Block->Pos[0].x + 30;
			Block->Pos[1].y = Block->Pos[0].y - 30;
			Block->Pos[2].y = Block->Pos[0].y;
			Block->Pos[3].y = Block->Pos[0].y + 30;
		}
		break;
	case 4:
		if (Block->Rotate%2 == 0) {
			Block->Pos[1].x = Block->Pos[0].x - 30;
			Block->Pos[2].x = Block->Pos[0].x;
			Block->Pos[3].x = Block->Pos[0].x + 30;
			Block->Pos[1].y = Block->Pos[0].y;
			Block->Pos[2].y = Block->Pos[3].y = Block->Pos[0].y + 30;
		}
		else {
			Block->Pos[1].x = Block->Pos[0].x;
			Block->Pos[2].x = Block->Pos[3].x = Block->Pos[0].x + 30;
			Block->Pos[1].y = Block->Pos[0].y + 30;
			Block->Pos[2].y = Block->Pos[0].y;
			Block->Pos[3].y = Block->Pos[0].y - 30;
		}
		break;
	case 5:
		for (int i = 0; i < 4; i++) {
			if (Block->Rotate == i) {
				Block->Pos[1].x = Block->Pos[0].x + ((i + 1) % 2) * (1 - i) * 30;
				Block->Pos[1].y = Block->Pos[0].y + (i % 2) * (2 - i) * 30;
				Block->Pos[2].x = Block->Pos[0].x * 2 - Block->Pos[1].x;
				Block->Pos[2].y = Block->Pos[0].y * 2 - Block->Pos[1].y;
				Block->Pos[3].x = Block->Pos[0].x + ((i == 0 || i == 3) ? -30 : 30);
				Block->Pos[3].y = Block->Pos[0].y + ((i / 2 == 0) ? 30 : -30);
			}
		}
		break;
	case 6:
		for (int i = 0; i < 4; i++) {
			if (Block->Rotate == i) {
				Block->Pos[1].x = Block->Pos[0].x - ((i + 1) % 2) * (1 - i) * 30;
				Block->Pos[1].y = Block->Pos[0].y + (i % 2) * (2 - i) * 30;
				Block->Pos[2].x = Block->Pos[0].x * 2 - Block->Pos[1].x;
				Block->Pos[2].y = Block->Pos[0].y * 2 - Block->Pos[1].y;
				Block->Pos[3].x = Block->Pos[0].x - ((i == 0 || i == 3) ? -30 : 30);
				Block->Pos[3].y = Block->Pos[0].y + ((i / 2 == 0) ? 30 : -30);
			}
		}
		break;
	case 7:
		for (int i = 0; i < 4; i++) {
			if (Block->Rotate == i) {
				Block->Pos[1].x = Block->Pos[0].x + ((i + 1) % 2) * (1 - i) * 30;
				Block->Pos[1].y = Block->Pos[0].y - (i % 2) * (2 - i) * 30;
				Block->Pos[2].x = Block->Pos[0].x + (i % 2) * (2 - i) * 30;
				Block->Pos[2].y = Block->Pos[0].y + ((i + 1) % 2) * (1 - i) * 30;
				Block->Pos[3].x = Block->Pos[0].x * 2 - Block->Pos[1].x;
				Block->Pos[3].y = Block->Pos[0].y * 2 - Block->Pos[1].y;
			}
		}
		break;
	}
}

void SInit(BLOCK* Block) {
	Select = 0;
	NextShape = rand() % 7 + 1;
	BlockCreate(&Block[Select]);
	NextSelect = 1;
	NextShape = rand() % 7 + 1;
	NextBlockCreate(&Block[NextSelect]);
	Change = 0;
	MaxChange = 3;
}

void SelectChange(BLOCK* Block) {
	if (!BlockMoveD(&Block[Select])) {
		MapCheckFirst(&Block[Select]);
		//Next에 있는거 Select로 설정하기
		Select = NextSelect;
		BlockCreate(&Block[Select]);
		//다음 나올거 생성
		for (int i = 0; i < 200; i++) {
			if (!Block[i].Create) {
				NextShape = rand() % 7 + 1;
				NextBlockCreate(&Block[i]);
				NextSelect = i;
				break;
			}
		}
	}
}

const int GetSelect() {
	return Select;
}

const int GetNextSelect() {
	//NextSelect를 얻는다.
	return NextSelect;
}

bool BlockRotate(BLOCK* Block) {
	//RotateCheck를 통해서 돌릴 수 있는지 판단하자.

	//돌릴 수 있다면 돌려주자!
	Block->Rotate++;
	Block->Rotate %= 4;
	BlockShapeSetting(Block);
	if (!MoveCheck(Block) || !RotateCheck(Block)) {
		Block->Rotate--;
		if (Block->Rotate == -1)
			Block->Rotate = 3;
		BlockShapeSetting(Block);
		return false;
	}
	return true;
}

const bool RotateCheck(const BLOCK* Block)
{
	//모든 회전은 MoveCheck에서 처리하지만 예외적으로 제일 위에서 회전하는 건 여기서 처리한다.
	for (int i = 0; i < 4; i++) 
		if (Block->Pos[i].y < 25)
			return false;

	return true;
}

const bool MoveCheck(const BLOCK* Block) {
	//밑에 블록이 있다던가 맵 밖으로 이동하려는 경우를 막아준다.

	//맵으로 인한 좌우 이동 불/가 판단
	for (int i = 0; i < 4; i++) 
		if (Block->Pos[i].x < 25 || Block->Pos[i].x > 325)
			return false;

	//맵으로 인한 아래쪽 이동 불/가 판단
	for (int i = 0; i < 4; i++)
		if (Block->Pos[i].y > 625)
			return false;
	
	//블록으로 인한 아래쪽 이동 불/가 판단
	for (int i = 0; i < 4; i++) {
		int y = (Block->Pos[i].y - 10) / 30;
		int x = (Block->Pos[i].x - 10) / 30;
		if (Map[y - 1][x - 1] != -1)
			return false;
	}
		
	//맵을 배열로 만들어놓자.
	return true;
}

const bool BlockMoveL(BLOCK* Block) {
	//현재 선택된 블록을 왼쪽으로 움직이게 해주는 함수.

	//먼저 블록을 이동시켜 준다.
	for (int i = 0; i < 4; i++)
		Block->Pos[i].x -= 30;
	//이동이 안되면 다시 원래대로 돌려준다.
	if (!MoveCheck(Block)) {
		for (int i = 0; i < 4; i++)
			Block->Pos[i].x += 30;
		return false;
	}
	return true;
}

const bool BlockMoveR(BLOCK* Block) {
	//현재 선택된 블록을 오른쪽으로 움직이게 해주는 함수.

	//먼저 블록을 이동시켜 준다.
	for (int i = 0; i < 4; i++)
		Block->Pos[i].x += 30;
	//이동이 안되면 다시 원래대로 돌려준다.
	if (!MoveCheck(Block)) {
		for (int i = 0; i < 4; i++)
			Block->Pos[i].x -= 30;
		return false;
	}
	return true;
}

const bool BlockMoveD(BLOCK* Block) {
	//현재 선택된 블록을 아래쪽으로 움직이게 해주는 함수.
	for (int i = 0; i < 4; i++)
		Block->Pos[i].y += 30;
	//이동이 안되면 다시 원래대로 돌려준다.
	if (!MoveCheck(Block)) {
		for (int i = 0; i < 4; i++)
			Block->Pos[i].y -= 30;
		return false;
	}
	return true;
}

void BlockDraw(HDC hdc, const BLOCK* Block) {

	for (int b = 0; b < 200; b++) {
		//블록이 생성되지 않았다면
		if (!Block[b].Create)
			continue;

		//Shape의 색깔대로 SolidColor를 지정해주자.
		SelectObject(hdc, BLBrush[Block[b].Shape - 1]);

		for (int i = 0; i < 4; i++)
			if (Block[b].NEmpty[i])
				Rectangle(hdc, Block[b].Pos[i].x - 15, Block[b].Pos[i].y - 15, Block[b].Pos[i].x + 15, Block[b].Pos[i].y + 15);
	}
}

void MapCheckFirst(const BLOCK* Block) {
	//Select된 블록이 더 이상 움직이지 않을때.
	for (int i = 0; i < 4; i++) {
		int y = ((Block->Pos[i].y - 10) / 30) - 1;
		int x = ((Block->Pos[i].x - 10) / 30) - 1;
		Map[y][x] = Select;
	}
}

const int BlockBreak(BLOCK* Block) {
	//각 줄을 검사해서 줄이 꽉차면 LINE 변수의 값을 1씩 올려준다.
	int LINE = 0;
	for (int y = 19; y >= 0; y--) {
		bool Destory = true;
		//줄 검사 줄의 Map값이 모두 true면 Destory는 true 아니면 false로 변환된다.
		for (int x = 0; x < 10; x++) {
			if (Map[y][x] == -1 && Destory)
				Destory = false;
		}
		//Destory값을 가지고 지울지 안지울지 판단한다.
		if (Destory) {
			//NEmpty[4]중 Destory될 줄에 포함이 되면 NEmpty값을 true로 바꾼다.
			for (int x = 0; x < 10; x++) {
				for (int i = 0; i < 4; i++) {
					//그 블록의 Pos값을 구해서 Map의 y값과 x값과 비교
					if (((Block[Map[y][x]].Pos[i].x - 10) / 30 == x + 1) && ((Block[Map[y][x]].Pos[i].y - 10) / 30 == y + 1)) {
						Block[Map[y][x]].NEmpty[i] = false;
						Block[Map[y][x]].Pos[i].y = 900;						
					}
				}
			}
			//그리고 그 줄을 지워주고 위에 줄들을 한칸씩 떙긴다.
			for (int My = y; My > 0; My--) {
				for (int Mx = 0; Mx < 10; Mx++) {
					Map[My][Mx] = Map[My - 1][Mx];
					for (int i = 0; i < 4; i++) 
						if (((Block[Map[My][Mx]].Pos[i].y - 10) / 30 == My)&& ((Block[Map[My][Mx]].Pos[i].x - 10) / 30 == Mx+1))
							Block[Map[My][Mx]].Pos[i].y += 30;
				}
			}

			//줄이 땡겨졌기 때문에 이번 줄을 다시 검사해야하므로 y를 1늘린다.
			y++;
			LINE++;
		}
	}
	//점수 계산은 여기서 계산된 LINE 값으로 함수 밖에서 계산한다.
	return LINE;
}

void BlockReset(BLOCK* Block) {
	//Reset버튼을 누르면 실행 되는 함수로
	//모든 Create를 false로 바꿔주어서 화면에 출력이 되지 않게한다.
	for (int i = 0; i < 200; i++)
		if (Block[i].Create)
			Block[i].Create = false;
}

void BlockDelete(BLOCK* Block) {
	//Create된 블럭들만 검사한다.
	for (int Select = 0; Select < 200; Select++) {
		if (!Block[Select].Create)
			continue;
		bool Pass = true;
		//선택된 블록의 NEmpty를 검사한다.
		//모두 false면 화면상에 없는 상태로 Create를 false로 바꿔준후, 새로운 블록을 받을 준비를 한다.
		for (int i = 0; i < 4; i++)
			if (Block[Select].NEmpty[i])
				Pass = false;
		if (Pass)
			Block[Select].Create = false;
	}
}

void BlockChange(BLOCK* Block) {
	if (MaxChange != Change) {
		PlaySound(MAKEINTRESOURCE(IDR_WAVE4), NULL, SND_RESOURCE | SND_ASYNC);
		while (1) {
			//블록 형태가 겹칠 수 있으므로 겹치지 않을 때 까지 While 문으로 돌려준다.
			int ret = NextShape;
			NextShape = rand() % 7 + 1;
			if (NextShape != ret) {
				Change++;
				NextBlockCreate(Block);
				break;
			}
		}
	}
}

void ChangeUp(const int Score) {
	//Score10000점당 3개 증가
	MaxChange = Score / 10000 * 3 + 3;
}

const int GetChange() {
	//Change값을 얻늗다.
	return MaxChange - Change;
}