#include "main.h"


Character MyCharacter;
char TempMap[27][68];
mutex m;	// gotoxy로 커서위치가 겹쳐지는 걸 방지

int main()
{
	Init_Console();
	srand((int)time(NULL));	// 난수생성을 위한 시드값 제공

	int game_state = INTIAL_GAME_STATE;
	while (1)
	{
		switch (game_state)
		{
		case INTIAL_GAME_STATE:
			game_state = Game::Initial_Game_State();	// 게임 전 프로세스
			break;

		case GAME_EXIT:			// 게임종료
			return 0;
		}
	}
}

int Percent(int percent)		// 확률 계산용 함수
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

int Avoid_Garbage_getch()			// 한글 및 엔터값 getch 처리
{
	int temp = _getch();

	if (temp == CARRIAGE_RETURN)	// 엔터 입력시 물음표표시 
	{
		return QUESTION_MARK;
	}
	//else if (temp > MAX_ASCII_NUM)	// 최대 아스키값 넘는 한글들을 물음표표시
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

#pragma region MyRegion
/*
void ShowSlime()
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
void ShowNeki()
{
	int row = 35;

	gotoxy(7, row++); cout << "            ,~~~~~~~-.                ";
	gotoxy(7, row++); cout << "          ,-!=*=$*==*~-               ";
	gotoxy(7, row++); cout << "         ,;*$*!**~****=-              ";
	gotoxy(7, row++); cout << "        .;:-!**!. ~**!*=~             ";
	gotoxy(7, row++); cout << "       ,*-.;*:*!  -*!;;!=:            ";
	gotoxy(7, row++); cout << "      ,;-,;$**#*  .~!;;!=:            ";
	gotoxy(7, row++); cout << "     ,;~ ;$#*=#$; .-!;;;**~           ";
	gotoxy(7, row++); cout << "     -*, *##!*#@= .-!;;;!=;           ";
	gotoxy(7, row++); cout << "     -*, *#=;*#@= .-!;:;!=;           ";
	gotoxy(7, row++); cout << "    ,::. ~*!:*#=~ .-!;:;!=;           ";
	gotoxy(7, row++); cout << "    -*;. ~!;:**~  ,:;::;!=;           ";
	gotoxy(7, row++); cout << "    -==:~!;~:!:  ,:!:::;!=;           ";
	gotoxy(7, row++); cout << "    ~*!==:~~:!;--:*;::;!*=;           ";
	gotoxy(7, row++); cout << "    -!!;::::::!$$=;;;;;!*=:           ";
	gotoxy(7, row++); cout << "     -!!!!!!!!!*=!!**!!!=;.           ";
	gotoxy(7, row++); cout << "      -!!=$=======**!!!*=:            ";
	gotoxy(7, row++); cout << "       ,-*$$===***!!;;!$:.            ";
	gotoxy(7, row++); cout << "         ,-!$=**!!!;;;*$~             ";
	gotoxy(7, row++); cout << "          .-;$==*;:;!=~.              ";
	gotoxy(7, row++); cout << "            ;!--~~:;!$-               ";
	gotoxy(7, row++); cout << "           ~;:,.,-:!*:.~;;;~          ";
	gotoxy(7, row++); cout << "          .;;,,.,-:!=--*==$*:~        ";
	gotoxy(7, row++); cout << "           ::...,~;*=:**!!!*==:.      ";
	gotoxy(7, row++); cout << "           ;;-,,~:;*==*!;;;!!=$,-~~~, ";
	gotoxy(7, row++); cout << "           ;;,,,~:;!=*!!;;;!!*$:!===;,";
	gotoxy(7, row++); cout << "           ::,.,~~:!*!!;:;;!!!=*!***$:";
	gotoxy(7, row++); cout << "           :;-.,~~:;!!;;;!!!;!!!;!*==~";
	gotoxy(7, row++); cout << "            :!--~~~:;;;!!**!!;:;!**$~ ";
	gotoxy(7, row++); cout << "            ::,.-~:;!*!*=!::;;!!**=~. ";
	gotoxy(7, row++); cout << "            .~;~~:;!**=:,:;::;**=*:.  ";
	gotoxy(7, row++); cout << "             .:****==:-. .:***==:-.   ";
	gotoxy(7, row++); cout << "              .~~~~~~.    .~~~~-.     ";


	//gotoxy(7, row++);  cout << "               ----~-----.                              ";
	//gotoxy(7, row++);  cout << "            ..-##$######$:..                            ";
	//gotoxy(7, row++);  cout << "            ;$$#!;*#:*$***=!.                           ";
	//gotoxy(7, row++);  cout << "          .:;:;#;!*:,-!=!***;,                          ";
	//gotoxy(7, row++);  cout << "        .:!,,:=;*=. .~$!;;!=;,                          ";
	//gotoxy(7, row++);  cout << "       .:*,.;$;:=*.  ~=!;;;*=;                          ";
	//gotoxy(7, row++);  cout << "       ;!, ;#$;=#=.  .-=!:;!=:                          ";
	//gotoxy(7, row++);  cout << "     .!;-.!$#$;$@#*, .,=!:;;**;                         ";
	//gotoxy(7, row++);  cout << "     .$: ,$##$;$#@#, .,=!:;!!$*	                        ";
	//gotoxy(7, row++);  cout << "     .=: ,$@#*:=#@#,..,=!:;;!==.                        ";
	//gotoxy(7, row++);  cout << "     ,=: ,=#*::$##$, .,=;:;;!$*.                        ";
	//gotoxy(7, row++);  cout << "    ,!~,  -**~:=#=-  .,*!::;!=*.                        ";
	//gotoxy(7, row++);  cout << "    -#!- .:!;~:=*~.  ,;!::;;!=*.                        ";
	//gotoxy(7, row++);  cout << "    -#$;~~*;~~:=:.  ,:*;::;;!=*.                        ";
	//gotoxy(7, row++);  cout << "    -$!*=*:~~::*;.,,;*;:::;!!==.                        ";
	//gotoxy(7, row++);  cout << "    -$*;;;:~~~~;!===*;::;;;!*==.                        ";
	//gotoxy(7, row++);  cout << "    .:=!;;:::::;!==*;;*!!;!!=*~                         ";
	//gotoxy(7, row++);  cout << "      ;**!!!**!!**= *!*=*!!!*$;                         ";
	//gotoxy(7, row++);  cout << "        ;==$#$$$$$$$$$=!!!!!*=;                         ";
	//gotoxy(7, row++);  cout << "        .,-$##$===****!!!!;!=~.                         ";
	//gotoxy(7, row++);  cout << "           -~!#$***!!!!;;;!*$-                          ";
	//gotoxy(7, row++);  cout << "             -!!*==**!;;:;**;,                          ";
	//gotoxy(7, row++);  cout << "               .*$***;:;;;**.                           ";
	//gotoxy(7, row++);  cout << "               .*!,.,-~;!!**. .                         ";
	//gotoxy(7, row++);  cout << "              ,!!~,,,,-:!*!-.:*!!*-                     ";
	//gotoxy(7, row++);  cout << "              ,=:,,.,,-:!=;.~*$=$$!~~.                  ";
	//gotoxy(7, row++);  cout << "              ,=~ . .-~;!=!-$=!!!!=$$~.                 ";
	//gotoxy(7, row++);  cout << "              ,=:,..,~;!!=$=*!!;;!!**$~ .               ";
	//gotoxy(7, row++);  cout << "              ,$:-,-~~;;!===*!;;;!;!*$:-****!.          ";
	//gotoxy(7, row++);  cout << "              ,$~,,,~::;!==*!;:;;!!!*$!;=====;.         ";
	//gotoxy(7, row++);  cout << "              ,=~...-~::;**!!;:;;!!!!==*!!!*=$-         ";
	//gotoxy(7, row++);  cout << "              ,*:,.,-~~:;!!;;;;;!!!;!!*!;!!*==-         ";
	//gotoxy(7, row++);  cout << "               ,!;--~~~~::;;;!!!**!!;;;;!!*$=-          ";
	//gotoxy(7, row++);  cout << "                *;,.,~~~:;!!!*=*;:;!!;;!**=*~.          ";
	//gotoxy(7, row++);  cout << "                ::-.,-~:;!*==!;!;~~::!!*=$*~            ";
	//gotoxy(7, row++);  cout << "                 ~*::~~;!*===- ,*;~~:***==~             ";
	//gotoxy(7, row++);  cout << "                  ~=$$$###!,.   ,*$$###!...             ";
	//gotoxy(7, row++);  cout << "                  .-------,      -~-~~-,                ";

}
*/
#pragma endregion


