#pragma once




class Unit abstract
{
public:
	struct Position
	{
		int x;
		int y;
		Position();
		void Move(int x, int y, int* stage, int* infoWindowType);
	};
	Position pos;

	Unit();
	Unit(string name, int level, int maxhp, int att, int gold);

	// getter
	string GetName() const;
	int GetLV() const;
	int GetMaxHP() const;
	int GetCurrentHP() const;
	int GetAtt() const;
	int GetDef() const;
	int GetGold() const;
	int GetAddAtt() const;

	// setter
	void SetName(const string& name);
	void SetLV(const int level);
	void SetMaxHP(const int maxhp);
	void SetCurrentHP(const int hp);
	void SetAtt(const int att);
	void SetDef(const int def);
	void SetGold(const int gold);
	void SetAddAtt(const int addAtt);

	virtual void Dead() abstract;

private:
	string name;
	int level;
	int maxHP;
	int currentHP;
	int att;
	int def;
	int gold;
	int addAtt;
};

class Character final : public Unit
{
public:
	Inventory inventory;

	Character();
	Character(int characterClass, int maxExp, int currentExp, int maxMp, int currentMP);

	int GetClass() const;
	int GetMaxExp() const;
	int GetCurrentExp() const;
	int GetMaxMP() const;
	int GetCurrentMP() const;

	void SetClass(int characterClass);
	void SetMaxExp(int maxExp);
	void SetCurrentExp(int currentExp);
	void SetMaxMP(int maxMp);
	void SetCurrentMP(int currentMp);
	void SetResurrection();

	void Attack(Monster* monster);
	void Dead();			// ƒ≥∏Ø≈Õ ªÁ∏¡Ω√ Ω∫≈»√ ±‚»≠, µ∑ »Í∏Æ±‚ µÓµÓ

private:
	int characterClass;
	int maxExp;
	int currentExp;
	int maxMP;
	int currentMP;
};

class Monster final : public Unit
{
private:
	int exp;
public:
	Monster();
	Monster(string name, int level, int maxhp, int att, int exp, int gold);

	void SetMonster(string name, int level, int maxhp, int att, int exp, int gold);
	void ShowMonsterInfo() const;

	int GetExp() const;
	void SetExp(int exp);

	void Attack(Character* character, int dungeonStage);
	void Dead();
};

