#include "main.h"



extern Character My_Character;
extern int Battle_log_row;

Inventory::Inventory()
{
	slots.reserve(sizeof(Item*)*10);
}
void Inventory::BuyItem(Item* item)
{
	bool overlap = false;

	if (slots.size() < MAX_INVENTORY_SIZE)
	{
		if (My_Character.GetGold() - item->GetPrice() < 0)	// ������ ���� ���� (���� ������) 
		{
			setcolor(BLACK, WHITE);							// ��� ��ġ����, ������
			gotoxy(48, 65); cout << "\"" << item->GetName() << "\" ��(��) ������ ���� �����մϴ�.";
			setcolor(WHITE, BLACK);
			cout << "        ";
		}
		else												// ������ ���� ���� (���� ����� ������)
		{
			if (item->GetItemType() == static_cast<int>(ItemType::Potion))	// ������ �������� ������ ��
			{
				for (int i = 0; i < slots.size(); i++)		// �κ��� �ߺ��� ������ ���� �ø���
				{
					if (item->GetName() == slots[i]->GetName())
					{
						overlap = true;
						slots[i]->SetCount(item->GetCount() + slots[i]->GetCount());
						break;
					}
				}
			}

			if (!overlap)	// �κ��� �ߺ��� ������ ���� ������ �߰�
				slots.push_back(item);
			
			My_Character.SetGold(My_Character.GetGold() - item->GetPrice());	// �� ����
		}
	}
	else	// �κ��ִ밳�� �ʰ���
	{
		setcolor(BLACK, WHITE);	// ��� ��ġ����, ������
		gotoxy(48, 65); cout << "   �κ��丮 ������ �����մϴ�   ";
		setcolor(WHITE, BLACK);
		cout << "                                         ";
	}
}
bool Inventory::UseItem(int input)
{
	
	int index = input - 48 - 1;		// �ƽ�Ű�� -48, �ε����� -1

	if (slots.size() > index)
	{	
		if (slots[index]->GetItemType() == static_cast<int>(ItemType::Potion))	// Potion �϶�
		{
			Game::Control_BattleLog();
			slots[index]->UseItem();
			
			gotoxy(72, Battle_log_row += 2); cout << "�� ";
			setcolor(GREEN, BLACK);	cout << My_Character.GetName();
			setcolor(WHITE, BLACK); cout << "��(��) ";
			setcolor(LIGHTBLUE, BLACK); cout << slots[index]->GetName();
			setcolor(WHITE, BLACK);	 cout << "����߽��ϴ�.";
		}
		else if (slots[index]->GetItemType() == static_cast<int>(ItemType::Equipment))	// ��� �϶�
		{
			
			for (int i = 0; i < slots.size(); i++)
				slots[i]->SetIsUse(0);	// ��� ��� -> ����
			
			Game::Control_BattleLog();
			slots[index]->SetIsUse(1);	// �� ��� ����
			slots[index]->UseItem();
			gotoxy(72, Battle_log_row += 2); cout << "�� ";
			setcolor(GREEN, BLACK);	cout << My_Character.GetName();
			setcolor(WHITE, BLACK); cout << "��(��) ";
			setcolor(LIGHTBLUE, BLACK); cout << slots[index]->GetName();
			setcolor(WHITE, BLACK);	 cout << "�����߽��ϴ�.";
		}

		if (slots[index]->GetCount() <= 0)		// 0���Ǹ� �κ��丮���� ����� 
			slots.erase(slots.begin() + index);
		
		return true;
	}
	return false;
}
void Inventory::Sell_Items(int index)
{
	if(slots.size() > index)
	{
		if (slots[index]->GetIsUse() != 1) // ������� �ƴҶ��� �ȼ��ֵ���.
		{
			// 1���Ǹ� (������ �������� 1�� ���̱�)
			slots[index]->SetCount(slots[index]->GetCount() - 1);
			// �Ǹ� �� ���ޱ� 
			My_Character.SetGold(My_Character.GetGold() + (slots[index]->GetPrice() / 2));
			// 0���Ǹ� �κ��丮���� ����� 
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
	gotoxy(73, 4); cout << "������   "; cout<< "     ����    ȿ��";
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
	gotoxy(85, 38); cout << "������   "; cout << "     ����    ȿ��   ";
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
	//Game::Remove_Inventory_In_Store(); // print �� ��ġ �����

	setcolor(CYAN, BLACK);
	gotoxy(2, 36); 	cout <<"[1~9] �����ۻ��  ";
	gotoxy(2, 37);  cout << "[SPACE] �ǵ��ư���";
	setcolor(WHITE, BLACK);

	int invenSize = (int)slots.size();
	cout.width(15);
	gotoxy(15, 38); cout << "������   "; cout << "     ����    ȿ��   ";
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