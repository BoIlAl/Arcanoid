#pragma once

#include <QGraphicsEllipseItem>

class Ball : public QGraphicsEllipseItem {
public:
	Ball(double x, double y, double diametr, double maxSpeed); //����������� ��������� ���������� ������, ��� ������ � ������������ ��������

	void setSpeed(double, double);
	double getDX() const;
	double getDY() const;
	double getSize() const;
private:
	double maxSpeed_;
	double size_;

	//����������-���������� ������� ��������
	double dX_;
	double dY_;

};
