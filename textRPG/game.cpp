#include "main.h"



extern mutex m;
extern char TempMap[27][68];
extern Character MyCharacter;
int Battle_log_row = MIN_BATTLE_LOG_ROW;

bool FLAG_mapUpdate = false;		// true - 맵을 업데이트 해라
bool FLAG_infoWindowUpdate = false; // true - 캐릭터 정보창 업데이트 해라
bool FLAG_using_store = false;		// true - 현재 상점을 이용중이다
bool FLAG_playing_battle = false;	// true - 현재 몬스터와 전투중이다
bool FLAG_Monster_Observation = false; // true - 관찰하기를 이용한 몬스터 추가정보를 보는 중이다.


//Game::Game()
//{
//	//cout << "게임을 실행합니다" << endl;
//}
string Game::Class_ItoS(char chractor_class)			// int값을 받고 string으로 반환
{
	if (chractor_class == ONE)
		return "전사";
	else if (chractor_class == TWO)
		return "궁수";
	else if (chractor_class == THREE)
		return "마법사";
	else
		return "쓰레기값 나올리가 없음!";	// << 나올수없게 짜놓음

}
//=====================================================
// 게임 전 - 게임 화면에 관련된 함수들
//=====================================================
int Game::Initial_Game_State()					
{
	int game_state = INIT_GAME;
	while (1) {
		switch (game_state)
		{
		case INIT_GAME:
			game_state = Init_Screen();		// 시작 화면
			break;

		case NEW_GAME_START:				// 캐릭터 생성화면으로
			game_state = Character_Create_Screen();
			break;

		case CONTINUE_GAME_START:			
			//break;

		case GAME_INFO:
			game_state = GameInfo_Screen();
			break;

		case GAME_PLAYING_STATE:			// 게임 진행State으로 넘어감
			game_state = Playing_Game_State();
			break;

		case GAME_EXIT:						// 게임 종료
			return GAME_EXIT;	
		}
	}
}
int Game::Init_Screen()									// 게임 초기 시작시, state에 의한 화면 출력 및 기능
{
	system("mode con cols=70 lines=30"); // 나중에 게임진행창의 크기가 변경됐을때 주석을 풀어서 쓸 것.
	system("cls");
	setcolor(WHITE, BLACK);
	cout << "\n";
	cout << "    ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■           ---------------------------------            ■\n";
	cout << "    ■          |            영웅키우기           |           ■\n";
	cout << "    ■          |             -던전편-            |           ■\n";
	cout << "    ■           ---------------------------------            ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                     1. 새 게임시작                     ■\n";
	cout << "    ■                     2. 불러오기(미구현)                ■\n";
	cout << "    ■                     3. 게임설명                        ■\n";
	cout << "    ■                     4. 게임종료                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n";

	gotoxy(21, 14);
	cout << " 선택할 숫자를 눌러주세요.";

	int Set_Color = BLACK;
	unsigned char input =0;

	while (1) {
		
		switch (input = Avoid_Garbage_getch())
		{
		case ONE:
			//cout << "새 게임시작" << endl;
			return NEW_GAME_START;

		case TWO:
			//cout << "불러오기" << endl;
			return CONTINUE_GAME_START;

		case THREE:
			//cout << "게임설명" << endl;
			return GAME_INFO;

		case FOUR:
			//cout << "게임종료" << endl;
			return GAME_EXIT;

		default:
			Set_Color %= MAX_CONSOLE_COLOR_NUM;
			gotoxy(15, 20); setcolor(Set_Color, WHITE);	// 출력 위치지정, 색지정
			if (input >= MAX_ASCII_NUM)	// 아스키값 넘는 한글을 표시			
				cout << "<한글>을 입력하였습니다. 다시 눌러주세요" << endl;
			else
				cout << "< " << input << " >을 입력하였습니다. 다시 눌러주세요 " << endl;
			setcolor(WHITE, BLACK);
			Set_Color++;
			break;
		}
		
	}

}
int Game::Character_Create_Screen()						// 캐릭터 생성 화면 (닉네임, 직업 선택)
{
	string name;
	unsigned char character_class = 0;
	Init_Game_Frame();

	gotoxy(23, 3); cout << "=======================";
	gotoxy(23, 4); cout << "      캐릭터 생성";
	gotoxy(23, 5); cout << "=======================";

	gotoxy(18, 7); cout << "사용할 닉네임 입력 :";
	gotoxy(15, 8); cout << "직업 선택[1. 전사, 2. 궁수, 3. 마법사] :";

	do
	{
		gotoxy(40, 7); cin >> name;
		if (name.size() > 20)
		{
			gotoxy(22, 11);cout << "닉네임은 최대 10글자입니다";	// 한글기준 10글자
			gotoxy(40, 7); cout << "                      ■     "; // 닉네임 쓴거 지우기
		}
		else break;
	} while (true);
	
	
	do
	{
		character_class = Avoid_Garbage_getch();
		gotoxy(15, 11);
		if (character_class >= MAX_ASCII_NUM)	// 아스키값 넘는 한글을 표시
		{
			 cout << "<한글>을 입력하였습니다. 영어로 입력하세요";
		}
		else
		{
			 cout << "< " << character_class << " >을 입력하였습니다. 다시 눌러주세요   ";
		}
	} while (character_class < ONE || THREE < character_class);	// 직업 선택 (1~3)


	
	Init_Game_Frame();
	gotoxy(23, 6); cout << "=======================";
	gotoxy(23, 7); cout << "   닉네임 :  " << name;
	gotoxy(23, 8); cout << "   직  업 :  " << Class_ItoS(character_class);
	gotoxy(23, 9); cout << "=======================" << endl;


	gotoxy(26, 13); setcolor(BLACK, WHITE);
	cout << "결정하시겠습니까?";
	gotoxy(24, 14); setcolor(BLACK, WHITE);
	cout << "<1. 네>   <2. 아니요>";
	gotoxy(12, 18); setcolor(BLACK, WHITE);
	cout << "스페이스바를 누르면 시작화면으로 이동합니다.";
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
			//cout << "<" << input <<"> 시작화면으로 이동 " << endl;
			return INIT_GAME;

		default:
			Set_Color %= MAX_CONSOLE_COLOR_NUM;
			gotoxy(15, 20); setcolor(Set_Color++, WHITE);	// 출력 위치지정, 색지정	
			if (input >= MAX_ASCII_NUM)	// 아스키값 넘는 한글을 표시
				cout << "<한글>을 입력하였습니다. 영어로 입력하세요";
			else
				cout << "< " << input << " >을 입력하였습니다. 다시 눌러주세요   ";	
			setcolor(WHITE, BLACK);
			break;
		}
		
	}
}
int Game::GameInfo_Screen()			// 게임설명창
{
	system("cls");
	cout << "\n";
	cout << "    ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                      ※게임목표※                      ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                    던전에서 성장해서                   ■\n";
	cout << "    ■                  10층의 던전을 탈출하자                ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                   방향키 : W A S D                     ■\n";
	cout << "    ■               ※한글입력주의(한/영 누르기)             ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n";

	gotoxy(12, 18); setcolor(BLACK, WHITE);
	cout << "스페이스바를 누르면 시작화면으로 이동합니다.";
	setcolor(WHITE, BLACK);

	int Set_Color = BLACK;
	unsigned char input=0;

	while (1) {
		
		switch (input = Avoid_Garbage_getch())
		{
		case SPACE_BAR:
			//cout << "<" << input <<"> 시작화면으로 이동 " << endl;
			return INIT_GAME;

		default:
			Set_Color %= MAX_CONSOLE_COLOR_NUM;
			gotoxy(15, 20); setcolor(Set_Color, WHITE);	// 출력 위치지정, 색지정
			if (input >= MAX_ASCII_NUM)	// 아스키값 넘는 한글을 표시			
				cout << "<한글>을 입력하였습니다. 다시 눌러주세요" << endl;
			else
				cout << "< " << input << " >을 입력하였습니다. 다시 눌러주세요 " << endl;
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
	cout << "    ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■                                                        ■\n";
	cout << "    ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n";
}


//=====================================================
// 중 - 전체 화면 및 플레이에 관련된 함수들
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

	int Set_Color = BLACK;	 //	BLACK = 0 초기값
	int dungeonStage = 1;	 // 던전 '1'단계 초기값
	int using_infoWindowType = 'U';	// U - 캐릭터상태창, I - 인벤토리창, 초기는 캐릭상태창
	unsigned char input = 0; // 키입력값 '0' 초기값

	// 처음화면 출력
	Playing_Game_Frame();
	Character_Info_Window(using_infoWindowType, dungeonStage);
	Make_Map_Dungeon(dungeonStage);


	// 게임 진행 및 키입력 
	while (1) {
		
		if (FLAG_mapUpdate)			// 다음 던전으로 진행 시, 맵 업데이트 
		{
			FLAG_mapUpdate = false;
			Make_Map_Dungeon(dungeonStage);
		}

		if (FLAG_infoWindowUpdate)	// 캐릭 정보창 업데이트(상점이용, 아이템이용시)
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
			MyCharacter.inventory.UseItem(input);	// 9번 아이템 사용
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
			return INTIAL_GAME_STATE;	// 시작화면으로 가기

		case 'i':
		case 'I':
		case 'U':
		case 'u':
			using_infoWindowType = input;
			Character_Info_Window(using_infoWindowType, dungeonStage);
			break;

		default:
			Set_Color %= MAX_CONSOLE_COLOR_NUM;
			gotoxy(85, 20); setcolor(Set_Color++, WHITE);	// 출력 위치지정, 색지정

			if (input >= MAX_ASCII_NUM)	// 아스키값 넘는 한글을 표시			
				cout << "<한글>을 입력하였습니다. 한/영을 눌러주세요    " << endl;
			else
				cout << "< " << input << " >을 입력하였습니다. 다시 눌러주세요   " << endl;

			setcolor(WHITE, BLACK);
		}

		if (MyCharacter.GetCurrentHP() <= 0)	// 캐릭터 부활시 처리
		{
			MyCharacter.Dead();
			FLAG_infoWindowUpdate = true;
		}
	}
}
void Game::Playing_Game_Frame()		// 전체 틀
{
	system("mode con cols=140 lines=70"); // 나중에 게임진행창의 크기가 변경됐을때 주석을 풀어서 쓸 것.
	system("cls");
	
	// 전체 틀
	setcolor(DARKGRAY, DARKGRAY);
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n";
	for (int i = 0; i < 67; i++)
	{
		cout << "■";
		setcolor(WHITE, BLACK);
		cout << "                                                                                                                                        ";
		setcolor(DARKGRAY, DARKGRAY);
		cout << "■\n";
	}
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n";

	// 중앙 가로
	gotoxy(0, 28); cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■";
	// 중앙 세로
	for (int i = 0; i < 28; i++)
	{
		gotoxy(69, i); cout << "■";
	}
	setcolor(WHITE, BLACK);
}


//=====================================================
// 중 - 맵 출력 관련 함수
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

	// 맵 구현부 (2차원배열을 맵으로 만들어 출력)
	gotoxy(2, 1);		// Playing_Game_Frame에 의해 x = 2, y = 1로 시작
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
			else if (object == '1')			// 벽
			{
				setcolor(WHITE, WHITE);
				cout << '1';
			}
			else if (object == 'c')			// 내 캐릭터
			{
				setcolor(YELLOW, BLACK);
				MyCharacter.pos.x = j + 2;	// 캐릭터 좌표값 설정
				MyCharacter.pos.y = i + 1;	// 캐릭터 좌표값 설정
				cout << '@';
				TempMap[i][j] = '0';		// 캐릭터 시작위치를 '0'값으로 변경(나중에 이동할수 있도록)
			}
			else if (object == 'm')			// 몬스터
			{
				setcolor(BLACK, BLACK);		// 몬스터 맵에 안보이게 하기 (몬스터전투 구현완료시 사용할 것)
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
		gotoxy(2, 1 + 1 + i); // Playing_Game_Frame에 의해 x = 2, y = 1로 시작한 후, y+1부터 출력
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

	////빈공간에 몬스터 생성함수
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

	// 맵 구현부 (2차원배열을 맵으로 만들어 출력)
	gotoxy(2, 1);		// Playing_Game_Frame에 의해 x = 2, y = 1로 시작
	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < 68; j++)
		{
			char temp = tempMap[i][j];

			if (temp == '0')
				cout << " ";
			else if (temp == '1')			// 벽위치
			{
				setcolor(WHITE, WHITE);
				cout << "#";
				setcolor(WHITE, BLACK);
			}
			else if (temp == 'c')			// 내 캐릭터 위치
			{
				setcolor(YELLOW, BLACK);
				My_Character.pos.x = j + 2;// 캐릭터 좌표값 설정
				My_Character.pos.y = i + 1;// 캐릭터 좌표값 설정
				cout << "@";
				tempMap[i][j] = '0';	// 캐릭터 시작위치를 '0'값으로 변경(나중에 이동할수 있도록)
				setcolor(WHITE, BLACK);
			}
			else if (temp == 'm')			// 몬스터
			{
				//setcolor(LIGHTGREEN, LIGHTGREEN);	// 현재 테스트용으로 사용중
				setcolor(BLACK, BLACK); // 몬스터 맵에 안보이게 하기 (몬스터전투 구현완료시 사용할 것)
				cout << "m";
				setcolor(WHITE, BLACK);
			}
			else if (temp == 's')			// store 위치
			{
				setcolor(LIGHTGREEN, BLACK);
				cout << "#";
				setcolor(WHITE, BLACK);
			}
			else if (temp == 'd')			// Destination 위치
			{
				setcolor(LIGHTPURPLE, LIGHTPURPLE);
				cout << "*";
				setcolor(WHITE, BLACK);
			}
		}
		gotoxy(2, 1 + 1 + i); // Playing_Game_Frame에 의해 x = 2, y = 1로 시작한 후, y+1부터 출력
	}


	// 맵 원본 표시 지우지 말것 !! 사용할 일이 생길수도..
	//gotoxy(2, 1);
	//for (int i = 0; i < 27; i++)
	//{
	//	for (int j = 0; j < 68; j++)
	//	{
	//		char temp = tempMap[i][j];
	//		cout << temp;
	//
	//	}
	//	gotoxy(2, 1 + 1 + i); // Playing_Game_Frame에 의해 x = 2, y = 1로 시작한 후, y+1부터 출력
	//}

}*/
#pragma endregion

//=====================================================
// 중 - 캐릭터 정보창(스탯, 인벤토리) 출력 관련 함수
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
void Game::Character_Status(int dungeonStage)		// 캐릭터 상태창(캐릭터 정보창,  인벤토리창)
{
	Remove_Character_Info_Window();
	gotoxy(98, 2);  cout << "< 캐릭터 정보 >";
	gotoxy(118, 2); cout << " [p] - 게임종료";
	gotoxy(118, 3); cout << " [U] - 캐릭터 정보";
	gotoxy(118, 4); cout << " [I] - 인벤토리";

	setcolor(RED, LIGHTCYAN);
	gotoxy(71, 1); cout << "보유 골드 : " << MyCharacter.GetGold() <<"G";
	setcolor(WHITE, BLACK);

	gotoxy(80, 6);  cout << "닉네임 : " << MyCharacter.GetName();
	gotoxy(100,6);  cout << "  직업 : " << Class_ItoS(MyCharacter.GetClass());
	gotoxy(80, 8);  cout << "    LV : " << MyCharacter.GetLV();
	gotoxy(80, 9);  cout << "    HP : " << MyCharacter.GetCurrentHP() << "/" << MyCharacter.GetMaxHP();
	gotoxy(80, 10); cout << "    MP : " << MyCharacter.GetCurrentMP() << "/" << MyCharacter.GetMaxMP();
	gotoxy(80, 11); cout << "공격력 : " << MyCharacter.GetAtt() + MyCharacter.GetAddAtt() << "(" << MyCharacter.GetAtt() << "+" << MyCharacter.GetAddAtt() << ")";
	gotoxy(80, 12); cout << "방어력 : " << MyCharacter.GetDef();
	gotoxy(80, 13); cout << "경험치 : " << MyCharacter.GetCurrentExp() << "/" << MyCharacter.GetMaxExp();
	gotoxy(78, 14); cout << "현재위치 : 던전 " << dungeonStage << "층";

}
void Game::Character_Inventory()
{
	Remove_Character_Info_Window();
	gotoxy(97, 2); cout << "< 인벤토리 정보 >";
	gotoxy(118, 2); cout << " [p] - 게임종료";
	gotoxy(118, 3); cout << " [U] - 캐릭터 정보";
	gotoxy(118, 4); cout << " [I] - 인벤토리";
	gotoxy(117, 5); cout << "[1~9] - 아이템사용";
	

	setcolor(RED, LIGHTCYAN);
	gotoxy(71, 1); cout << "보유 골드 : " << MyCharacter.GetGold() <<"G";
	setcolor(WHITE, BLACK);
	//gotoxy(71, 6); cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■";
	MyCharacter.inventory.ShowInventory();
	//gotoxy(71, 16); cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■";
	
}
void Game::Remove_Character_Info_Window()	// 캐릭터 상태창 지우는 함수
{
	for (int row = 1; row < 28; row++)
	{
		gotoxy(71, row); cout << "                                                                  ";
	}                                                                                                   
}


//=====================================================
// 중 - 게임진행 출력창 (상점, 몬스터 전투)
//=====================================================
inline void Game::Remove_GameProcess_Window()		// 상점화면, 배틀화면 지우기
{
	for (int row = 29; row <= 67; row++)	// 게임진행창 전체 지우기
	{
		gotoxy(2, row); cout << "                                                                                                                                        ";
	}

	//for (int row = 29; row <= 67; row++)	// 게임진행창 왼쪽 반만 지우기 (로그남김)
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
	gotoxy(72, 67); cout << "아무키나 누르세요....";
	setcolor(WHITE, BLACK);
	input = _getch();
	for (int row = 29; row <= 67; row++)	// 게임진행창 전체 지우기
	{
		gotoxy(2, row); cout << "                                                                                                                                        ";
	}
}

// 상점 관련
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
		if (FLAG_infoWindowUpdate)		// 캐릭 정보창 업데이트
		{
			FLAG_infoWindowUpdate = false;
			Character_Info_Window(infoWindowType, dungeonStage);	// 정보창 업뎃
			MyCharacter.inventory.ShowInventory_In_Store();	// 상점내 인벤토리 업뎃
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
			Character_Info_Window(infoWindowType, dungeonStage);	// U, I 눌렀을때 바꾸도록
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

		case SPACE_BAR : // 테스트용
			MyCharacter.SetGold(500000);
			break;

		default:
			Set_Color %= MAX_CONSOLE_COLOR_NUM;
			setcolor(BLACK, Set_Color);	// 출력 위치지정, 색지정
			gotoxy(48, 65); cout << "현재 상점 이용중입니다. 나간 후에 시도해주세요";
			setcolor(WHITE, BLACK);
			Set_Color++;	
		}
		FLAG_infoWindowUpdate = true; // 상점에서 어떤 상호작용을 하던지 정보창이 업뎃되도록,
	}
	// gotoxy(2,67); cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■";
}
void Game::Store_Screen(int dungeonStage)
{
	//gotoxy(2,29); cout << "
	gotoxy(48, 31);  cout << "=============================================";
	gotoxy(47, 32);  cout << "｜               던전 " << dungeonStage << "층 상점              ｜";
	gotoxy(48, 33);  cout << "=============================================";


	gotoxy(115, 30); cout << "   [P]- 상점 나가기";
	gotoxy(113, 31); cout << "[방향키]- 상점 나가기";
	gotoxy(114, 32); cout << "    [R]-판매구매모드";
	gotoxy(115, 33); cout << " [1~9]- 아이템 구매";
	gotoxy(115, 34); cout << " [1~9]- 아이템 판매";

	for (int i = 37; i <= 57; i++)
	{
		gotoxy(69, i); cout << "∥";
	}

	switch (dungeonStage)
	{
	case 1:
		gotoxy(25, 36);  cout << "<< 장비 아이템 >>";
		gotoxy(20, 38);  cout << "1. 초심자의 대검\t200Gold";
		gotoxy(20, 39);  cout << "   초심자의 대검 - 공격력 +10";
		gotoxy(20, 41);  cout << "2. 초심자의 죽창\t500Gold";
		gotoxy(20, 42);  cout << "   초심자의 죽창 - 공격력 +20";


		gotoxy(25, 46); cout << "<< 소비 아이템 >>";
		gotoxy(20, 48); cout << "3. 빨간포션\t30Gold";
		gotoxy(20, 49); cout << "   빨간포션 - HP을(를) 30회복합니다";
		gotoxy(20, 51); cout << "4. 파란포션\t50Gold";
		gotoxy(20, 52); cout << "   파란포션 - MP을(를) 30회복합니다";

		gotoxy(95, 36); cout << "<< 인벤토리 >>";
		MyCharacter.inventory.ShowInventory_In_Store();
		break;

	case 2:
		gotoxy(25, 36);  cout << "<< 장비 아이템 >>";
		gotoxy(20, 38);  cout << "1. 중급자의 대검\t1200Gold";
		gotoxy(20, 39);  cout << "   중급자의 대검 - 공격력 +40";
		gotoxy(20, 41);  cout << "2. 중급자의 죽창\t2000Gold";
		gotoxy(20, 42);  cout << "   중급자의 죽창 - 공격력 +55";


		gotoxy(25, 46); cout << "<< 소비 아이템 >>";
		gotoxy(20, 48); cout << "3. 주황포션\t50Gold";
		gotoxy(20, 49); cout << "   주황포션 - HP을(를) 70회복합니다";
		gotoxy(20, 51); cout << "4. 남색포션\t70Gold";
		gotoxy(20, 52); cout << "   남색포션 - MP을(를) 80회복합니다";

		gotoxy(95, 36); cout << "<< 인벤토리 >>";
		MyCharacter.inventory.ShowInventory_In_Store();
		break;
	}
}
void Game::Store_BuyMode(int dungeonStage,int input)	// 상점에서 구매모드일때
{
	switch (dungeonStage)
	{
	case 1:	// 던전 1층
		switch (input)
		{
		case '1':
			MyCharacter.inventory.BuyItem(new Equipment("초심자의 대검", 200, 10));
			break;
		case '2':
			MyCharacter.inventory.BuyItem(new Equipment("초심자의 죽창", 500, 20));
			break;
		case '3':
			MyCharacter.inventory.BuyItem(new Potion("빨간포션", 30, 0, 30, 1));
			break;
		case '4':
			MyCharacter.inventory.BuyItem(new Potion("파란포션", 0, 30, 50, 1));
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
	case 2:	// 던전 2층
		switch (input)
		{
		case '1':
			MyCharacter.inventory.BuyItem(new Equipment("중급자의 대검", 1200, 40));
			break;
		case '2':
			MyCharacter.inventory.BuyItem(new Equipment("중급자의 죽창", 2000, 55));
			break;
		case '3':
			MyCharacter.inventory.BuyItem(new Potion("주황포션", 70, 0, 50, 1));
			break;
		case '4':
			MyCharacter.inventory.BuyItem(new Potion("남색포션", 0, 80, 70, 1));
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
	case 3:	// 던전 3층
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
void Game::Store_SellMode(int input)	// 상점에서 판매모드일때
{
	int index = input - 48 - 1;	// 아스키 -48, 인덱스 -1
	//setcolor(BLACK, WHITE);	// 상점 디버그용 // 테스트
	//gotoxy(48, 59); cout << "입력숫자 : " << (char)input;
	//setcolor(WHITE, BLACK);

	MyCharacter.inventory.Sell_Items(index);
}

// 몬스터 전투관련
void Game::Battle_Process(int dungeonStage, int &infoWindowType)
{
	Monster monster("noname", 0, 0, 0, 0, 0);

	Monster_Decision(dungeonStage ,monster);		// 만날 몬스터 결정
	Battle_Screen(&monster);

	unsigned int input = 0;
	bool monster_attack_turn = false;				// true - 몬스터의 공격턴 됐을 시

	FLAG_Monster_Observation = false;
	FLAG_playing_battle = true;
	FLAG_infoWindowUpdate = true;
	Battle_log_row = MIN_BATTLE_LOG_ROW;			// 전투 시작시 로그 시작은 27행으로 맞춰놓기 

	thread t1(Game::Thread_InBattle, ref(m));
	int testnum = 0;
	while (FLAG_playing_battle)
	{
		m.lock();
		
		if (monster_attack_turn)	// 몬스터 공격턴이면 공격하고 정보업뎃
		{
			monster_attack_turn = false;
			monster.Attack(&MyCharacter, dungeonStage);
		}
		
		if (FLAG_infoWindowUpdate)	// 캐릭 정보창 업뎃(전투시 실시간반영)
		{
			FLAG_infoWindowUpdate = false;
			Remove_Inventory_In_Battle();

			Character_Info_Window(infoWindowType, dungeonStage);
			monster.ShowMonsterInfo();
			//gotoxy(50, 30); cout << "캐릭정보수정, " << testnum++;
		}

		if (MyCharacter.GetCurrentHP() <= 0)
		{
			FLAG_playing_battle = false;
			Game::Remove_At_Battle_End();	// 누르면 화면지우고 진행
			Game::Make_Map_Dungeon(dungeonStage);	// ※순서주의※ 죽었으니 맵을 업뎃함
			m.unlock();
			break;
		}
		Control_BattleLog();		// 배틀로그 행 조절
		m.unlock();

		input = Avoid_Garbage_getch();
		m.lock();
		FLAG_infoWindowUpdate = true;
		switch (input)
		{
		case '1':					// 기본공격
			monster_attack_turn = true;
			MyCharacter.Attack(&monster);
			break;

		case '2':					// 스킬 (미구현)
			monster_attack_turn = true;
			MyCharacter.Attack(&monster);
			break;

		case '3':					// 아이템 사용
			if (Battle_UseItem())		// 0 리턴은 행동을 취하지 않음(턴소모X)
				monster_attack_turn = true;
			break;

		case '4':					// 관찰하기
			monster_attack_turn = true;
			Battle_ObservMonster();
			break;

		case '5':					// 도망가기 
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

	int randomMonster = rand() % 100;	// 확률구현
	switch (dungeonStage)
	{
	case 1:		// 던전 1층		// 이름, 레벨, 체력, 공격력, 경험치, 돈
		if (randomMonster < 30)
			monster.SetMonster("슬라임", 1, 35, 5, 5, 20);
		else if (randomMonster < 60)
			monster.SetMonster("검은 슬라임", 1, 60, 12, 10, 40);
		else if (randomMonster < 90)
			monster.SetMonster("하얀 슬라임", 1, 70, 8, 10, 40);
		else
			monster.SetMonster("킹 슬라임", 2, 150, 9, 20, 100);
		break;
	case 2:		// 던전 2층		// 이름, 레벨, 체력, 공격력, 경험치, 돈
		if (randomMonster < 30)
			monster.SetMonster("네키", 2, 70, 10, 15, 20);
		else if (randomMonster < 60)
			monster.SetMonster("검은 네키", 2, 130, 40, 40, 80);
		else if (randomMonster < 90)
			monster.SetMonster("하얀 네키", 2, 180, 25, 40, 80);
		else
			monster.SetMonster("대왕 네키", 4, 320, 25, 300, 300);
		break;
	case 3:		// 던전 3층		// 이름, 레벨, 체력, 공격력, 경험치, 돈
		if (randomMonster < 25)
			monster.SetMonster("카고", 3, 150, 35, 60, 100);
		else if (randomMonster < 50)
			monster.SetMonster("하얀 카고", 3, 230, 40, 80, 180);
		else if (randomMonster < 70)
			monster.SetMonster("검은 카고", 4, 200, 45, 80, 180);
		else if (randomMonster < 85)
			monster.SetMonster("오래된 카고", 5, 180, 150, 100, 200);
		else
			monster.SetMonster("여왕 카고", 5, 400, 45, 300, 400);
		break;
	case 4:		// 던전 4층
		break;
	case 5:		// 던전 5층
		break;
	case 6:		// 던전 6층
		break;
	case 7:		// 던전 7층
		break;
	case 8:		// 던전 8층
		break;
	case 9:		// 던전 9층
		break;
	case 10:	// 던전 10층
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
	//		gotoxy(30, 29);  cout << "★☆★☆★☆★☆★☆★☆★☆";
	//		gotoxy(30, 31);  cout << "☆★☆★☆★☆★☆★☆★☆★";
	//	}
	//	else {
	//		gotoxy(30, 29);  cout << "☆★☆★☆★☆★☆★☆★☆★";
	//		gotoxy(30, 31);  cout << "★☆★☆★☆★☆★☆★☆★☆";
	//	}
	//	gotoxy(30, 30); setcolor(RED, BLACK);  cout << "      "; cout << monster->GetName() << " 발견       ";
	//	
	//	Sleep(20);
	//}
	setcolor(WHITE, BLACK);
	gotoxy(2, 67); setcolor(BLACK, WHITE); cout << "몬스터와 전투시 모든 행동은 턴을 소모합니다.";

	setcolor(CYAN, BLACK);
	int row1 = 29, row2 = 29;
	//gotoxy(2,29);	cout << "행동을 선택하세요";
	gotoxy(2, row1++);	cout << "[1] 기본공격         ";	gotoxy(23, row2++); cout << "|";
	gotoxy(2, row1++);	cout << "[2] 스킬             ";	gotoxy(23, row2++); cout << "|";
	gotoxy(2, row1++);	cout << "[3] 아이템           ";	gotoxy(23, row2++); cout << "|";
	gotoxy(2, row1++);	cout << "[4] 관찰하기         ";	gotoxy(23, row2++); cout << "|";
	gotoxy(2, row1++);	cout << "[5] 도망가기 (70%)   ";	gotoxy(23, row2++); cout << "|";
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
		gotoxy(63, 30); cout << " 도망가기 성공 ";
		setcolor(WHITE, BLACK);
	}
	else
	{
		setcolor(BLACK, WHITE);	
		gotoxy(63, 30); cout << " 도망가기 실패 ";
		setcolor(WHITE, BLACK);
	}
}
void Game::Battle_ObservMonster()
{
	FLAG_Monster_Observation = true;	// true - 관찰하기로 보는 몬스터 추가정보 띄우기
	 
	gotoxy(72, Battle_log_row += 2); cout << "▣ ";
	setcolor(GREEN, BLACK);	cout << MyCharacter.GetName();
	setcolor(WHITE, BLACK); cout << "은(는) ";
	setcolor(LIGHTCYAN, BLACK); cout << "관찰하기";
	setcolor(WHITE, BLACK);	 cout << "를 했습니다.";
}
bool Game::Battle_UseItem()
{
	Remove_Inventory_In_Battle();	// 인벤토리쪽 프린트 지우는코드
	MyCharacter.inventory.ShowInventory_In_Battle(); // 프린트 위치조정
	
	unsigned char input = 0;
	input = Avoid_Garbage_getch();
	if ('1' <= input && input <= '9')
	{
		if (MyCharacter.inventory.UseItem(input))
			return true;	// 아이템 사용성공 
		else
			return false;	// 아이템 사용실패 (슬롯에 아이템이 없음)
	}
	else
		return false;		// 템을 사용 안했다(행동을 취하지 않음)
}
void Game::Control_BattleLog()	// 배틀로그가 길어지면 행조절
{
	if (Battle_log_row >= 67)
	{	
		Battle_log_row = MIN_BATTLE_LOG_ROW;
		Remove_BattleLog();
	}
	// gotoxy(72, Battle_log_row +=2); cout << ▣■
}

