#include "Obstacle.h"

Directions Obstacle::impactOnBall(const Ball& ball) const {

	bool flag1 = isPointInto(ball.x(), ball.y());
	bool flag2 = isPointInto(ball.x() + ball.getSize(), ball.y());
	bool flag3 = isPointInto(ball.x(), ball.y() + ball.getSize());
	bool flag4 = isPointInto(ball.x() + ball.getSize(), ball.y() + ball.getSize());

	if (flag1 && flag2) {
		return D_DOWN;
	} else if (flag1 && flag3) {
		return D_RIGHT;
	} else if (flag2 && flag4) {
		return D_LEFT;
	} else if (flag3 && flag4) {
		return D_UP;
	} else if (flag1) {
		if (this->getWidth() - (ball.x() - this->x()) < this->getHeight() - (ball.y() - this->y())) {
			return D_RIGHT;
		}
		else {
			return D_DOWN;
		}
	} else if (flag2) {
		if (ball.x() + ball.getSize() - this->x() < this->getHeight() - (ball.y() - this->y())) {
			return D_LEFT;
		}
		else {
			return D_DOWN;
		}
	} else if (flag3) {
		if (this->getWidth() - (ball.x() - this->x()) < ball.y() + ball.getSize() - this->y()) {
			return D_RIGHT;
		}
		else {
			return D_UP;
		}
	} else if (flag4) {
		if (ball.x() + ball.getSize() - this->x() < ball.y() + ball.getSize() - this->y()) {
			return D_LEFT;
		}
		else {
			return D_UP;
		}
	}
	return D_NO;
}

double Obstacle::getWidth() const {
	return width_;
}

double Obstacle::getHeight() const {
	return height_;
}

void Obstacle::setSize(double newWidth, double newHeight){
	this->setRect(0, 0, newWidth, newHeight);
	this->setPos(this->x(), this->y());
	width_ = newWidth;
	height_ = newHeight;
}

bool Obstacle::isPointInto(double x, double y) const {
	if (x >= this->x() && x <= this->x() + getWidth() && y >= this->y() && y <= this->y() + getHeight()) {
		return true;
	}
	return false;
}
