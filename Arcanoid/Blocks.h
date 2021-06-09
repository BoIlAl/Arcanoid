#pragma once
#include <QPen>
#include "Bonus.h"
#include "Obstacle.h"

enum InteractionOutcomes {
	B_NOTHING,
	B_NOTDESTROYED,
	B_DESTROYED
};

class AbstractBlock : public Obstacle {
public:
	AbstractBlock(double x, double y, double w, double h) : Obstacle(x, y, w, h) {}
	void showType(); //����� ��������������� ���� � ��������������� ��� ����
	virtual std::tuple<InteractionOutcomes, Directions, short> collisionReact(Ball&) = 0; //�����, �������������� ������������ ����� � �������. 
																																												//��������� ��������� ������������, ����������� ��� ������, ���������� ����� �� �������
protected:
	virtual QPen getPen() const = 0; //�����, ������������ ���� �����
};

//��� ���������� ������ ������������ ���������� ���������� "destrPoints" � "hitPoints", ������������ ���-�� ����� �� ���������� ����� � ��������� �� ���� ������������� 
//� ������������� ����� ��������� ��������������� �� ���� ��������������

//������� ����
class SimpleBlock : public AbstractBlock {
public:
	SimpleBlock(double x, double y, double w, double h) : AbstractBlock(x, y, w, h) {};
	virtual std::tuple<InteractionOutcomes, Directions, short> collisionReact(Ball&);
private:
	virtual QPen getPen() const;
	const short destrPoints = 1;
};

//���� �� ���������
class StrongBlock : public AbstractBlock {
public:
	StrongBlock(double x, double y, double w, double h, unsigned int health) : AbstractBlock(x, y, w, h) { health_ = health; }
	virtual std::tuple<InteractionOutcomes, Directions, short> collisionReact(Ball&);
protected:
	unsigned int health_ = 1;
private:
	virtual QPen getPen() const;
	const short destrPoints = 2;
	const short hitPoints = 1;
};

//������������ ����
class IndestructibleBlock : public AbstractBlock {
public:
	IndestructibleBlock(double x, double y, double w, double h) : AbstractBlock(x, y, w, h) {}
	virtual std::tuple<InteractionOutcomes, Directions, short> collisionReact(Ball&);
private:
	virtual QPen getPen() const;
	const short hitPoints = 0;
};

//������� ����
class SpringyBlock : public AbstractBlock {
public:
	SpringyBlock(double x, double y, double w, double h, double multiplier) : AbstractBlock(x, y, w, h) { speedMultiplier_ = multiplier; }
	virtual std::tuple<InteractionOutcomes, Directions, short> collisionReact(Ball&);
private:
	virtual QPen getPen() const;
	double speedMultiplier_ = 1;
	const short destrPoints = 2;
};

//���� � �������
class BonusBlock : public AbstractBlock {
public:
	BonusBlock(double x, double y, double w, double h, AbstractBonus* bonus) : AbstractBlock(x, y, w, h) { bonus_ = bonus; }
	virtual std::tuple<InteractionOutcomes, Directions, short> collisionReact(Ball&);
private:
	virtual QPen getPen() const;
	const short destrPoints = 1;
	AbstractBonus* bonus_;
};

//���������� ����
class MovingBlock : public StrongBlock {
public:
	MovingBlock(double x, double y, double w, double h, unsigned int health, double speed, Directions startDir);
	virtual std::tuple<InteractionOutcomes, Directions, short> collisionReact(Ball&);
	void setDirection(Directions); 
	Directions getDirection() const;
	void move();
private:
	virtual QPen getPen() const;
	double speed_;
	Directions dir_; //���������� ����������� �������� ������
	const short destrPoints = 3;
	const short hitPoints = 1;
};