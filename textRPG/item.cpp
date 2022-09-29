#include "main.h"


extern Character My_Character;


//=====================================================
// Item Class ����
//=====================================================
Item::Item() : name("NONAME"), price(0), isWearing(false) {}
Item::Item(string name, int price) : name(name), price(price), isWearing(false) {}
Item::~Item()
{
	//setcolor(BLACK, WHITE);	// ���� ����׿� // �׽�Ʈ
	//gotoxy(48, 59); cout << "~Item ����";
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
int Item::GetCount()
{
	return 1;
}
void Item::SetCount(int count)
{

}

int Item::GetIsUse()
{
	return 0;		// ���࿡ ���ؼ� ������� �ƴϴϱ� �׻� 0, 
}
void Item::SetIsUse(int isuse)
{

}

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
Equipment::Equipment() :hp(0), mp(0), att(0), count(1){ isWearing = 0; }
Equipment::Equipment(string Name, int Price, int Att)	// �����
	: Item(Name, Price), att(Att), count(1), hp(0), mp(0) {isWearing = 0;}

Equipment::~Equipment()
{
	//gotoxy(48, 57); cout << "~Equipment ����";
}

//virtual
int Equipment::GetCount()
{
	return this->count;
}
void Equipment::SetCount(int count)
{
	this->count = count;
}

int Equipment::GetIsUse()
{
	return isWearing;
}
void Equipment::SetIsUse(int isuse)
{
	this->isWearing = isuse;
}

void Equipment::UseItem()
{
	My_Character.SetAddAtt(this->att);
}
void Equipment::ShowInfo()
{
	if (this->GetName() == "�ʽ����� ���")
	{
		cout.width(15);
		cout << this->GetName();
		if (isWearing) { cout << "(����)";	cout.width(2); }
		else cout.width(8);
		cout << this->count;
		cout.width(13);
		cout << "���ݷ� +10";
	}
	else if (this->GetName() == "�ʽ����� ��â")
	{
		cout.width(15);
		cout << this->GetName();
		if (isWearing) { cout << "(����)";	cout.width(2); }
		else cout.width(8);
		cout << this->count;
		cout.width(13);
		cout << "���ݷ� +20";
	}
	else if (this->GetName() == "�߱����� ���")
	{
		cout.width(15);
		cout << this->GetName();
		if (isWearing) { cout << "(����)";	cout.width(2); }
		else cout.width(8);
		cout << this->count;
		cout.width(13);
		cout << "���ݷ� +40";
	}
	else if (this->GetName() == "�߱����� ��â")
	{
		cout.width(15);
		cout << this->GetName();
		if (isWearing) { cout << "(����)";	cout.width(2); }
		else cout.width(8);
		cout << this->count;
		cout.width(13);
		cout << "���ݷ� +55";
	}
}
int Equipment::GetItemType()	// [1] - ��� ������, [0] - �Һ������ 
{
	return static_cast<int> (ItemType::Equipment);
}



//=====================================================
// Potion Class ����
//=====================================================
Potion::Potion() :count(0), hp(0), mp(0) {}
Potion::Potion(string Name, int Hp, int Mp, int Price, int Count)
	: Item(Name, Price), count(Count), hp(Hp), mp(Mp) {}
Potion::~Potion()
{
	//gotoxy(48, 60); cout << "~Potion ����";
}


int Potion::GetCount()
{
	return this->count;
}

void Potion::SetCount(int count)
{
	this->count = count;
}
//virtual
//int Potion::GetIsUse()
//{
//	return 0;
//}
//void Potion::SetIsUse(int isuse)
//{
//
//}


void Potion::UseItem()
{
	SetCount(GetCount() - 1);	// 1�����̱� (������ �������� 1�� ���̱�)

	// HP ȸ��
	if ((My_Character.GetCurrentHP() + this->hp) > My_Character.GetMaxHP()) // HPȸ�������� MaxMP���� Ŭ��
	{
		My_Character.SetCurrentHP(My_Character.GetMaxHP());
	}
	else	// HPȸ�������� Max���� ������
	{
		My_Character.SetCurrentHP(My_Character.GetCurrentHP() + this->hp);
	}

	// MP ȸ��
	if (My_Character.GetCurrentMP() + this->mp > My_Character.GetMaxMP()) // MPȸ�������� MaxMP���� Ŭ��
	{
		My_Character.SetCurrentMP(My_Character.GetMaxMP());
	}
	else	// MPȸ�������� Max���� ������
	{
		My_Character.SetCurrentMP(My_Character.GetCurrentMP() + this->mp);
	}

}
void Potion::ShowInfo()
{
	if (this->GetName() == "��������")
	{
		cout.width(15);
		cout << this->GetName();
		cout.width(8);
		cout << this->count;
		cout.width(13);
		cout << "HP +30";
	}
	else if (this->GetName() == "�Ķ�����")
	{
		cout.width(15);
		cout << this->GetName();
		cout.width(8);
		cout << this->count;
		cout.width(13);
		cout << "MP +30";
	}
	else if (this->GetName() == "��Ȳ����")
	{
		cout.width(15);
		cout << this->GetName();
		cout.width(8);
		cout << this->count;
		cout.width(13);
		cout << "MP +70";
	}
	else if (this->GetName() == "��������")
	{
		cout.width(15);
		cout << this->GetName();
		cout.width(8);
		cout << this->count;
		cout.width(13);
		cout << "MP +80";
	}
}

int Potion::GetItemType()
{
	return static_cast<int> (ItemType::Potion);
}