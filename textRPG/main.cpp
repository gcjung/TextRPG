#include "main.h"


Character My_Character;
char tempMap[27][68];
mutex m;	// gotoxy�� Ŀ����ġ�� �������� �� ����
int main()
{
	
	Init_Console();
	srand((int)time(NULL));	// ���������� ���� �õ尪 ����

	int game_state = INTIAL_GAME_STATE;
	while (1)
	{
		switch (game_state)
		{
		case INTIAL_GAME_STATE:
			game_state = Game::Initial_Game_State();	// ����ȭ��
			break;

		case GAME_PLAYING_STATE:
			game_state = Game::Playing_Game_State();	// ����ȭ��
			break;

		case GAME_EXIT:		// ��������
			return 0;
		}
	}
}

int Percent(int percent)		// Ȯ�� ���� �Լ�
{
	if ((rand() % 100) < percent)
	{		
		return SUCCESS;
	}
	else
	{		
		return FAIL;
	}
}

int Avoid_Garbage_getch()			// �ѱ� �� ���Ͱ� getch ó��
{
	int temp = _getch();

	if (temp == CARRIAGE_RETURN)	// ���� �Է½� ����ǥǥ�� 
	{
		return QUESTION_MARK;
	}
	//else if (temp > MAX_ASCII_NUM)	// �ִ� �ƽ�Ű�� �Ѵ� �ѱ۵��� ����ǥǥ��
	//{
	//	return QUESTION_MARK;
	//}

	return temp;
}

void Init_Console()
{
	system("mode con cols=70 lines=30 | title TXT_RPG");
	removeCursor();
}

void Show_Slime()
{
	int row = 35; 
	//gotoxy(16, row++);
	gotoxy(7, row++); cout << "                         . = @@!.     ";
	gotoxy(7, row++); cout << "                       ~=#=**=$#-     ";
	gotoxy(7, row++); cout << "     ;;-              ~:#      :=-    ";
	gotoxy(7, row++); cout << "    ;~, .             ~@        ~=,   ";
	gotoxy(7, row++); cout << "   *:~,. :           $!.=        ;=   ";
	gotoxy(7, row++); cout << "   ;::-,,~          :~~-.;        =-  ";
	gotoxy(7, row++); cout << "    ;=:~!          ;,:~,.,,       =@  ";
	gotoxy(7, row++); cout << "    .!!$.         ;-::-,. *       =#  ";
	gotoxy(7, row++); cout << "    .!          .$,::~-,,. $.     ;$  ";
	gotoxy(7, row++); cout << "     ;        ,=!-::~--,,.  !-    !#  ";
	gotoxy(7, row++); cout << "     #~     ;*:,~::~--,,,.   ,!   $@  ";
	gotoxy(7, row++); cout << "     ~#   $~-,~:::~--,,,..     ~: $@  ";
	gotoxy(7, row++); cout << "      !#@~,--::::~---,,,.       ,@#   ";
	gotoxy(7, row++); cout << "      ,*.--~::::~----,,..        ~#   ";
	gotoxy(7, row++); cout << "     .*,-=!::::~~---,,,..         $   ";
	gotoxy(7, row++); cout << "     $.-#;#@:::~---,,,,..         .*  ";
	gotoxy(7, row++); cout << "     ;-~= $@::~~---,,@~@,.         #  ";
	gotoxy(7, row++); cout << "    $.-:@-~:::~~---,#* $@..        *  ";
	gotoxy(7, row++); cout << "    #,~:;@$;:::~--,,*-  !,.....       ";
	gotoxy(7, row++); cout << "    #,~:;;;:;!*~~-,,~@ @#,, ......  ; ";
	gotoxy(7, row++); cout << "    #,~:;;;::! =#-,,,~**,,,,,.  ..  * ";
	gotoxy(7, row++); cout << "    #,~:;;;::!*##--,,,,,,,,,,.  ..  * ";
	gotoxy(7, row++); cout << "    #.-:;;:::!*=#--,,,,,,,,,,.  ..  , ";
	gotoxy(7, row++); cout << "    , -~:::::!;~$---,,,,,,,,,,..,. #  ";
	gotoxy(7, row++); cout << "     =,-~~:::;..$----,,,,,,,,,,,,  #  ";
	gotoxy(7, row++); cout << "     *-,,-~:::, $~---,,,,,,,,,,,. $   ";
	gotoxy(7, row++); cout << "      $  ,-::::;~~-----,,,,,,-,. !;   ";
	gotoxy(7, row++); cout << "      .$ .-::::;~~~~----------. #;    ";
	gotoxy(7, row++); cout << "        $.,-~::::::~~~~~~~~~, .#      ";
	gotoxy(7, row++); cout << "         ,$:.-~~::::::::~-, ~#!       ";
	gotoxy(7, row++); cout << "           -***,.,,,,,,.*!#:-         ";
	gotoxy(7, row++); cout << "              ..,$@@@@;...            ";
}