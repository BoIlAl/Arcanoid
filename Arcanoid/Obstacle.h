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

// ласс преграды дл€ шарика. ќбщий предок дл€ блоков и каретки.
class Obstacle : public QGraphicsRectItem {
public:
	Obstacle(double x, double y, double w, double h) : QGraphicsRectItem(x, y, w, h) { width_ = w; height_ = h; }
	Directions impactOnBall(const Ball&) const; //ћетод, определ€ющий, в какую сторону данна€ преграда оттолкнула шарик
	double getWidth() const;
	double getHeight() const;
	void setSize(double, double);
	bool isPointInto(double, double) const; //ћетод, определ€ющий, находитс€ ли точка внетри данной преграды
private:
	double width_;
	double height_;
};