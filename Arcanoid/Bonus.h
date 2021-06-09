#pragma once
#include "Carriage.h"


class AbstractBonus : public QGraphicsRectItem {
public:
	AbstractBonus(double, double, double, double); //����������� ��������� ���������� �����, ��� ������ � ��������
	bool isTouch�arriage(const Carriage&) const;
	double getSpeed() const;
	double getSize() const;
	bool isFalling() const; //���������� ������ ������
	void startFall(); //�������� ������ ������ � "���������" �� "������"
	virtual void bonusActivate() const = 0; //�����, ��������� ������
private:
	bool flagFall_ = false; //��������� (true - ������, false - ���������)
	double dY_; //��������
	double size_;
};

//������� ������ � ����������� ���������� ������� ���������� � (��� ���������) ��������, 
//�� ���� ������� ����� �����������/������ ������ � MyPhysics �� ���������� � bonusActivate

//����� ��������� ������� �������
class CarriageSizeBonus : public AbstractBonus {
public:
	CarriageSizeBonus(double x, double y, double size, double speed, Carriage* �arriage, double sizeMultiplier);
	virtual void bonusActivate() const;
private:
	double sizeMultiplier_;
	Carriage* �arriage_;
};

//����� ��������� �������� ������
class BallSpeedBonus : public AbstractBonus {
public:
	BallSpeedBonus(double x, double y, double size, double speed, Ball* ball, double speedMultiplier);
	virtual void bonusActivate() const;
private:
	double speedMultiplier_;
	Ball* ball_;
};

//����� ���������� ������ � �������
class StickyBonus : public AbstractBonus {
public:
	StickyBonus(double x, double y, double size, double speed, int* stickingCounter, int numOfSticking);
	virtual void bonusActivate() const;
private:
	int numOfSticking_;
	int* stickingCounter_;
};

//����� ������������ ���
class BottomObstacleBonus : public AbstractBonus {
public:
	BottomObstacleBonus(double x, double y, double size, double speed, bool* bottomObstacleFlag);
	virtual void bonusActivate() const;
private:
	bool* bottomObstacleFlag_;
};

//����� ��������� ������� �������� ���������� ������
class RandomTrajectoryBonus : public AbstractBonus {
public:
	RandomTrajectoryBonus(double x, double y, double size, double speed, Ball* ball);
	virtual void bonusActivate() const;
private:
	//������ ������������ ������������ ���������� ������� �������� ������ �� ����������� � ���������
	const double maxValue = std::cos(std::acos(-1.0) / 12);
	const double minValue = std::cos(std::acos(-1.0) / 12 * 5);
	Ball* ball_;
};

//�����, ��������� ���������� ����
class MovingBlockBonus : public AbstractBonus {
public:
	MovingBlockBonus(double x, double y, double size, double speed, bool* movingBlockFlag);
	virtual void bonusActivate() const;
private:
	bool* movingBlockFlag_;
};
