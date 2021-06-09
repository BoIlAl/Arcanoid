#pragma once
#include "Obstacle.h"

class Carriage : public Obstacle {
public:
	Carriage(double x, double y, double w, double h, double speed, double maxWidth); //����������� ��������� ����������, �������, �������� � ������������ ������ �������
	void move(bool); //����� �������� ������� ��������� ����������� (true - �����, false - ������)
	double getSpeed() const;
	void setSizeSave(double, double); //�����, �������� ������� ������� � ������ ������������ ������
	bool isBallOnTop(const Ball* ball) const; //�����, ����������� ��������� �� ����� ������ �� �������
private:
	double maxWidth_;
	double speed_;
};