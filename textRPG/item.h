#pragma once

enum charactor_class{ NO_CLASS, WARRIOR, ARCHER, WIZARD};

class Item abstract
{
private:
	string name;
	int price;

public:
	Item();
	Item(string, int);
	virtual ~Item();

	void SetName(const string& name);
	void SetPrice(int);

	string GetName() const;
	int GetPrice() const;

	// virtual
	virtual int GetIsUse() abstract;
	virtual int GetCount() abstract;
	
	virtual void SetIsUse(const int isuse) abstract;
	virtual void SetCount(const int count) abstract;
	
	virtual void UseItem() abstract;
	virtual void ShowInfo() abstract;
	virtual int IsEquipment() abstract;
};

class Equipment final : public Item
{
private:
	int HP;
	int MP;
	int Att;
	int Def;
	bool IsUse;
	int Count;

public:
	Equipment();
	Equipment(string Name, int Price, int Att); // 무기용
	Equipment(string Name, int Price, int Hp, int Mp, int Def); // 방어구용
	virtual ~Equipment() override;

	// virtual
	int GetIsUse() override;
	int GetCount() override;

	void SetIsUse(const int isuse) override;
	void SetCount(const int count) override;

	void UseItem() override;
	void ShowInfo() override;
	int IsEquipment() override;
};

class Potion final : public Item
{
private:
	int Count;
	int HP;
	int MP;
public:
	Potion();
	Potion(string Name, int Hp, int Mp, int Price, int Count);
	virtual ~Potion() override;

	// virtual
	int GetCount() override;
	int GetIsUse() override;

	void SetCount(const int count) override;
	void SetIsUse(const int isuse) override;

	void UseItem() override;
	void ShowInfo() override;
	int IsEquipment() override;
};
