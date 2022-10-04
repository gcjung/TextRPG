#pragma once

// ���� ����
enum Init_State{ INTIAL_GAME_STATE, INIT_GAME, NEW_GAME_START, CONTINUE_GAME_START, GAME_INFO, GAME_EXIT};
enum Playing_State{ GAME_PLAYING_STATE=10, PLAYING_GAME};

constexpr int MAX_STAGE1_MONSTER_NUM = 100;
constexpr int MAX_STAGE2_MONSTER_NUM = 100;
constexpr int MAX_STAGE3_MONSTER_NUM = 100;
constexpr int MAX_STAGE4_MONSTER_NUM = 100;
constexpr int MAX_STAGE5_MONSTER_NUM = 100;
constexpr int MAX_STAGE6_MONSTER_NUM = 100;
constexpr int MAX_STAGE7_MONSTER_NUM = 100;
constexpr int MAX_STAGE8_MONSTER_NUM = 100;
constexpr int MAX_STAGE9_MONSTER_NUM = 100;
constexpr int MAX_STAGE10_MONSTER_NUM = 100;


//=======================================================
// Game Class - ������ ȭ��, ����� ���õ� ����Լ� ����
//=======================================================
class Game
{
public:
	static string Class_ItoS(char chractor_class);
	
	// ���� ��
	static int Initial_Game_State();
	static int Init_Screen();
	static int GameInfo_Screen();
	static int Character_Create_Screen();
	static void Init_Game_Frame();
	
	// ���� ��
	static int Playing_Game_Process();
	static void Playing_Game_Frame();

	// �� ���� �Լ�
	static void Make_Map_Dungeon(int dungeonStage);
	static void CreateMonster(char(&map)[27][68], int maxMonsterNum);
	
	// ĳ���� ����â ���� �Լ�
	static void Character_Info_Window(int state, int dungeonStage);
	static void Character_Status(int dungeonStage);
	static void Character_Inventory();
	static void Remove_Character_Info_Window();

	// ��������â ��� ����
	static void Remove_GameProcess_Window();
	static void Remove_Inventory_In_Store();
	static void Remove_Inventory_In_Battle();
	static void Remove_BattleLog();
	static void Remove_At_Battle_End();

	// ���� ����
	static void Store_Process(int dungeonStage, int& infoWindowType);
	static void Store_Screen(int dungeonStage, char state);
	static void Store_BuyState(int dungeonStage, int input);
	static void Store_SellState(int input);

	// ���� ��������
	static void Battle_Process(int dungeonStage, int& infoWindowType);
	static void Monster_Decision(int dungeonStage, Monster& monster);
	static void Battle_Screen(Monster* monster);
	static void Thread_InBattle(mutex& m);

	static void Battle_ObservMonster();
	static void Battle_RunAway();
	static bool Battle_UseItem();
	static void Control_BattleLog();
};


//static int Playing_Game_State();