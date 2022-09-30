#include "main.h"



extern mutex m;
extern char TempMap[27][68];
extern Character MyCharacter;
int Battle_log_row = MIN_BATTLE_LOG_ROW;

bool FLAG_mapUpdate = false;		// true - ���� ������Ʈ �ض�
bool FLAG_infoWindowUpdate = false; // true - ĳ���� ����â ������Ʈ �ض�
bool FLAG_using_store = false;		// true - ���� ������ �̿����̴�
bool FLAG_playing_battle = false;	// true - ���� ���Ϳ� �������̴�
bool FLAG_Monster_Observation = false; // true - �����ϱ⸦ �̿��� ���� �߰������� ���� ���̴�.


//Game::Game()
//{
//	//cout << "������ �����մϴ�" << endl;
//}
string Game::Class_ItoS(char chractor_class)			// int���� �ް� string���� ��ȯ
{
	if (chractor_class == ONE)
		return "����";
	else if (chractor_class == TWO)
		return "�ü�";
	else if (chractor_class == THREE)
		return "������";
	else
		return "�����Ⱚ ���ø��� ����!";	// << ���ü����� ¥����

}
//=====================================================
// ���� �� - ���� ȭ�鿡 ���õ� �Լ���
//=====================================================
int Game::Initial_Game_State()					
{
	int game_state = INIT_GAME;
	while (1) {
		switch (game_state)
		{
		case INIT_GAME:
			game_state = Init_Screen();		// ���� ȭ��
			break;

		case NEW_GAME_START:				// ĳ���� ����ȭ������
			game_state = Character_Create_Screen();
			break;

		case CONTINUE_GAME_START:			
			//break;

		case GAME_INFO:
			game_state = GameInfo_Screen();
			break;

		case GAME_PLAYING_STATE:			// ���� ����State���� �Ѿ
			game_state = Playing_Game_State();
			break;

		case GAME_EXIT:						// ���� ����
			return GAME_EXIT;	
		}
	}
}
int Game::Init_Screen()									// ���� �ʱ� ���۽�, state�� ���� ȭ�� ��� �� ���
{
	system("mode con cols=70 lines=30"); // ���߿� ��������â�� ũ�Ⱑ ��������� �ּ��� Ǯ� �� ��.
	system("cls");
	setcolor(WHITE, BLACK);
	cout << "\n";
	cout << "    �������������������������������\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��           ---------------------------------            ��\n";
	cout << "    ��          |            ����Ű���           |           ��\n";
	cout << "    ��          |             -������-            |           ��\n";
	cout << "    ��           ---------------------------------            ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                     1. �� ���ӽ���                     ��\n";
	cout << "    ��                     2. �ҷ�����(�̱���)                ��\n";
	cout << "    ��                     3. ���Ӽ���                        ��\n";
	cout << "    ��                     4. ��������                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    �������������������������������\n";

	gotoxy(21, 14);
	cout << " ������ ���ڸ� �����ּ���.";

	int Set_Color = BLACK;
	unsigned char input =0;

	while (1) {
		
		switch (input = Avoid_Garbage_getch())
		{
		case ONE:
			//cout << "�� ���ӽ���" << endl;
			return NEW_GAME_START;

		case TWO:
			//cout << "�ҷ�����" << endl;
			return CONTINUE_GAME_START;

		case THREE:
			//cout << "���Ӽ���" << endl;
			return GAME_INFO;

		case FOUR:
			//cout << "��������" << endl;
			return GAME_EXIT;

		default:
			Set_Color %= MAX_CONSOLE_COLOR_NUM;
			gotoxy(15, 20); setcolor(Set_Color, WHITE);	// ��� ��ġ����, ������
			if (input >= MAX_ASCII_NUM)	// �ƽ�Ű�� �Ѵ� �ѱ��� ǥ��			
				cout << "<�ѱ�>�� �Է��Ͽ����ϴ�. �ٽ� �����ּ���" << endl;
			else
				cout << "< " << input << " >�� �Է��Ͽ����ϴ�. �ٽ� �����ּ��� " << endl;
			setcolor(WHITE, BLACK);
			Set_Color++;
			break;
		}
		
	}

}
int Game::Character_Create_Screen()						// ĳ���� ���� ȭ�� (�г���, ���� ����)
{
	string name;
	unsigned char character_class = 0;
	Init_Game_Frame();

	gotoxy(23, 3); cout << "=======================";
	gotoxy(23, 4); cout << "      ĳ���� ����";
	gotoxy(23, 5); cout << "=======================";

	gotoxy(18, 7); cout << "����� �г��� �Է� :";
	gotoxy(15, 8); cout << "���� ����[1. ����, 2. �ü�, 3. ������] :";

	do
	{
		gotoxy(40, 7); cin >> name;
		if (name.size() > 20)
		{
			gotoxy(22, 11);cout << "�г����� �ִ� 10�����Դϴ�";	// �ѱ۱��� 10����
			gotoxy(40, 7); cout << "                      ��     "; // �г��� ���� �����
		}
		else break;
	} while (true);
	
	
	do
	{
		character_class = Avoid_Garbage_getch();
		gotoxy(15, 11);
		if (character_class >= MAX_ASCII_NUM)	// �ƽ�Ű�� �Ѵ� �ѱ��� ǥ��
		{
			 cout << "<�ѱ�>�� �Է��Ͽ����ϴ�. ����� �Է��ϼ���";
		}
		else
		{
			 cout << "< " << character_class << " >�� �Է��Ͽ����ϴ�. �ٽ� �����ּ���   ";
		}
	} while (character_class < ONE || THREE < character_class);	// ���� ���� (1~3)


	
	Init_Game_Frame();
	gotoxy(23, 6); cout << "=======================";
	gotoxy(23, 7); cout << "   �г��� :  " << name;
	gotoxy(23, 8); cout << "   ��  �� :  " << Class_ItoS(character_class);
	gotoxy(23, 9); cout << "=======================" << endl;


	gotoxy(26, 13); setcolor(BLACK, WHITE);
	cout << "�����Ͻðڽ��ϱ�?";
	gotoxy(24, 14); setcolor(BLACK, WHITE);
	cout << "<1. ��>   <2. �ƴϿ�>";
	gotoxy(12, 18); setcolor(BLACK, WHITE);
	cout << "�����̽��ٸ� ������ ����ȭ������ �̵��մϴ�.";
	setcolor(WHITE, BLACK);


	int Set_Color = BLACK;
	unsigned char input = 0;

	while (1) 
	{
		switch (input = Avoid_Garbage_getch())
		{
		case ONE:
			MyCharacter.SetName(name);
			MyCharacter.SetClass(character_class);
			return GAME_PLAYING_STATE;

		case TWO:
			return NEW_GAME_START;

		case SPACE_BAR:
			//cout << "<" << input <<"> ����ȭ������ �̵� " << endl;
			return INIT_GAME;

		default:
			Set_Color %= MAX_CONSOLE_COLOR_NUM;
			gotoxy(15, 20); setcolor(Set_Color++, WHITE);	// ��� ��ġ����, ������	
			if (input >= MAX_ASCII_NUM)	// �ƽ�Ű�� �Ѵ� �ѱ��� ǥ��
				cout << "<�ѱ�>�� �Է��Ͽ����ϴ�. ����� �Է��ϼ���";
			else
				cout << "< " << input << " >�� �Է��Ͽ����ϴ�. �ٽ� �����ּ���   ";	
			setcolor(WHITE, BLACK);
			break;
		}
		
	}
}
int Game::GameInfo_Screen()			// ���Ӽ���â
{
	system("cls");
	cout << "\n";
	cout << "    �������������������������������\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                      �ذ��Ӹ�ǥ��                      ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                    �������� �����ؼ�                   ��\n";
	cout << "    ��                  10���� ������ Ż������                ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                   ����Ű : W A S D                     ��\n";
	cout << "    ��               ���ѱ��Է�����(��/�� ������)             ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    �������������������������������\n";

	gotoxy(12, 18); setcolor(BLACK, WHITE);
	cout << "�����̽��ٸ� ������ ����ȭ������ �̵��մϴ�.";
	setcolor(WHITE, BLACK);

	int Set_Color = BLACK;
	unsigned char input=0;

	while (1) {
		
		switch (input = Avoid_Garbage_getch())
		{
		case SPACE_BAR:
			//cout << "<" << input <<"> ����ȭ������ �̵� " << endl;
			return INIT_GAME;

		default:
			Set_Color %= MAX_CONSOLE_COLOR_NUM;
			gotoxy(15, 20); setcolor(Set_Color, WHITE);	// ��� ��ġ����, ������
			if (input >= MAX_ASCII_NUM)	// �ƽ�Ű�� �Ѵ� �ѱ��� ǥ��			
				cout << "<�ѱ�>�� �Է��Ͽ����ϴ�. �ٽ� �����ּ���" << endl;
			else
				cout << "< " << input << " >�� �Է��Ͽ����ϴ�. �ٽ� �����ּ��� " << endl;
			setcolor(WHITE, BLACK);
			Set_Color++;
			break;
		}
		
	}

}
void Game::Init_Game_Frame()
{
	system("cls");
	cout << "\n";
	cout << "    �������������������������������\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    ��                                                        ��\n";
	cout << "    �������������������������������\n";
}


//=====================================================
// �� - ��ü ȭ�� �� �÷��̿� ���õ� �Լ���
//=====================================================
int Game::Playing_Game_State()
{
	int game_state = PLAYING_GAME;
	while (1) {
		switch (game_state)
		{
		case PLAYING_GAME:
			game_state = Playing_Game_Process();
			break;

		case INTIAL_GAME_STATE:
			return INTIAL_GAME_STATE;
		}
	}
}
int Game::Playing_Game_Process()
{

	int Set_Color = BLACK;	 //	BLACK = 0 �ʱⰪ
	int dungeonStage = 1;	 // ���� '1'�ܰ� �ʱⰪ
	int using_infoWindowType = 'U';	// U - ĳ���ͻ���â, I - �κ��丮â, �ʱ�� ĳ������â
	unsigned char input = 0; // Ű�Է°� '0' �ʱⰪ

	// ó��ȭ�� ���
	Playing_Game_Frame();
	Character_Info_Window(using_infoWindowType, dungeonStage);
	Make_Map_Dungeon(dungeonStage);


	// ���� ���� �� Ű�Է� 
	while (1) {
		
		if (FLAG_mapUpdate)			// ���� �������� ���� ��, �� ������Ʈ 
		{
			FLAG_mapUpdate = false;
			Make_Map_Dungeon(dungeonStage);
		}

		if (FLAG_infoWindowUpdate)	// ĳ�� ����â ������Ʈ(�����̿�, �������̿��)
		{
			FLAG_infoWindowUpdate = false;
			Character_Info_Window(using_infoWindowType, dungeonStage);
		}

		switch (input = _getch())
		{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			FLAG_infoWindowUpdate = true;
			MyCharacter.inventory.UseItem(input);	// 9�� ������ ���
			break;
		case 'w':
		case 'W':
			MyCharacter.pos.Move(0, -1, dungeonStage, using_infoWindowType);
			break;
		case 'a':
		case 'A':
			MyCharacter.pos.Move(-1, 0, dungeonStage, using_infoWindowType);
			break;
		case 's':
		case 'S':
			MyCharacter.pos.Move(0, 1, dungeonStage, using_infoWindowType);
			break;
		case 'd':
		case 'D':
			MyCharacter.pos.Move(1, 0, dungeonStage, using_infoWindowType);
			break;

		case 'p':
		case 'P':
			return INTIAL_GAME_STATE;	// ����ȭ������ ����

		case 'i':
		case 'I':
		case 'U':
		case 'u':
			using_infoWindowType = input;
			Character_Info_Window(using_infoWindowType, dungeonStage);
			break;

		default:
			Set_Color %= MAX_CONSOLE_COLOR_NUM;
			gotoxy(85, 20); setcolor(Set_Color++, WHITE);	// ��� ��ġ����, ������

			if (input >= MAX_ASCII_NUM)	// �ƽ�Ű�� �Ѵ� �ѱ��� ǥ��			
				cout << "<�ѱ�>�� �Է��Ͽ����ϴ�. ��/���� �����ּ���    " << endl;
			else
				cout << "< " << input << " >�� �Է��Ͽ����ϴ�. �ٽ� �����ּ���   " << endl;

			setcolor(WHITE, BLACK);
		}

		if (MyCharacter.GetCurrentHP() <= 0)	// ĳ���� ��Ȱ�� ó��
		{
			MyCharacter.Dead();
			FLAG_infoWindowUpdate = true;
		}
	}
}
void Game::Playing_Game_Frame()		// ��ü Ʋ
{
	system("mode con cols=140 lines=70"); // ���߿� ��������â�� ũ�Ⱑ ��������� �ּ��� Ǯ� �� ��.
	system("cls");
	
	// ��ü Ʋ
	setcolor(DARKGRAY, DARKGRAY);
	cout << "�����������������������������������������������������������������������\n";
	for (int i = 0; i < 67; i++)
	{
		cout << "��";
		setcolor(WHITE, BLACK);
		cout << "                                                                                                                                        ";
		setcolor(DARKGRAY, DARKGRAY);
		cout << "��\n";
	}
	cout << "�����������������������������������������������������������������������\n";

	// �߾� ����
	gotoxy(0, 28); cout << "�����������������������������������������������������������������������";
	// �߾� ����
	for (int i = 0; i < 28; i++)
	{
		gotoxy(69, i); cout << "��";
	}
	setcolor(WHITE, BLACK);
}


//=====================================================
// �� - �� ��� ���� �Լ�
//=====================================================
void Game::Make_Map_Dungeon(int dungeonStage)
{
	char map1[27][68] = {
		{"1111111111111111111111111111111111111111111111111111111111111111111"},
		{"10000000#0000000110000000000000000000000000011111000000000000000001"},
		{"1000000000000000110000000000000000000000000011111000000000000000001"},
		{"100c110000011000110000000000000000000000000011111000000000111111111"},	// c = character
		{"1000110000011000110000000000000000000000000011111000000000111111111"},
		{"1000110000011000000000000000000000000000000011111000000000000000001"},
		{"1000110000011000000000000000000000000000000011111000000000000000001"},	// 1 = wall
		{"1000110000011000110000000000001111100000000011111000000000000000001"},
		{"1000110000011000110000000000001111100000000011111000000000011110001"},
		{"1000110000011000110000000000001111100000000000000000000000011110001"},
		{"1000000000011000000000000000001111100000000000000000000000011110001"},
		{"1000000000011000000000000000001111100000000111111000000000011110001"},
		{"1000111111111000111111111100001111100000000110011000000000000000001"},
		{"1000110000000000000000001100000000000000000110011000000000000000001"},
		{"1000110000000000000000001100000000000000000000000000000000000000001"},
		{"1000110000000000011111111111111111111000000000000000000000000000001"},	
		{"1000110000000000000000001100000000000000000000000000000000000000001"},
		{"1000110001100000000000001100000000000000000000000001111100011111111"},
		{"1000110001100000000000001100000000000000000000000000001100000000dd1"},	// d = destination
		{"1000110001111111100000001100000000000011111111110000001100000000dd1"},
		{"1000110001100000000000001100011000000011111111110000001100000000dd1"},
		{"1000110001100000000000001100011000000011111111110000001100000000001"},
		{"100011000110000011111111110001100000001111111111000000000#000000001"},	// # = store
		{"1000110001100000000000000000011000000000000000000000000000000000001"},
		{"1000000001100000000000000000011000000000000000000000000000000000001"},
		{"1000000001100000000000000000011000000000000000000000000000000000001"},
		{"1111111111111111111111111111111111111111111111111111111111111111111"}
	};
	char map2[27][68] = {
		{"1111111111111111111111111111111111111111111111111111111111111111111"},
		{"1000000000000000000000011100000000000000000000000000000111100000001"},
		{"100000000000000000000001110000000s000000000000000000000111100000001"},
		{"100c011000000111000000011100000000000000000000000000000111100000dd1"},	// c = character
		{"1000011000000111000000011100000000000000000000000000000111100000dd1"},
		{"1000011000000111000000011100000000000000000000000000000111100000dd1"},
		{"1000011000000111000000011100000111000000111111111110000111100000001"},
		{"1000011000000111000000000000000111000000111111111110000111100000001"},
		{"1000011000000111000000000000000111000000000000000000000111100000001"},
		{"1000011000000111000000000000000111000000000000000000000111100000001"},
		{"1000000000000111000000000000000000000000000000000000000111100000001"},
		{"1000000000000111000000000000000000000000000000000000000111100000001"},
		{"1000011111000111001111111000001111100000000000000000000111100000001"},
		{"1000011000000000000000000000000000000000000001111111111111100000001"},
		{"1000011000000000000000000000000000000000000001111111111111100000001"},
		{"1000011000000000000111000000000000000000000000000000000111100000001"},
		{"1000011000000000000111000000000000000000000000000000000111100000001"},
		{"1000011000000000111111110000000001111000000000000000000111100000001"},
		{"1000011000011111111111111100000001111000000000000011111110000000001"},
		{"1000011000011111111111111100000001111000000000000011111110000000001"},
		{"1000011000000000000111000000000001111000000000000000011110000000001"},
		{"1000011000000000000111000000000001111000000111000000000000000000001"},
		{"1000011000000000s00000000000000001111000000111000000000000000000001"},	// s = store
		{"1000011000000000000000000000000001111000000000000000000000000000001"},
		{"1000000000000000000000000000000001111000000000000000000000000000001"},
		{"1000000000000000000000000000000001111000000000000000000000000000001"},
		{"1111111111111111111111111111111111111111111111111111111111111111111"}
	};
	char map3[27][68] = {
		{"1111111111111111111111111111111111111111111111111111111111111111111"},
		{"1000000000000111100000000000000000001111000000000000000000000000001"},
		{"100000000000011110000000000000000000111100000000000000000000c000001"},
		{"1000011000000111100000000000s00000001111000000000000000000000000dd1"},	// c = character
		{"1000011000000111100000000000000000001111000000111000000000000000dd1"},
		{"1000011000000111100000000000000000001111000000111000000000000000dd1"},
		{"1000011000000000000000000000000000001111000000111000000111110000001"},
		{"1000011000000000000000000111000000000000000000111000000111110000001"},
		{"1000011000000011100000000111000000000000000000111000000111110000001"},
		{"1000011000000011100000000000000000000000000000111000000000000000001"},
		{"1000000000000000000000000000000000000000000000111000000000000000001"},
		{"1000000000000000000000000000000000000000000000111000000000000000001"},
		{"1000011111000111001111111000001111100000000100111111100001111111111"},
		{"1000011000000000000000000000000000000001111111111111000001111111111"},
		{"1000011000000000000000000000000000000001110011111000000000000000001"},
		{"1000011000000000000000000000000000000001100001110000000000001000001"},
		{"1000011000001111110000000000000000000111000000111000000000000000001"},
		{"1000011000001111110000000011000000000000000000111000000000000000001"},
		{"1000011000000000000000011111000000000000000000111000000000000000001"},
		{"1000011000000000000000111011000000000000000000111000000000000000001"},
		{"1dd0011000000000000001100011000000000000001000111000001111100000001"},
		{"1dd0011000000000000110000011000000000000011000000000001111100000001"},
		{"1dd0011000000000s01100000011000000000000110000000000000110000000001"},	// s = store
		{"1000011000000000000000000011000000000001100000000000000000000000001"},
		{"1000000000000000000000000011000000000001000000000000000000000000001"},
		{"1000000000000000000000000011000000000000000000000000000000000000001"},
		{"1111111111111111111111111111111111111111111111111111111111111111111"}
	};

	switch (dungeonStage)
	{
	case 1:
		memcpy(TempMap, map1, sizeof(TempMap));
		break;
	case 2:
		memcpy(TempMap, map2, sizeof(TempMap));
		break;
	case 3:
		memcpy(TempMap, map3, sizeof(TempMap));
		break;
	}
	
	CreateMonster(TempMap, MAX_STAGE1_MONSTER_NUM);

	// �� ������ (2�����迭�� ������ ����� ���)
	gotoxy(2, 1);		// Playing_Game_Frame�� ���� x = 2, y = 1�� ����
	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < 68; j++)
		{
			char object = TempMap[i][j];

			if (object == '0')
			{
				setcolor(WHITE, BLACK);
				cout << ' ';
			}
			else if (object == '1')			// ��
			{
				setcolor(WHITE, WHITE);
				cout << '1';
			}
			else if (object == 'c')			// �� ĳ����
			{
				setcolor(YELLOW, BLACK);
				MyCharacter.pos.x = j + 2;	// ĳ���� ��ǥ�� ����
				MyCharacter.pos.y = i + 1;	// ĳ���� ��ǥ�� ����
				cout << '@';
				TempMap[i][j] = '0';		// ĳ���� ������ġ�� '0'������ ����(���߿� �̵��Ҽ� �ֵ���)
			}
			else if (object == 'm')			// ����
			{
				setcolor(BLACK, BLACK);		// ���� �ʿ� �Ⱥ��̰� �ϱ� (�������� �����Ϸ�� ����� ��)
				cout << 'm';
			}
			else if (object == '#')			// store
			{
				setcolor(LIGHTGREEN, BLACK);
				cout << '#';
			}
			else if (object == 'd')			// Destination
			{
				setcolor(LIGHTPURPLE, LIGHTPURPLE);
				cout << 'd';
			}
		}
		gotoxy(2, 1 + 1 + i); // Playing_Game_Frame�� ���� x = 2, y = 1�� ������ ��, y+1���� ���
	}
}
void Game::CreateMonster(char(&map)[27][68], int maxMonsterNum)
{
	int stage_monster_num = 0;

	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < 68; j++)
		{
			if (stage_monster_num > maxMonsterNum) return;

			if (map[i][j] == '0')
			{
				if (Percent(4))
				{
					map[i][j] = 'm';
					stage_monster_num++;
				}
			}
		}
	}

}

#pragma region Make_Map_Dungeon
/*
void Game::Make_Map_Dungeon1(int dungeonStage)
{

	char map[27][68] = {
		{"1111111111111111111111111111111111111111111111111111111111111111111"},
		{"10000000s0000000110000000000000000000000000011111000000000000000001"},
		{"1000000000000000110000000000000000000000000011111000000000000000001"},
		{"100c110000011000110000000000000000000000000011111000000000111111111"},	// c = character
		{"1000110000011000110000000000000000000000000011111000000000111111111"},
		{"1000110000011000000000000000000000000000000011111000000000000000001"},
		{"1000110000011000000000000000000000000000000011111000000000000000001"},
		{"1000110000011000110000000000001111100000000011111000000000000000001"},
		{"1000110000011000110000000000001111100000000011111000000000011110001"},
		{"1000110000011000110000000000001111100000000000000000000000011110001"},
		{"1000000000011000000000000000001111100000000000000000000000011110001"},
		{"1000000000011000000000000000001111100000000111111000000000011110001"},
		{"1000111111111000111111111100001111100000000110011000000000000000001"},
		{"1000110000000000000000001100000000000000000110011000000000000000001"},
		{"1000110000000000000000001100000000000000000000000000000000000000001"},
		{"1000110000000000011111111111111111111000000000000000000000000000001"},
		{"1000110000000000000000001100000000000000000000000000000000000000001"},
		{"1000110001100000000000001100000000000000000000000001111100011111111"},
		{"1000110001100000000000001100000000000000000000000000001100000000dd1"},
		{"1000110001111111100000001100000000000011111111110000001100000000dd1"},
		{"1000110001100000000000001100011000000011111111110000001100000000dd1"},
		{"1000110001100000000000001100011000000011111111110000001100000000001"},
		{"100011000110000011111111110001100000001111111111000000000s000000001"},	// s = store
		{"1000110001100000000000000000011000000000000000000000000000000000001"},
		{"1000000001100000000000000000011000000000000000000000000000000000001"},
		{"1000000001100000000000000000011000000000000000000000000000000000001"},
		{"1111111111111111111111111111111111111111111111111111111111111111111"}

	};

	CreateMonster(map, MAX_STAGE1_MONSTER_NUM);
	//	int stage_monster_num = 0;

	////������� ���� �����Լ�
	//if (stage_monster_num <= MAX_STAGE2_MONSTER_NUM)
	//{
	//	for (int i = 0; i < 27; i++)
	//	{
	//		for (int j = 0; j < 68; j++)
	//		{
	//			if (map[i][j] == '0')
	//			{
	//				if (Percent(5))
	//				{
	//					map[i][j] = 'm';
	//					stage_monster_num++;
	//				}
	//			}

	//		}
	//	}
	//}
	memcpy(tempMap, map, sizeof(tempMap));

	// �� ������ (2�����迭�� ������ ����� ���)
	gotoxy(2, 1);		// Playing_Game_Frame�� ���� x = 2, y = 1�� ����
	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < 68; j++)
		{
			char temp = tempMap[i][j];

			if (temp == '0')
				cout << " ";
			else if (temp == '1')			// ����ġ
			{
				setcolor(WHITE, WHITE);
				cout << "#";
				setcolor(WHITE, BLACK);
			}
			else if (temp == 'c')			// �� ĳ���� ��ġ
			{
				setcolor(YELLOW, BLACK);
				My_Character.pos.x = j + 2;// ĳ���� ��ǥ�� ����
				My_Character.pos.y = i + 1;// ĳ���� ��ǥ�� ����
				cout << "@";
				tempMap[i][j] = '0';	// ĳ���� ������ġ�� '0'������ ����(���߿� �̵��Ҽ� �ֵ���)
				setcolor(WHITE, BLACK);
			}
			else if (temp == 'm')			// ����
			{
				//setcolor(LIGHTGREEN, LIGHTGREEN);	// ���� �׽�Ʈ������ �����
				setcolor(BLACK, BLACK); // ���� �ʿ� �Ⱥ��̰� �ϱ� (�������� �����Ϸ�� ����� ��)
				cout << "m";
				setcolor(WHITE, BLACK);
			}
			else if (temp == 's')			// store ��ġ
			{
				setcolor(LIGHTGREEN, BLACK);
				cout << "#";
				setcolor(WHITE, BLACK);
			}
			else if (temp == 'd')			// Destination ��ġ
			{
				setcolor(LIGHTPURPLE, LIGHTPURPLE);
				cout << "*";
				setcolor(WHITE, BLACK);
			}
		}
		gotoxy(2, 1 + 1 + i); // Playing_Game_Frame�� ���� x = 2, y = 1�� ������ ��, y+1���� ���
	}


	// �� ���� ǥ�� ������ ���� !! ����� ���� �������..
	//gotoxy(2, 1);
	//for (int i = 0; i < 27; i++)
	//{
	//	for (int j = 0; j < 68; j++)
	//	{
	//		char temp = tempMap[i][j];
	//		cout << temp;
	//
	//	}
	//	gotoxy(2, 1 + 1 + i); // Playing_Game_Frame�� ���� x = 2, y = 1�� ������ ��, y+1���� ���
	//}

}*/
#pragma endregion

//=====================================================
// �� - ĳ���� ����â(����, �κ��丮) ��� ���� �Լ�
//=====================================================
void Game::Character_Info_Window(int state, int dungeonStage)
{
	char state_window = state;
	switch (state_window)
	{
	case 'u':
	case 'U':
		Character_Status(dungeonStage);
		break;

	case 'i':
	case 'I':
		Character_Inventory();
		break;
	}
}
void Game::Character_Status(int dungeonStage)		// ĳ���� ����â(ĳ���� ����â,  �κ��丮â)
{
	Remove_Character_Info_Window();
	gotoxy(98, 2);  cout << "< ĳ���� ���� >";
	gotoxy(118, 2); cout << " [p] - ��������";
	gotoxy(118, 3); cout << " [U] - ĳ���� ����";
	gotoxy(118, 4); cout << " [I] - �κ��丮";

	setcolor(RED, LIGHTCYAN);
	gotoxy(71, 1); cout << "���� ��� : " << MyCharacter.GetGold() <<"G";
	setcolor(WHITE, BLACK);

	gotoxy(80, 6);  cout << "�г��� : " << MyCharacter.GetName();
	gotoxy(100,6);  cout << "  ���� : " << Class_ItoS(MyCharacter.GetClass());
	gotoxy(80, 8);  cout << "    LV : " << MyCharacter.GetLV();
	gotoxy(80, 9);  cout << "    HP : " << MyCharacter.GetCurrentHP() << "/" << MyCharacter.GetMaxHP();
	gotoxy(80, 10); cout << "    MP : " << MyCharacter.GetCurrentMP() << "/" << MyCharacter.GetMaxMP();
	gotoxy(80, 11); cout << "���ݷ� : " << MyCharacter.GetAtt() + MyCharacter.GetAddAtt() << "(" << MyCharacter.GetAtt() << "+" << MyCharacter.GetAddAtt() << ")";
	gotoxy(80, 12); cout << "���� : " << MyCharacter.GetDef();
	gotoxy(80, 13); cout << "����ġ : " << MyCharacter.GetCurrentExp() << "/" << MyCharacter.GetMaxExp();
	gotoxy(78, 14); cout << "������ġ : ���� " << dungeonStage << "��";

}
void Game::Character_Inventory()
{
	Remove_Character_Info_Window();
	gotoxy(97, 2); cout << "< �κ��丮 ���� >";
	gotoxy(118, 2); cout << " [p] - ��������";
	gotoxy(118, 3); cout << " [U] - ĳ���� ����";
	gotoxy(118, 4); cout << " [I] - �κ��丮";
	gotoxy(117, 5); cout << "[1~9] - �����ۻ��";
	

	setcolor(RED, LIGHTCYAN);
	gotoxy(71, 1); cout << "���� ��� : " << MyCharacter.GetGold() <<"G";
	setcolor(WHITE, BLACK);
	//gotoxy(71, 6); cout << "����������������������������������";
	MyCharacter.inventory.ShowInventory();
	//gotoxy(71, 16); cout << "����������������������������������";
	
}
void Game::Remove_Character_Info_Window()	// ĳ���� ����â ����� �Լ�
{
	for (int row = 1; row < 28; row++)
	{
		gotoxy(71, row); cout << "                                                                  ";
	}                                                                                                   
}


//=====================================================
// �� - �������� ���â (����, ���� ����)
//=====================================================
inline void Game::Remove_GameProcess_Window()		// ����ȭ��, ��Ʋȭ�� �����
{
	for (int row = 29; row <= 67; row++)	// ��������â ��ü �����
	{
		gotoxy(2, row); cout << "                                                                                                                                        ";
	}

	//for (int row = 29; row <= 67; row++)	// ��������â ���� �ݸ� ����� (�α׳���)
	//{
	//	gotoxy(2, row); cout << "                                                                      ";
	//}
}
void Game::Remove_Inventory_In_Store()
{
	for (int row = 38; row <= 64; row++)
	{
		gotoxy(72, row); cout << "                                                                  ";
	}
}
inline void Game::Remove_Inventory_In_Battle()
{
	for (int row = 35; row <= 67; row++)
	{
		gotoxy(2, row); cout << "                                                     ";
	}
}
inline void Game::Remove_BattleLog()
{
	for (int row = 29; row <= 67; row++)
	{
		gotoxy(72, row); cout << "                                                           ";
	}
}
void Game::Remove_At_Battle_End() 
{
	char input = 0;
	setcolor(BLACK, WHITE);
	gotoxy(72, 67); cout << "�ƹ�Ű�� ��������....";
	setcolor(WHITE, BLACK);
	input = _getch();
	for (int row = 29; row <= 67; row++)	// ��������â ��ü �����
	{
		gotoxy(2, row); cout << "                                                                                                                                        ";
	}
}

// ���� ����
void Game::Store_Process(int dungeonStage,int& infoWindowType)
{
	Remove_GameProcess_Window();
	Store_Screen(dungeonStage);
	
	char Set_Color = BLACK;
	unsigned char input= 0;
	char storeMode = BUY_MODE;

	setcolor(BLUE, LIGHTGREEN);
	gotoxy(60, 35);  cout << "======BUY  MODE======";
	setcolor(WHITE, BLACK);

	FLAG_using_store = true;
	while (FLAG_using_store)
	{
		if (FLAG_infoWindowUpdate)		// ĳ�� ����â ������Ʈ
		{
			FLAG_infoWindowUpdate = false;
			Character_Info_Window(infoWindowType, dungeonStage);	// ����â ����
			MyCharacter.inventory.ShowInventory_In_Store();	// ������ �κ��丮 ����
		}

		switch (input = _getch())
		{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if (storeMode == BUY_MODE)
				Store_BuyMode(dungeonStage, input);
			else if (storeMode == SELL_MODE)
				Store_SellMode(input);
			break;

		case 'u':
		case 'U':
		case 'i':
		case 'I':
			infoWindowType = input;
			Character_Info_Window(infoWindowType, dungeonStage);	// U, I �������� �ٲٵ���
			break;

		case 'r':
		case 'R':
			if (storeMode == BUY_MODE)
			{
				setcolor(RED, LIGHTGREEN);   
				gotoxy(60, 35);  cout << "======SELL MODE======";
				setcolor(WHITE, BLACK);
				storeMode = SELL_MODE;
			}
			else
			{
				setcolor(BLUE, LIGHTGREEN);
				gotoxy(60, 35);  cout << "======BUY  MODE======";
				setcolor(WHITE, BLACK);
				storeMode = BUY_MODE;
			}
			break;

		case 'w':
		case 'W':
		case 'a':
		case 'A':
		case 's':
		case 'S':
		case 'd':
		case 'D':
		case 'p':
		case 'P':
			FLAG_using_store = false;
			Remove_GameProcess_Window();
			break;

		case SPACE_BAR : // �׽�Ʈ��
			MyCharacter.SetGold(500000);
			break;

		default:
			Set_Color %= MAX_CONSOLE_COLOR_NUM;
			setcolor(BLACK, Set_Color);	// ��� ��ġ����, ������
			gotoxy(48, 65); cout << "���� ���� �̿����Դϴ�. ���� �Ŀ� �õ����ּ���";
			setcolor(WHITE, BLACK);
			Set_Color++;	
		}
		FLAG_infoWindowUpdate = true; // �������� � ��ȣ�ۿ��� �ϴ��� ����â�� �����ǵ���,
	}
	// gotoxy(2,67); cout << "���������������������������������������������������������������������";
}
void Game::Store_Screen(int dungeonStage)
{
	//gotoxy(2,29); cout << "
	gotoxy(48, 31);  cout << "=============================================";
	gotoxy(47, 32);  cout << "��               ���� " << dungeonStage << "�� ����              ��";
	gotoxy(48, 33);  cout << "=============================================";


	gotoxy(115, 30); cout << "   [P]- ���� ������";
	gotoxy(113, 31); cout << "[����Ű]- ���� ������";
	gotoxy(114, 32); cout << "    [R]-�Ǹű��Ÿ��";
	gotoxy(115, 33); cout << " [1~9]- ������ ����";
	gotoxy(115, 34); cout << " [1~9]- ������ �Ǹ�";

	for (int i = 37; i <= 57; i++)
	{
		gotoxy(69, i); cout << "��";
	}

	switch (dungeonStage)
	{
	case 1:
		gotoxy(25, 36);  cout << "<< ��� ������ >>";
		gotoxy(20, 38);  cout << "1. �ʽ����� ���\t200Gold";
		gotoxy(20, 39);  cout << "   �ʽ����� ��� - ���ݷ� +10";
		gotoxy(20, 41);  cout << "2. �ʽ����� ��â\t500Gold";
		gotoxy(20, 42);  cout << "   �ʽ����� ��â - ���ݷ� +20";


		gotoxy(25, 46); cout << "<< �Һ� ������ >>";
		gotoxy(20, 48); cout << "3. ��������\t30Gold";
		gotoxy(20, 49); cout << "   �������� - HP��(��) 30ȸ���մϴ�";
		gotoxy(20, 51); cout << "4. �Ķ�����\t50Gold";
		gotoxy(20, 52); cout << "   �Ķ����� - MP��(��) 30ȸ���մϴ�";

		gotoxy(95, 36); cout << "<< �κ��丮 >>";
		MyCharacter.inventory.ShowInventory_In_Store();
		break;

	case 2:
		gotoxy(25, 36);  cout << "<< ��� ������ >>";
		gotoxy(20, 38);  cout << "1. �߱����� ���\t1200Gold";
		gotoxy(20, 39);  cout << "   �߱����� ��� - ���ݷ� +40";
		gotoxy(20, 41);  cout << "2. �߱����� ��â\t2000Gold";
		gotoxy(20, 42);  cout << "   �߱����� ��â - ���ݷ� +55";


		gotoxy(25, 46); cout << "<< �Һ� ������ >>";
		gotoxy(20, 48); cout << "3. ��Ȳ����\t50Gold";
		gotoxy(20, 49); cout << "   ��Ȳ���� - HP��(��) 70ȸ���մϴ�";
		gotoxy(20, 51); cout << "4. ��������\t70Gold";
		gotoxy(20, 52); cout << "   �������� - MP��(��) 80ȸ���մϴ�";

		gotoxy(95, 36); cout << "<< �κ��丮 >>";
		MyCharacter.inventory.ShowInventory_In_Store();
		break;
	}
}
void Game::Store_BuyMode(int dungeonStage,int input)	// �������� ���Ÿ���϶�
{
	switch (dungeonStage)
	{
	case 1:	// ���� 1��
		switch (input)
		{
		case '1':
			MyCharacter.inventory.BuyItem(new Equipment("�ʽ����� ���", 200, 10));
			break;
		case '2':
			MyCharacter.inventory.BuyItem(new Equipment("�ʽ����� ��â", 500, 20));
			break;
		case '3':
			MyCharacter.inventory.BuyItem(new Potion("��������", 30, 0, 30, 1));
			break;
		case '4':
			MyCharacter.inventory.BuyItem(new Potion("�Ķ�����", 0, 30, 50, 1));
			break;
		case '5':
			break;
		case '6':
			break;
		case '7':
			break;
		case '8':
			break;
		case '9':
			break;
		}
		break;
	case 2:	// ���� 2��
		switch (input)
		{
		case '1':
			MyCharacter.inventory.BuyItem(new Equipment("�߱����� ���", 1200, 40));
			break;
		case '2':
			MyCharacter.inventory.BuyItem(new Equipment("�߱����� ��â", 2000, 55));
			break;
		case '3':
			MyCharacter.inventory.BuyItem(new Potion("��Ȳ����", 70, 0, 50, 1));
			break;
		case '4':
			MyCharacter.inventory.BuyItem(new Potion("��������", 0, 80, 70, 1));
			break;
		case '5':
			break;
		case '6':
			break;
		case '7':
			break;
		case '8':
			break;
		case '9':
			break;
		}
		break;
	case 3:	// ���� 3��
		switch (input)
		{
		case '1':
			break;
		case '2':
			break;
		case '3':
			break;
		case '4':
			break;
		case '5':
			break;
		case '6':
			break;
		case '7':
			break;
		case '8':
			break;
		case '9':
			break;
		}
		break;
	}
}
void Game::Store_SellMode(int input)	// �������� �ǸŸ���϶�
{
	int index = input - 48 - 1;	// �ƽ�Ű -48, �ε��� -1
	//setcolor(BLACK, WHITE);	// ���� ����׿� // �׽�Ʈ
	//gotoxy(48, 59); cout << "�Է¼��� : " << (char)input;
	//setcolor(WHITE, BLACK);

	MyCharacter.inventory.Sell_Items(index);
}

// ���� ��������
void Game::Battle_Process(int dungeonStage, int &infoWindowType)
{
	Monster monster("noname", 0, 0, 0, 0, 0);

	Monster_Decision(dungeonStage ,monster);		// ���� ���� ����
	Battle_Screen(&monster);

	unsigned int input = 0;
	bool monster_attack_turn = false;				// true - ������ ������ ���� ��

	FLAG_Monster_Observation = false;
	FLAG_playing_battle = true;
	FLAG_infoWindowUpdate = true;
	Battle_log_row = MIN_BATTLE_LOG_ROW;			// ���� ���۽� �α� ������ 27������ ������� 

	thread t1(Game::Thread_InBattle, ref(m));
	int testnum = 0;
	while (FLAG_playing_battle)
	{
		m.lock();
		
		if (monster_attack_turn)	// ���� �������̸� �����ϰ� ��������
		{
			monster_attack_turn = false;
			monster.Attack(&MyCharacter, dungeonStage);
		}
		
		if (FLAG_infoWindowUpdate)	// ĳ�� ����â ����(������ �ǽð��ݿ�)
		{
			FLAG_infoWindowUpdate = false;
			Remove_Inventory_In_Battle();

			Character_Info_Window(infoWindowType, dungeonStage);
			monster.ShowMonsterInfo();
			//gotoxy(50, 30); cout << "ĳ����������, " << testnum++;
		}

		if (MyCharacter.GetCurrentHP() <= 0)
		{
			FLAG_playing_battle = false;
			Game::Remove_At_Battle_End();	// ������ ȭ������� ����
			Game::Make_Map_Dungeon(dungeonStage);	// �ؼ������ǡ� �׾����� ���� ������
			m.unlock();
			break;
		}
		Control_BattleLog();		// ��Ʋ�α� �� ����
		m.unlock();

		input = Avoid_Garbage_getch();
		m.lock();
		FLAG_infoWindowUpdate = true;
		switch (input)
		{
		case '1':					// �⺻����
			monster_attack_turn = true;
			MyCharacter.Attack(&monster);
			break;

		case '2':					// ��ų (�̱���)
			monster_attack_turn = true;
			MyCharacter.Attack(&monster);
			break;

		case '3':					// ������ ���
			if (Battle_UseItem())		// 0 ������ �ൿ�� ������ ����(�ϼҸ�X)
				monster_attack_turn = true;
			break;

		case '4':					// �����ϱ�
			monster_attack_turn = true;
			Battle_ObservMonster();
			break;

		case '5':					// �������� 
			monster_attack_turn = true;
			Battle_RunAway();	
			break;

		case 'i':
		case 'I':
		case 'U':
		case 'u':
			infoWindowType = input;
			Character_Info_Window(infoWindowType, dungeonStage);
			break;

		//case SPACE_BAR:
		//	FLAG_playing_battle = false;
		//	//Remove_Inventory_In_Battle();
		//	Remove_GameProcess_Window();
		//	break;
		}
		m.unlock();
	}
	Battle_log_row = MIN_BATTLE_LOG_ROW;
	Remove_GameProcess_Window();
	t1.detach();
}
void Game::Monster_Decision(int dungeonStage, Monster& monster)
{
	// void Monster::SetMonster(string name, int level, int maxhp, int att, int exp, int gold)

	int randomMonster = rand() % 100;	// Ȯ������
	switch (dungeonStage)
	{
	case 1:		// ���� 1��		// �̸�, ����, ü��, ���ݷ�, ����ġ, ��
		if (randomMonster < 30)
			monster.SetMonster("������", 1, 35, 5, 5, 20);
		else if (randomMonster < 60)
			monster.SetMonster("���� ������", 1, 60, 12, 10, 40);
		else if (randomMonster < 90)
			monster.SetMonster("�Ͼ� ������", 1, 70, 8, 10, 40);
		else
			monster.SetMonster("ŷ ������", 2, 150, 9, 20, 100);
		break;
	case 2:		// ���� 2��		// �̸�, ����, ü��, ���ݷ�, ����ġ, ��
		if (randomMonster < 30)
			monster.SetMonster("��Ű", 2, 70, 10, 15, 20);
		else if (randomMonster < 60)
			monster.SetMonster("���� ��Ű", 2, 130, 40, 40, 80);
		else if (randomMonster < 90)
			monster.SetMonster("�Ͼ� ��Ű", 2, 180, 25, 40, 80);
		else
			monster.SetMonster("��� ��Ű", 4, 320, 25, 300, 300);
		break;
	case 3:		// ���� 3��		// �̸�, ����, ü��, ���ݷ�, ����ġ, ��
		if (randomMonster < 25)
			monster.SetMonster("ī��", 3, 150, 35, 60, 100);
		else if (randomMonster < 50)
			monster.SetMonster("�Ͼ� ī��", 3, 230, 40, 80, 180);
		else if (randomMonster < 70)
			monster.SetMonster("���� ī��", 4, 200, 45, 80, 180);
		else if (randomMonster < 85)
			monster.SetMonster("������ ī��", 5, 180, 150, 100, 200);
		else
			monster.SetMonster("���� ī��", 5, 400, 45, 300, 400);
		break;
	case 4:		// ���� 4��
		break;
	case 5:		// ���� 5��
		break;
	case 6:		// ���� 6��
		break;
	case 7:		// ���� 7��
		break;
	case 8:		// ���� 8��
		break;
	case 9:		// ���� 9��
		break;
	case 10:	// ���� 10��
		break;
	}

}
void Game::Battle_Screen(Monster* monster)
{
	Remove_GameProcess_Window();	

	//for (int i = BLACK; i < MAX_CONSOLE_COLOR_NUM; i++)
	//{
	//	setcolor(i, BLACK);

	//	if (i % 2 == 0) {
	//		gotoxy(30, 29);  cout << "�ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ�";
	//		gotoxy(30, 31);  cout << "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�";
	//	}
	//	else {
	//		gotoxy(30, 29);  cout << "�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�";
	//		gotoxy(30, 31);  cout << "�ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ�";
	//	}
	//	gotoxy(30, 30); setcolor(RED, BLACK);  cout << "      "; cout << monster->GetName() << " �߰�       ";
	//	
	//	Sleep(20);
	//}
	setcolor(WHITE, BLACK);
	gotoxy(2, 67); setcolor(BLACK, WHITE); cout << "���Ϳ� ������ ��� �ൿ�� ���� �Ҹ��մϴ�.";

	setcolor(CYAN, BLACK);
	int row1 = 29, row2 = 29;
	//gotoxy(2,29);	cout << "�ൿ�� �����ϼ���";
	gotoxy(2, row1++);	cout << "[1] �⺻����         ";	gotoxy(23, row2++); cout << "|";
	gotoxy(2, row1++);	cout << "[2] ��ų             ";	gotoxy(23, row2++); cout << "|";
	gotoxy(2, row1++);	cout << "[3] ������           ";	gotoxy(23, row2++); cout << "|";
	gotoxy(2, row1++);	cout << "[4] �����ϱ�         ";	gotoxy(23, row2++); cout << "|";
	gotoxy(2, row1++);	cout << "[5] �������� (70%)   ";	gotoxy(23, row2++); cout << "|";
	gotoxy(2, row1++);	cout << "---------------------";gotoxy(23, row2++); cout << "|";
	setcolor(WHITE, BLACK);
}
void Game::Thread_InBattle(mutex& m)
{
	int row = 29;
	int column = 28;
	while (FLAG_playing_battle)
	{
		m.lock();
		setcolor(YELLOW, BLACK);
		gotoxy(28, 29); cout << "                      "; //48
		gotoxy(column, row); cout << "=";

		if (FLAG_Monster_Observation)
		{
			gotoxy(28, 29 + 7); cout << "                      ";
			gotoxy(column, row + 7); cout << "=";
		}
		else
		{
			gotoxy(28, 29 + 5); cout << "                      ";
			gotoxy(77 - column, row + 5); cout << "="; // 75 -28 45 51
		}
		setcolor(WHITE, BLACK);
		m.unlock();

		Sleep(150);
		if (column < 48) column++;
		else column = 28;
	}

}

void Game::Battle_RunAway()
{
	if (Percent(70))
	{
		FLAG_playing_battle = false;
		//Remove_At_Battle_End();
		//Remove_GameProcess_Window();
		setcolor(BLACK, WHITE);	
		gotoxy(63, 30); cout << " �������� ���� ";
		setcolor(WHITE, BLACK);
	}
	else
	{
		setcolor(BLACK, WHITE);	
		gotoxy(63, 30); cout << " �������� ���� ";
		setcolor(WHITE, BLACK);
	}
}
void Game::Battle_ObservMonster()
{
	FLAG_Monster_Observation = true;	// true - �����ϱ�� ���� ���� �߰����� ����
	 
	gotoxy(72, Battle_log_row += 2); cout << "�� ";
	setcolor(GREEN, BLACK);	cout << MyCharacter.GetName();
	setcolor(WHITE, BLACK); cout << "��(��) ";
	setcolor(LIGHTCYAN, BLACK); cout << "�����ϱ�";
	setcolor(WHITE, BLACK);	 cout << "�� �߽��ϴ�.";
}
bool Game::Battle_UseItem()
{
	Remove_Inventory_In_Battle();	// �κ��丮�� ����Ʈ ������ڵ�
	MyCharacter.inventory.ShowInventory_In_Battle(); // ����Ʈ ��ġ����
	
	unsigned char input = 0;
	input = Avoid_Garbage_getch();
	if ('1' <= input && input <= '9')
	{
		if (MyCharacter.inventory.UseItem(input))
			return true;	// ������ ��뼺�� 
		else
			return false;	// ������ ������ (���Կ� �������� ����)
	}
	else
		return false;		// ���� ��� ���ߴ�(�ൿ�� ������ ����)
}
void Game::Control_BattleLog()	// ��Ʋ�αװ� ������� ������
{
	if (Battle_log_row >= 67)
	{	
		Battle_log_row = MIN_BATTLE_LOG_ROW;
		Remove_BattleLog();
	}
	// gotoxy(72, Battle_log_row +=2); cout << �á�
}

