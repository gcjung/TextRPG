#pragma once

enum class ItemType {Equipment, Potion};

class Item abstract
{
protected:
	string name;
	int price;
	bool isWearing;

public:
	Item();
	Item(string, int);
	virtual ~Item();

	void SetName(const string& name);
	void SetPrice(int);

	string GetName() const;
	int GetPrice() const;

	virtual int GetIsUse();
	virtual int GetCount() abstract;
	
	virtual void SetIsUse(const int isuse);
	virtual void SetCount(const int count) abstract;
	
	virtual void UseItem() abstract;
	virtual void ShowInfo() abstract;
	virtual int GetItemType() abstract;
};

class Equipment final : public Item
{
private:
	int hp;
	int mp;
	int att;
	int count;

public:
	Equipment();
	Equipment(string Name, int Price, int Att); // ¹«±â¿ë

	virtual ~Equipment() override;

	// virtual
	int GetIsUse() override;
	int GetCount() override;

	void SetIsUse(const int isuse) override;
	void SetCount(const int count) override;

	void UseItem() override;
	void ShowInfo() override;
	int GetItemType() override;
};

class Potion final : public Item
{
private:
	int count;
	int hp;
	int mp;
public:
	Potion();
	Potion(string Name, int Hp, int Mp, int Price, int Count);
	virtual ~Potion() override;

	int GetCount() override;
	void SetCount(const int count) override;

	void UseItem() override;
	void ShowInfo() override;
	int GetItemType() override;
};
