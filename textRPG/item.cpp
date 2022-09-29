#include "main.h"


extern Character My_Character;


//=====================================================
// Item Class 정의
//=====================================================
Item::Item() : name("NONAME"), price(0), isWearing(false) {}
Item::Item(string name, int price) : name(name), price(price), isWearing(false) {}
Item::~Item()
{
	//setcolor(BLACK, WHITE);	// 상점 디버그용 // 테스트
	//gotoxy(48, 59); cout << "~Item 해제";
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
	return 0;		// 물약에 대해선 장착장비가 아니니깐 항상 0, 
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
// Equipment Class 정의
//=====================================================
Equipment::Equipment() :hp(0), mp(0), att(0), count(1){ isWearing = 0; }
Equipment::Equipment(string Name, int Price, int Att)	// 무기용
	: Item(Name, Price), att(Att), count(1), hp(0), mp(0) {isWearing = 0;}

Equipment::~Equipment()
{
	//gotoxy(48, 57); cout << "~Equipment 해제";
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
	if (this->GetName() == "초심자의 대검")
	{
		cout.width(15);
		cout << this->GetName();
		if (isWearing) { cout << "(장착)";	cout.width(2); }
		else cout.width(8);
		cout << this->count;
		cout.width(13);
		cout << "공격력 +10";
	}
	else if (this->GetName() == "초심자의 죽창")
	{
		cout.width(15);
		cout << this->GetName();
		if (isWearing) { cout << "(장착)";	cout.width(2); }
		else cout.width(8);
		cout << this->count;
		cout.width(13);
		cout << "공격력 +20";
	}
	else if (this->GetName() == "중급자의 대검")
	{
		cout.width(15);
		cout << this->GetName();
		if (isWearing) { cout << "(장착)";	cout.width(2); }
		else cout.width(8);
		cout << this->count;
		cout.width(13);
		cout << "공격력 +40";
	}
	else if (this->GetName() == "중급자의 죽창")
	{
		cout.width(15);
		cout << this->GetName();
		if (isWearing) { cout << "(장착)";	cout.width(2); }
		else cout.width(8);
		cout << this->count;
		cout.width(13);
		cout << "공격력 +55";
	}
}
int Equipment::GetItemType()	// [1] - 장비 아이템, [0] - 소비아이템 
{
	return static_cast<int> (ItemType::Equipment);
}



//=====================================================
// Potion Class 정의
//=====================================================
Potion::Potion() :count(0), hp(0), mp(0) {}
Potion::Potion(string Name, int Hp, int Mp, int Price, int Count)
	: Item(Name, Price), count(Count), hp(Hp), mp(Mp) {}
Potion::~Potion()
{
	//gotoxy(48, 60); cout << "~Potion 해제";
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
	SetCount(GetCount() - 1);	// 1개줄이기 (개수가 여러개면 1개 줄이기)

	// HP 회복
	if ((My_Character.GetCurrentHP() + this->hp) > My_Character.GetMaxHP()) // HP회복했을때 MaxMP보다 클때
	{
		My_Character.SetCurrentHP(My_Character.GetMaxHP());
	}
	else	// HP회복했을때 Max보다 작을때
	{
		My_Character.SetCurrentHP(My_Character.GetCurrentHP() + this->hp);
	}

	// MP 회복
	if (My_Character.GetCurrentMP() + this->mp > My_Character.GetMaxMP()) // MP회복했을때 MaxMP보다 클때
	{
		My_Character.SetCurrentMP(My_Character.GetMaxMP());
	}
	else	// MP회복했을때 Max보다 작을때
	{
		My_Character.SetCurrentMP(My_Character.GetCurrentMP() + this->mp);
	}

}
void Potion::ShowInfo()
{
	if (this->GetName() == "빨간포션")
	{
		cout.width(15);
		cout << this->GetName();
		cout.width(8);
		cout << this->count;
		cout.width(13);
		cout << "HP +30";
	}
	else if (this->GetName() == "파란포션")
	{
		cout.width(15);
		cout << this->GetName();
		cout.width(8);
		cout << this->count;
		cout.width(13);
		cout << "MP +30";
	}
	else if (this->GetName() == "주황포션")
	{
		cout.width(15);
		cout << this->GetName();
		cout.width(8);
		cout << this->count;
		cout.width(13);
		cout << "MP +70";
	}
	else if (this->GetName() == "남색포션")
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