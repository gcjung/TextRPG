#pragma once

#include <iostream>
#include <conio.h>		// getch �Լ�
#include <windows.h>	// console ����
#include <cstdlib>		// rand �Լ�
#include <ctime>		// �ð��� (srand �õ尪���� ���)
#include <string>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;

class Unit;
class Monster;
class Character;
class Inventory;
class Item;
//class Position;

#include "console.h"
#include "game.h"
#include "item.h"
#include "inventory.h"
#include "unit.h"

#define BUY_MODE	0
#define SELL_MODE	1

#define QUESTION_MARK	63		// ����ǥ �ƽ�Ű��
#define CARRIAGE_RETURN 13		// Enter  �ƽ�Ű��  
#define MAX_ASCII_NUM	127		// �ƽ�Ű �ִ밪
#define VIRTUAL_RETURN	99		// �θ� virtual return�� // �̰� �������.. �ڴʰ� ������

#define SUCCESS 1
#define FAIL	0
#define MIN_BATTLE_LOG_ROW  27


void Init_Console();
int Avoid_Garbage_getch();
int Percent(int percent);
