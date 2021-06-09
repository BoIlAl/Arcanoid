#include "Carriage.h"

Carriage::Carriage(double x, double y, double w, double h, double speed, double maxWidth) : Obstacle(x, y, w, h) {
	speed_ = speed;
	maxWidth_ = maxWidth;
}

void Carriage::move(bool side) {
	if (side) {
		this->setPos(this->x() - this->speed_, this->y());
	}
	else {
		this->setPos(this->x() + this->speed_, this->y());
	}
}

double Carriage::getSpeed() const {
	return speed_;
}

void Carriage::setSizeSave(double newWidth, double newHeight) {
	if (newWidth > maxWidth_) {
		this->setSize(maxWidth_, newHeight);
	}
	else {
		this->setSize(newWidth, newHeight);
	}
}

bool Carriage::isBallOnTop(const Ball* ball) const {
	bool flag1 = isPointInto(ball->x(), ball->y());
	bool flag2 = isPointInto(ball->x() + ball->getSize(), ball->y());
	bool flag3 = isPointInto(ball->x(), ball->y() + ball->getSize());
	bool flag4 = isPointInto(ball->x() + ball->getSize(), ball->y() + ball->getSize());
	if (!flag1 && !flag2 && (flag3 || flag4)){
		return true;
	}
	return false;
}


