#pragma once

// 게임 상태
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
// Game Class - 게임의 화면, 진행과 관련된 멤버함수 선언
//=======================================================
class Game
{
public:
	static string Class_ItoS(char chractor_class);
	
	// 게임 전
	static int Initial_Game_State();
	static int Init_Screen();
	static int GameInfo_Screen();
	static int Character_Create_Screen();
	static void Init_Game_Frame();
	
	// 게임 중
	static int Playing_Game_Process();
	static void Playing_Game_Frame();

	// 맵 관련 함수
	static void Make_Map_Dungeon(int dungeonStage);
	static void CreateMonster(char(&map)[27][68], int maxMonsterNum);
	
	// 캐릭터 정보창 관련 함수
	static void Character_Info_Window(int state, int dungeonStage);
	static void Character_Status(int dungeonStage);
	static void Character_Inventory();
	static void Remove_Character_Info_Window();

	// 게임진행창 출력 관련
	static void Remove_GameProcess_Window();
	static void Remove_Inventory_In_Store();
	static void Remove_Inventory_In_Battle();
	static void Remove_BattleLog();
	static void Remove_At_Battle_End();

	// 상점 관련
	static void Store_Process(int dungeonStage, int& infoWindowType);
	static void Store_Screen(int dungeonStage, char state);
	static void Store_BuyState(int dungeonStage, int input);
	static void Store_SellState(int input);

	// 몬스터 전투관련
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