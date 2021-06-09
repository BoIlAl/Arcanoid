#include "Ball.h"

Ball::Ball(double x, double y, double diametr, double maxSpeed) : QGraphicsEllipseItem(x, y, diametr, diametr) {
	size_ = diametr; 
	maxSpeed_ = maxSpeed;
}

void Ball::setSpeed(double dX, double dY)  {
	if (std::sqrt(dX * dX + dY * dY) > maxSpeed_) {
		return;
	}
	dX_ = dX;
	dY_ = dY;
}

double Ball::getDX() const {
	return dX_;
}

double Ball::getDY() const {
	return dY_;
}

double Ball::getSize() const {
	return size_;
}
