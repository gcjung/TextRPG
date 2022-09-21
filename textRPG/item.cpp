#include "main.h"


extern Character My_Character;


//=====================================================
// Item Class ����
//=====================================================
Item::Item() : name("NONAME"), price(0) {}
Item::Item(string name, int price) : name(name), price(price){}
Item::~Item()
{
	//setcolor(BLACK, WHITE);	// ���� ����׿� // �׽�Ʈ
	gotoxy(48, 59); cout << "~Item ����";
	//setcolor(WHITE, BLACK);
}

// setter
void Item::SetName(const string& name)
{
	this->name = name;
}
void Item::SetPrice(int)
{
}

// getter
string Item::GetName() const
{
	return name;
}
int Item::GetPrice() const
{
	return this->price;
}


// virtual
//int Item::GetCount()
//{
//	return VIRTUAL_RETURN;
//}
//void Item::SetCount(int count)
//{
//
//}

//int Item::GetIsUse()
//{
//	return 0;		// ���࿡ ���ؼ� ������� �ƴϴϱ� �׻� 0, 
//}
//void Item::SetIsUse(int isuse)
//{
//
//}

//void Item::UseItem()
//{
//
//}
//void Item::ShowInfo()
//{
//	cout << "Item" << endl;
//}
//int Item::IsEquipment()
//{
//	return VIRTUAL_RETURN;
//}



//=====================================================
// Equipment Class ����
//=====================================================
Equipment::Equipment() :HP(0), MP(0), Att(0), Def(0), IsUse(0),Count(1) {}
Equipment::Equipment(string Name, int Price, int Att)	// �����
	:Item(Name,Price), Att(Att), IsUse(0), Count(1),HP(0), MP(0), Def(0) {}
Equipment::Equipment(string Name, int Price, int Hp, int Mp, int Def) // ����
	:Item(Name, Price), HP(Hp), MP(Mp),Def(Def),IsUse(0), Count(1), Att(0) {}
Equipment::~Equipment()
{
	gotoxy(48, 57); cout << "~Equipment ����";
}

//virtual
int Equipment::GetCount()
{
	return this->Count;
}
void Equipment::SetCount(int count)
{
	this->Count = count;
}

int Equipment::GetIsUse()
{
	return IsUse;
}
void Equipment::SetIsUse(int isuse)
{
	this->IsUse = isuse;
}

void Equipment::UseItem()
{
	My_Character.SetAddAtt(this->Att);
}
void Equipment::ShowInfo()
{
	if (this->GetName() == "�ʽ����� ���")
	{
		cout.width(15);
		cout << this->GetName();
		if (IsUse) { cout << "(����)";	cout.width(2); }
		else cout.width(8);
		cout << this->Count;
		cout.width(13);
		cout << "���ݷ� +10";
	}
	else if (this->GetName() == "�ʽ����� ��â")
	{
		cout.width(15);
		cout << this->GetName();
		if (IsUse) { cout << "(����)";	cout.width(2); }
		else cout.width(8);
		cout << this->Count;
		cout.width(13);
		cout << "���ݷ� +20";
	}
	else if (this->GetName() == "�߱����� ���")
	{
		cout.width(15);
		cout << this->GetName();
		if (IsUse) { cout << "(����)";	cout.width(2); }
		else cout.width(8);
		cout << this->Count;
		cout.width(13);
		cout << "���ݷ� +40";
	}
	else if (this->GetName() == "�߱����� ��â")
	{
		cout.width(15);
		cout << this->GetName();
		if (IsUse) { cout << "(����)";	cout.width(2); }
		else cout.width(8);
		cout << this->Count;
		cout.width(13);
		cout << "���ݷ� +55";
	}
}
int Equipment::IsEquipment()	// [1] - ��� ������, [0] - �Һ������ 
{
	return 1;
}



//=====================================================
// Potion Class ����
//=====================================================
Potion::Potion() :Count(0), HP(0), MP(0) {}
Potion::Potion(string Name, int Hp, int Mp, int Price, int Count)
	: Item(Name, Price), Count(Count), HP(Hp), MP(Mp) {}
Potion::~Potion()
{
	gotoxy(48, 60); cout << "~Potion ����";
}

//virtual
int Potion::GetCount()
{
	return this->Count;
}
void Potion::SetCount(int count)
{
	this->Count = count;
}

int Potion::GetIsUse()
{
	return VIRTUAL_RETURN;
}
void Potion::SetIsUse(int isuse)
{

}

void Potion::UseItem()
{
	SetCount(GetCount() - 1);	// 1���Ǹ� (������ �������� 1�� ���̱�)

	// HP ȸ��
	if ((My_Character.GetCurrentHP() + this->HP) > My_Character.GetMaxHP()) // HPȸ�������� MaxMP���� Ŭ��
	{
		My_Character.SetCurrentHP(My_Character.GetMaxHP());
	}
	else	// HPȸ�������� Max���� ������
	{
		My_Character.SetCurrentHP(My_Character.GetCurrentHP() + this->HP);
	}

	// MP ȸ��
	if (My_Character.GetCurrentMP() + this->MP > My_Character.GetMaxMP()) // MPȸ�������� MaxMP���� Ŭ��
	{
		My_Character.SetCurrentMP(My_Character.GetMaxMP());
	}
	else	// MPȸ�������� Max���� ������
	{
		My_Character.SetCurrentMP(My_Character.GetCurrentMP() + this->MP);
	}

}
void Potion::ShowInfo()
{
	if (this->GetName() == "��������")
	{
		cout.width(15);
		cout << this->GetName();
		cout.width(8);
		cout << this->Count;
		cout.width(13);
		cout << "HP +30";
	}
	else if (this->GetName() == "�Ķ�����")
	{
		cout.width(15);
		cout << this->GetName();
		cout.width(8);
		cout << this->Count;
		cout.width(13);
		cout << "MP +30";
	}
	else if (this->GetName() == "��Ȳ����")
	{
		cout.width(15);
		cout << this->GetName();
		cout.width(8);
		cout << this->Count;
		cout.width(13);
		cout << "MP +70";
	}
	else if (this->GetName() == "��������")
	{
		cout.width(15);
		cout << this->GetName();
		cout.width(8);
		cout << this->Count;
		cout.width(13);
		cout << "MP +80";
	}
}

int Potion::IsEquipment()
{
	return 0;
}