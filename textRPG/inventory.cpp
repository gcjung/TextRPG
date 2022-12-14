#include "main.h"



extern Character MyCharacter;
extern int Battle_log_row;

Inventory::Inventory()
{
	slots.reserve(sizeof(Item*)*10);
}
void Inventory::BuyItem(Item* item)
{
	bool overlap = false;
	if (slots.size() < MAX_INVENTORY_SIZE)		// 인벤토리 공간이 있을 때
	{
		if (MyCharacter.GetGold() - item->GetPrice() < 0)	// 아이템 구매 실패 (돈이 없을때) 
		{
			setcolor(BLACK, BLACK);	gotoxy(48, 65);
			cout << "                                                 ";
			setcolor(LIGHTCYAN, BLACK);	gotoxy(48, 65);
			cout << "\"" << item->GetName() << "\" 을(를) 구매할 돈이 부족합니다.";
		}
		else												// 아이템 구매 성공 (돈이 충분히 있을때)
		{
			if (item->GetItemType() == static_cast<int>(ItemType::Potion))	// 구매한 아이템이 포션일 때
			{
				for (int i = 0; i < slots.size(); i++)		
				{
					if (item->GetName() == slots[i]->GetName())			// 이미 갖고 있는지 확인
					{
						overlap = true;
						slots[i]->SetCount(item->GetCount() + slots[i]->GetCount());
						break;
					}
				}
			}

			if (!overlap)	// 인벤토리에 템이 없다면 아이템 추가
				slots.push_back(item);
			
			MyCharacter.SetGold(MyCharacter.GetGold() - item->GetPrice());	// 돈 지불
		}
	}
	else	// 인벤 최대 개수 초과시
	{
		setcolor(BLACK, BLACK); gotoxy(48, 65); cout << "                                                 ";
		setcolor(LIGHTBLUE, BLACK); gotoxy(56, 65); cout << "인벤토리 공간이 부족합니다";
	}
}
bool Inventory::UseItem(int input)
{
	
	int index = input - 48 - 1;		// 아스키값 -48, 인덱스값 -1

	if (slots.size() > index)
	{	
		if (slots[index]->GetItemType() == static_cast<int>(ItemType::Potion))	// Potion 일때
		{
			Game::Control_BattleLog();
			slots[index]->UseItem();
			
			gotoxy(72, Battle_log_row += 2); cout << "▣ ";
			setcolor(GREEN, BLACK);	cout << MyCharacter.GetName();
			setcolor(WHITE, BLACK); cout << "은(는) ";
			setcolor(LIGHTBLUE, BLACK); cout << slots[index]->GetName();
			setcolor(WHITE, BLACK);	 cout << "사용했습니다.";
		}
		else if (slots[index]->GetItemType() == static_cast<int>(ItemType::Equipment))	// 장비 일때
		{
			
			for (int i = 0; i < slots.size(); i++)
				slots[i]->SetIsUse(0);	// 모든 장비 -> 해제
			
			Game::Control_BattleLog();
			slots[index]->SetIsUse(1);	// 이 장비만 장착
			slots[index]->UseItem();
			gotoxy(72, Battle_log_row += 2); cout << "▣ ";
			setcolor(GREEN, BLACK);	cout << MyCharacter.GetName();
			setcolor(WHITE, BLACK); cout << "은(는) ";
			setcolor(LIGHTBLUE, BLACK); cout << slots[index]->GetName();
			setcolor(WHITE, BLACK);	 cout << "장착했습니다.";
		}

		if (slots[index]->GetCount() <= 0)		// 0개되면 인벤토리에서 지우기 
			slots.erase(slots.begin() + index);
		
		return true;
	}
	return false;
}
void Inventory::Sell_Items(int index)
{
	if(slots.size() > index)
	{
		if (slots[index]->GetIsUse() != 1) // 장착장비가 아닐때만 팔수있도록.
		{
			// 1개판매 (개수가 여러개면 1개 줄이기)
			slots[index]->SetCount(slots[index]->GetCount() - 1);
			// 판매 후 돈받기 
			MyCharacter.SetGold(MyCharacter.GetGold() + (slots[index]->GetPrice() / 2));
			// 0개되면 인벤토리에서 지우기 
			if (slots[index]->GetCount() <= 0)
			{
				delete slots[index];
				slots.erase(slots.begin() + index);
			}
		}
	}
}
void Inventory::ShowInventory()
{
	int invenSize = (int)slots.size();
	cout.width(15);
	gotoxy(73, 4); cout << "아이템   "; cout<< "     개수    효과";
	gotoxy(73, 5); cout << "-------------------------------------";
	for (int i = 0; i < invenSize; i++)
	{
		gotoxy(71, 6+i); cout << i + 1 << ".";
		gotoxy(73, 6+i); slots[i]->ShowInfo();
	}
	
	gotoxy(73, 6 + invenSize); cout << "-------------------------------------";
}
void Inventory::ShowInventory_In_Store()
{
	Game::Remove_Inventory_In_Store();

	int invenSize = (int)slots.size();
	cout.width(15);
	gotoxy(85, 38); cout << "아이템   "; cout << "     개수    효과   ";
	gotoxy(85, 39); cout << "=====================================";
	for (int i = 0; i < invenSize; i++)
	{
		gotoxy(83, 40 + i);	cout << i+1 << ".";
		gotoxy(85, 40 + i); slots[i]->ShowInfo();
	}
	gotoxy(85, 40 + invenSize); cout << "-------------------------------------";

}
void Inventory::ShowInventory_In_Battle()
{
	//Game::Remove_Inventory_In_Store(); // print 찍어낼 위치 지우기

	setcolor(CYAN, BLACK);
	gotoxy(2, 36); 	cout <<"[1~9] 아이템사용  ";
	gotoxy(2, 37);  cout << "[SPACE] 되돌아가기";
	setcolor(WHITE, BLACK);

	int invenSize = (int)slots.size();
	cout.width(15);
	gotoxy(15, 38); cout << "아이템   "; cout << "     개수    효과   ";
	gotoxy(15, 39); cout << "=====================================";
	for (int i = 0; i < invenSize; i++)
	{
		gotoxy(13, 40 + i);	cout << i + 1 << ".";
		gotoxy(15, 40 + i); slots[i]->ShowInfo();
	}
	gotoxy(15, 40 + invenSize); cout << "-------------------------------------";

}

void Inventory::Test()
{
	cout << "slot : " << slots.capacity();
}