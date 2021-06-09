#pragma once
#include <QGraphicsRectItem>
#include "Ball.h"

enum Directions {
	D_RIGHT,
	D_UP,
	D_LEFT,
	D_DOWN,
	D_NO
};

//����� �������� ��� ������. ����� ������ ��� ������ � �������.
class Obstacle : public QGraphicsRectItem {
public:
	Obstacle(double x, double y, double w, double h) : QGraphicsRectItem(x, y, w, h) { width_ = w; height_ = h; }
	Directions impactOnBall(const Ball&) const; //�����, ������������, � ����� ������� ������ �������� ���������� �����
	double getWidth() const;
	double getHeight() const;
	void setSize(double, double);
	bool isPointInto(double, double) const; //�����, ������������, ��������� �� ����� ������ ������ ��������
private:
	double width_;
	double height_;
};