#pragma once

#include <iostream>
#include <conio.h>		// getch 함수
#include <windows.h>	// console 관련
#include <cstdlib>		// rand 함수
#include <ctime>		// 시간값 (srand 시드값으로 사용)
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

#define BUY_STATE	0
#define SELL_STATE	1

#define QUESTION_MARK	63		// 물음표 아스키값
#define CARRIAGE_RETURN 13		// Enter  아스키값  
#define MAX_ASCII_NUM	127		// 아스키 최대값

#define SUCCESS 1
#define FAIL	0
#define MIN_BATTLE_LOG_ROW  27


void Init_Console();
int Avoid_Garbage_getch();
int Percent(int percent);
