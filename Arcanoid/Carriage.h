#pragma once
#include "Obstacle.h"

class Carriage : public Obstacle {
public:
	Carriage(double x, double y, double w, double h, double speed, double maxWidth); //Конструктор принимает координаты, размеры, скорость и максимальную ширину каретки
	void move(bool); //Метод движения каретки указанное направление (true - влево, false - вправо)
	double getSpeed() const;
	void setSizeSave(double, double); //Метод, меняющий размеры каретки с учетом максимальной ширины
	bool isBallOnTop(const Ball* ball) const; //Метод, проверяющий находится ли шарик сверху на каретке
private:
	double maxWidth_;
	double speed_;
};