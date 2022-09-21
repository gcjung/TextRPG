#pragma once

#define MAX_INVENTORY_SIZE 21		// �κ��丮 ȭ�� ����� �Ѱ��,, 21�� ���� (�ִ� �κ��丮 ������)

//=====================================================
// �κ��丮 Ŭ���� 
//=====================================================
class Inventory
{
private:
	vector<Item*> slots;
public:
	Inventory();
	void BuyItem(Item* Item, Unit* unit);
	bool UseItem(int index);
	void Sell_Items(int index);

	void ShowInventory();
	void ShowInventory_In_Store();
	void ShowInventory_In_Battle();
	void Test();
};