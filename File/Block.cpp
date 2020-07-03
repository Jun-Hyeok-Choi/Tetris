#include "Resource.h"

void MapInit() {
	//Map�� -1�� �ʱ�ȭ�Ѵ�.
	//Map�� �� ĭ�� ���° ����� �ִ��� ����Ǿ��ִ� �迭�̴�.
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
	//Select���� Pos���� Rotate���� ���� ����������Ѵ�.
	//�ȱ׷��� �ʹ� ���̻۵�
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
	//��� ��� ����
	//��� �����Ҷ� ��� ȸ���Ҷ��� ���ȴ�.
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
		//Next�� �ִ°� Select�� �����ϱ�
		Select = NextSelect;
		BlockCreate(&Block[Select]);
		//���� ���ð� ����
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
	//NextSelect�� ��´�.
	return NextSelect;
}

bool BlockRotate(BLOCK* Block) {
	//RotateCheck�� ���ؼ� ���� �� �ִ��� �Ǵ�����.

	//���� �� �ִٸ� ��������!
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
	//��� ȸ���� MoveCheck���� ó�������� ���������� ���� ������ ȸ���ϴ� �� ���⼭ ó���Ѵ�.
	for (int i = 0; i < 4; i++) 
		if (Block->Pos[i].y < 25)
			return false;

	return true;
}

const bool MoveCheck(const BLOCK* Block) {
	//�ؿ� ����� �ִٴ��� �� ������ �̵��Ϸ��� ��츦 �����ش�.

	//������ ���� �¿� �̵� ��/�� �Ǵ�
	for (int i = 0; i < 4; i++) 
		if (Block->Pos[i].x < 25 || Block->Pos[i].x > 325)
			return false;

	//������ ���� �Ʒ��� �̵� ��/�� �Ǵ�
	for (int i = 0; i < 4; i++)
		if (Block->Pos[i].y > 625)
			return false;
	
	//������� ���� �Ʒ��� �̵� ��/�� �Ǵ�
	for (int i = 0; i < 4; i++) {
		int y = (Block->Pos[i].y - 10) / 30;
		int x = (Block->Pos[i].x - 10) / 30;
		if (Map[y - 1][x - 1] != -1)
			return false;
	}
		
	//���� �迭�� ��������.
	return true;
}

const bool BlockMoveL(BLOCK* Block) {
	//���� ���õ� ����� �������� �����̰� ���ִ� �Լ�.

	//���� ����� �̵����� �ش�.
	for (int i = 0; i < 4; i++)
		Block->Pos[i].x -= 30;
	//�̵��� �ȵǸ� �ٽ� ������� �����ش�.
	if (!MoveCheck(Block)) {
		for (int i = 0; i < 4; i++)
			Block->Pos[i].x += 30;
		return false;
	}
	return true;
}

const bool BlockMoveR(BLOCK* Block) {
	//���� ���õ� ����� ���������� �����̰� ���ִ� �Լ�.

	//���� ����� �̵����� �ش�.
	for (int i = 0; i < 4; i++)
		Block->Pos[i].x += 30;
	//�̵��� �ȵǸ� �ٽ� ������� �����ش�.
	if (!MoveCheck(Block)) {
		for (int i = 0; i < 4; i++)
			Block->Pos[i].x -= 30;
		return false;
	}
	return true;
}

const bool BlockMoveD(BLOCK* Block) {
	//���� ���õ� ����� �Ʒ������� �����̰� ���ִ� �Լ�.
	for (int i = 0; i < 4; i++)
		Block->Pos[i].y += 30;
	//�̵��� �ȵǸ� �ٽ� ������� �����ش�.
	if (!MoveCheck(Block)) {
		for (int i = 0; i < 4; i++)
			Block->Pos[i].y -= 30;
		return false;
	}
	return true;
}

void BlockDraw(HDC hdc, const BLOCK* Block) {

	for (int b = 0; b < 200; b++) {
		//����� �������� �ʾҴٸ�
		if (!Block[b].Create)
			continue;

		//Shape�� ������ SolidColor�� ����������.
		SelectObject(hdc, BLBrush[Block[b].Shape - 1]);

		for (int i = 0; i < 4; i++)
			if (Block[b].NEmpty[i])
				Rectangle(hdc, Block[b].Pos[i].x - 15, Block[b].Pos[i].y - 15, Block[b].Pos[i].x + 15, Block[b].Pos[i].y + 15);
	}
}

void MapCheckFirst(const BLOCK* Block) {
	//Select�� ����� �� �̻� �������� ������.
	for (int i = 0; i < 4; i++) {
		int y = ((Block->Pos[i].y - 10) / 30) - 1;
		int x = ((Block->Pos[i].x - 10) / 30) - 1;
		Map[y][x] = Select;
	}
}

const int BlockBreak(BLOCK* Block) {
	//�� ���� �˻��ؼ� ���� ������ LINE ������ ���� 1�� �÷��ش�.
	int LINE = 0;
	for (int y = 19; y >= 0; y--) {
		bool Destory = true;
		//�� �˻� ���� Map���� ��� true�� Destory�� true �ƴϸ� false�� ��ȯ�ȴ�.
		for (int x = 0; x < 10; x++) {
			if (Map[y][x] == -1 && Destory)
				Destory = false;
		}
		//Destory���� ������ ������ �������� �Ǵ��Ѵ�.
		if (Destory) {
			//NEmpty[4]�� Destory�� �ٿ� ������ �Ǹ� NEmpty���� true�� �ٲ۴�.
			for (int x = 0; x < 10; x++) {
				for (int i = 0; i < 4; i++) {
					//�� ����� Pos���� ���ؼ� Map�� y���� x���� ��
					if (((Block[Map[y][x]].Pos[i].x - 10) / 30 == x + 1) && ((Block[Map[y][x]].Pos[i].y - 10) / 30 == y + 1)) {
						Block[Map[y][x]].NEmpty[i] = false;
						Block[Map[y][x]].Pos[i].y = 900;						
					}
				}
			}
			//�׸��� �� ���� �����ְ� ���� �ٵ��� ��ĭ�� �����.
			for (int My = y; My > 0; My--) {
				for (int Mx = 0; Mx < 10; Mx++) {
					Map[My][Mx] = Map[My - 1][Mx];
					for (int i = 0; i < 4; i++) 
						if (((Block[Map[My][Mx]].Pos[i].y - 10) / 30 == My)&& ((Block[Map[My][Mx]].Pos[i].x - 10) / 30 == Mx+1))
							Block[Map[My][Mx]].Pos[i].y += 30;
				}
			}

			//���� �������� ������ �̹� ���� �ٽ� �˻��ؾ��ϹǷ� y�� 1�ø���.
			y++;
			LINE++;
		}
	}
	//���� ����� ���⼭ ���� LINE ������ �Լ� �ۿ��� ����Ѵ�.
	return LINE;
}

void BlockReset(BLOCK* Block) {
	//Reset��ư�� ������ ���� �Ǵ� �Լ���
	//��� Create�� false�� �ٲ��־ ȭ�鿡 ����� ���� �ʰ��Ѵ�.
	for (int i = 0; i < 200; i++)
		if (Block[i].Create)
			Block[i].Create = false;
}

void BlockDelete(BLOCK* Block) {
	//Create�� ���鸸 �˻��Ѵ�.
	for (int Select = 0; Select < 200; Select++) {
		if (!Block[Select].Create)
			continue;
		bool Pass = true;
		//���õ� ����� NEmpty�� �˻��Ѵ�.
		//��� false�� ȭ��� ���� ���·� Create�� false�� �ٲ�����, ���ο� ����� ���� �غ� �Ѵ�.
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
			//��� ���°� ��ĥ �� �����Ƿ� ��ġ�� ���� �� ���� While ������ �����ش�.
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
	//Score10000���� 3�� ����
	MaxChange = Score / 10000 * 3 + 3;
}

const int GetChange() {
	//Change���� ��f��.
	return MaxChange - Change;
}