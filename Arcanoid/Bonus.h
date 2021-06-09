#pragma once
#include "Carriage.h"


class AbstractBonus : public QGraphicsRectItem {
public:
	AbstractBonus(double, double, double, double); //Конструктор принимает координаты блока, его размер и скорость
	bool isTouchСarriage(const Carriage&) const;
	double getSpeed() const;
	double getSize() const;
	bool isFalling() const; //Возвращает статус бонуса
	void startFall(); //Изменяет статус бонуса с "неактивен" на "падает"
	virtual void bonusActivate() const = 0; //Метод, активации бонуса
private:
	bool flagFall_ = false; //Состояние (true - падает, false - неактивен)
	double dY_; //Скорость
	double size_;
};

//Каждому бонусу в конструктор передается элемент управления и (для некоторых) параметр, 
//за счет которых бонус реализуется/подает сигнал в MyPhysics об изменениях в bonusActivate

//Бонус изменения размера каретки
class CarriageSizeBonus : public AbstractBonus {
public:
	CarriageSizeBonus(double x, double y, double size, double speed, Carriage* сarriage, double sizeMultiplier);
	virtual void bonusActivate() const;
private:
	double sizeMultiplier_;
	Carriage* сarriage_;
};

//Бонус изменения скорости шарика
class BallSpeedBonus : public AbstractBonus {
public:
	BallSpeedBonus(double x, double y, double size, double speed, Ball* ball, double speedMultiplier);
	virtual void bonusActivate() const;
private:
	double speedMultiplier_;
	Ball* ball_;
};

//Бонус прилипания шарика к каретке
class StickyBonus : public AbstractBonus {
public:
	StickyBonus(double x, double y, double size, double speed, int* stickingCounter, int numOfSticking);
	virtual void bonusActivate() const;
private:
	int numOfSticking_;
	int* stickingCounter_;
};

//Бонус одноразового дна
class BottomObstacleBonus : public AbstractBonus {
public:
	BottomObstacleBonus(double x, double y, double size, double speed, bool* bottomObstacleFlag);
	virtual void bonusActivate() const;
private:
	bool* bottomObstacleFlag_;
};

//Бонус случайным образом меняющий траекторию шарика
class RandomTrajectoryBonus : public AbstractBonus {
public:
	RandomTrajectoryBonus(double x, double y, double size, double speed, Ball* ball);
	virtual void bonusActivate() const;
private:
	//Данные определяющий максимальное отклонение вектора скорости шарика от горизонтали и вертикали
	const double maxValue = std::cos(std::acos(-1.0) / 12);
	const double minValue = std::cos(std::acos(-1.0) / 12 * 5);
	Ball* ball_;
};

//Бонус, создающий движущийся блок
class MovingBlockBonus : public AbstractBonus {
public:
	MovingBlockBonus(double x, double y, double size, double speed, bool* movingBlockFlag);
	virtual void bonusActivate() const;
private:
	bool* movingBlockFlag_;
};
