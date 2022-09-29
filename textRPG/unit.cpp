#include "main.h"




extern char tempMap[27][68];
extern bool FLAG_mapUpdate;
extern bool FLAG_infoWindowUpdate;
extern bool FLAG_Monster_Observation;
extern bool FLAG_playing_battle;
extern int Battle_log_row;
extern Character My_Character;

//=======================================================
// Unit Class �Լ� ����
//=======================================================
Unit::Unit() : name("NONAME"), level(1), maxHP(100), currentHP(100), att(10), def(5), gold(1000), addAtt(0)
{

}
Unit::Unit(string name, int level, int maxhp, int att, int gold)
	:name(name), level(level), maxHP(maxhp), currentHP(maxhp), att(att), def(5), gold(30), addAtt(0)
{

}

Unit::Position::Position() : x(1), y(1)
{

}

void Unit::Position::Move(int inputX,int inputY,int &dungeonStage,int &infoWindowType)	// �̵� �� ������Ʈ ��ȣ�ۿ�
{
	char mapObject = tempMap[this->y + inputY - 1][this->x + inputX - 2]; // �̸� �̵��� ���� ������Ʈ

	if (mapObject == '0')		// �� ĭ
	{
		setcolor(WHITE, BLACK);
		gotoxy(this->x, this->y);
		cout << " ";

		setcolor(YELLOW, BLACK);
		gotoxy(this->x + inputX, this->y + inputY);
		cout << "@";
		setcolor(WHITE, BLACK);

		this->x += inputX;
		this->y += inputY;
	}
	else if (mapObject == 's')	// ����
	{
		Game::Store_Process(dungeonStage, infoWindowType);
	}
	else if (mapObject == 'm')	// ����
	{
		Game::Battle_Process(dungeonStage, infoWindowType);
		tempMap[this->y + inputY - 1][this->x + inputX - 2] = '0';	// ���� ���� �� ������� ������ֱ�
	}
	else if (mapObject == 'd')	// ������
	{
		// (* dungeonStage)++; << ���߻���ҿ���
		dungeonStage = (dungeonStage % 3) + 1;	// �׽�Ʈ, 
		FLAG_mapUpdate = true;			// ���� ���������, �ʾ�����Ʈ
		FLAG_infoWindowUpdate = true;	// ���� ���������, ����â�� ���������� �����ϱ�����
	}

}

// Getter �Լ�
inline string Unit::GetName() const
{
	return this->name;
}
inline int Unit::GetLV() const
{
	return this->level;
}
inline int Unit::GetMaxHP() const
{
	return this->maxHP;
}
inline int Unit::GetCurrentHP() const
{
	return this->currentHP;
}
inline int Unit::GetAtt() const
{
	return this->att;
}
 int Unit::GetDef() const
{
	return this->def;
}
inline int Unit::GetGold() const
{
	return this->gold;
}	
inline int Unit::GetAddAtt() const
{
	return this->addAtt;
}


// Setter �Լ�
void Unit::SetName(const string& name)
{
	this->name = name;
}
void Unit::SetLV(const int level)
{
	this->level = level;
}
void Unit::SetMaxHP(const int maxhp)
{
	this->maxHP = maxhp;
}
void Unit::SetCurrentHP(const int hp)
{
	this->currentHP = hp;
}
void Unit::SetAtt(const int att)
{
	this->att = att;
}
void Unit::SetDef(const int def)
{
	this->def = def;
}
void Unit::SetGold(const int gold)
{
	this->gold = gold;
}
void Unit::SetAddAtt(const int addAtt)
{
	this->addAtt = addAtt;
}


//=======================================================
// Charactor Class �Լ� ����
//=======================================================
Character::Character() : characterClass(0), maxExp(100), currentExp(0), maxMP(100), currentMP(100),Unit()
{

}
Character::Character(int Character_Class, int MaxExp, int CurrentExp, int MaxMp, int CurrentMP)
	: characterClass(Character_Class), maxExp(MaxExp), currentExp(CurrentExp), maxMP(MaxMp), currentMP(CurrentMP)
{

}

// Getter �Լ�
int Character::GetClass() const
{
	return this->characterClass;
}
int Character::GetMaxExp() const
{
	return this->maxExp;
}
int Character::GetCurrentExp() const
{
	return this->currentExp;
}
int Character::GetMaxMP() const
{
	return this->maxMP;
}
int Character::GetCurrentMP() const
{
	return this->currentMP;
}

// Setter �Լ�
void Character::SetClass(int charac_class)
{
	this->characterClass = charac_class;
}
void Character::SetMaxExp(int max_exp)
{
	this->maxExp = max_exp;
}
void Character::SetCurrentExp(int current_exp)
{
	this->currentExp = current_exp;
}
void Character::SetMaxMP(int max_mp)
{
	this->maxMP = max_mp;
}
void Character::SetCurrentMP(int current_mp)
{
	this->currentMP = current_mp;
}
//void Character::SetResurrection()
//{
//	this->currentMP = maxMP; 
//	this->SetCurrentHP(this->GetMaxHP());
//	this->currentExp = (this->currentExp) - (this->currentExp/10);
//	this->SetGold(this->GetGold() - (this->GetGold()/10));
//}


void Character::Attack(Monster* monster)
{
	Game game;
	int totalAtt = this->GetAtt() + this->GetAddAtt();
	int damage = (rand() % totalAtt) + (totalAtt / 2);
													// ex) �Ѱ��ݷ� 100�� ��, 50~150�� ������������ �ش�.
													// ex) �Ѱ��ݷ� 150�� ��, 75~225�� ������������ �ش�.

	if ((monster->GetCurrentHP() - damage) <= 0)	// ���� ü�� 0���� �϶�
	{
		monster->SetCurrentHP(0);

		//setcolor(GREEN, BLACK);	cout << My_Character.GetName();
		gotoxy(72, Battle_log_row += 2); cout << "�� ";
		setcolor(GREEN, BLACK);	cout << My_Character.GetName();
		setcolor(WHITE, BLACK);	cout << " ����-> ";
		setcolor(RED, BLACK);	cout << monster->GetName();
		setcolor(WHITE, BLACK);	cout << "�� óġ�߽��ϴ�.";
		monster->Dead();			// ���� ����

		monster->ShowMonsterInfo();
		FLAG_playing_battle = false;
		game.Remove_At_Battle_End(); //
	}
	else												// ���� ü�� 1�̻� �϶�
	{
		monster->SetCurrentHP(monster->GetCurrentHP() - damage);
		
		gotoxy(72, Battle_log_row += 2); cout << "�� ";
		setcolor(GREEN, BLACK);	cout << My_Character.GetName();
		setcolor(WHITE, BLACK);	cout << " ����-> ";
		setcolor(RED, BLACK);	cout << monster->GetName();
		setcolor(WHITE, BLACK); cout << "��(��) ";
		setcolor(PURPLE, BLACK);cout << damage;
		setcolor(WHITE, BLACK);	cout << "�� ���ظ� �Ծ���.";
	}
}
void Character::Dead() 
{
	this->currentMP = maxMP;
	this->SetCurrentHP(this->GetMaxHP());
	this->currentExp = (this->currentExp) - (this->currentExp / 10);
	this->SetGold(this->GetGold() - (this->GetGold() / 10));
	//FLAG_playing_battle = false;
	//Game::Remove_At_Battle_End();	// ������ ȭ������� ����
	//Game::Map_Window(dungeonStage);	// �ؼ������ǡ� �׾����� ���� ������
}
//=======================================================
// Monster Class �Լ� ����
//=======================================================
Monster::Monster() : Unit(), exp(0) {}
Monster::Monster(string name, int level, int maxhp, int att, int exp, int gold) : Unit(name,level,maxhp,att,gold), exp(exp)
{

}

void Monster::SetMonster(string name, int level, int maxhp, int att, int exp, int gold)
{
	this->SetName(name);
	this->SetLV(level);
	this->SetMaxHP(maxhp);
	this->SetCurrentHP(maxhp);
	this->SetAtt(att);
	this->SetAddAtt(0);
	this->SetGold(gold);
	this->exp = exp;
}
void Monster::ShowMonsterInfo() const
{
	int row = 30;
	ShowMonster();
	
	//gotoxy(30, row++); cout << "====================" << "          ";
	gotoxy(30, row++); cout << "[LV." << GetLV() << "]  ";
	setcolor(RED, BLACK); cout << GetName() << "          "; row++;
	setcolor(WHITE, BLACK); 
	gotoxy(30, row++); cout << "HP : " << GetCurrentHP() << " / " << GetMaxHP() << "           ";
	gotoxy(30, row++); cout << "���ݷ� : " << GetAtt() << endl;
	if (FLAG_Monster_Observation)
	{
		gotoxy(30, row++);  cout << "ȹ�� ����ġ: " << GetExp() << "           ";
		gotoxy(30, row++);  cout << "ȹ��  GOLD : " << GetGold() << "           ";
	}
	//gotoxy(30, row++); cout << "====================";
}
void Monster::ShowMonster() const
{
	string tempStr;
	
	if (name.find(" ") == string::npos)
		tempStr = name;
	else
		tempStr = name.substr(name.find(" ")+1);
	//gotoxy(50, 30); cout << "ĳ���������� : " << tempStr;
	if (tempStr == "������")
		ShowSlime();
	else if (tempStr == "��Ű")
		ShowNeki();
	else
		ShowSlime();
}
void Monster::ShowSlime() const
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
void Monster::ShowNeki() const
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
}

int Monster::GetExp() const
{
	return this->exp;
}
void Monster::SetExp(int exp)
{
	this->exp = exp;
}

void Monster::Attack(Character* character,int dungeonStage)
{
	int totalAtt = this->GetAtt() + this->GetAddAtt();
	int damage;
	damage = (rand() % totalAtt) + (totalAtt / 2);	// ex) �Ѱ��ݷ� 100�� ��, 50~150�� ������������ �ش�.
													// ex) �Ѱ��ݷ� 150�� ��, 75~225�� ������������ �ش�.

	if ((character->GetCurrentHP() - damage) <= 0)		// ĳ���� ü�� 0���� �϶�
	{
		character->SetCurrentHP(0);
		
		gotoxy(72, Battle_log_row += 2); cout << "   ";
		setcolor(RED, BLACK);	cout << this->GetName();
		setcolor(WHITE, BLACK);	cout << " ����-> ";
		setcolor(GREEN, BLACK);	cout << character->GetName();
		setcolor(WHITE, BLACK); cout << "��(��) ";
		setcolor(PURPLE, BLACK); cout << damage;
		setcolor(WHITE, BLACK);	cout << "�� ���ظ� �԰� ";
		setcolor(RED, BLACK); cout << "�׾����ϴ�.";
		setcolor(WHITE, BLACK);
		//Show_snake();

		//FLAG_playing_battle = false;	
		//Game::Remove_At_Battle_End();	// ������ ȭ������� ����
		//Game::Make_Map_Dungeon(dungeonStage);	// �ؼ������ǡ� �׾����� ���� ������
	}
	else
	{
		gotoxy(72, Battle_log_row += 2); cout << "   ";
		setcolor(RED, BLACK);	cout << this->GetName();
		setcolor(WHITE, BLACK);	cout << " ����-> ";
		setcolor(GREEN, BLACK); cout << character->GetName();
		setcolor(WHITE, BLACK); cout << "��(��) ";
		setcolor(PURPLE, BLACK);cout << damage;
		setcolor(WHITE, BLACK);	cout <<"�� ���ظ� �Ծ���.";

	//	��
		character->SetCurrentHP(character->GetCurrentHP() - damage);
	}
	
}
void Monster::Dead()
{
	My_Character.SetGold(this->GetGold() + My_Character.GetGold());			// �� ȹ��

	if (My_Character.GetCurrentExp() + this->GetExp() >= My_Character.GetMaxExp()) // �������ؾߵ�
	{
		My_Character.SetCurrentExp(0);					// ���� ����ġ�� 0
		My_Character.SetLV(My_Character.GetLV() + 1);	// LV ��
		My_Character.SetMaxExp(My_Character.GetMaxExp() + My_Character.GetMaxExp() / 25);	// �ִ��ġ 20%����
		My_Character.SetMaxHP(My_Character.GetMaxHP() + (My_Character.GetMaxHP() / 15));
		My_Character.SetMaxMP(My_Character.GetMaxMP() + (My_Character.GetMaxMP() / 15));
	}
	else
	{
		My_Character.SetCurrentExp(My_Character.GetCurrentExp() + this->GetExp());
	}
}