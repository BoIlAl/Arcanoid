#include "Bonus.h"

AbstractBonus::AbstractBonus(double x, double y, double size, double speed) : QGraphicsRectItem(x, y, size, size) {
	dY_ = speed;
	size_ = size;
}

bool AbstractBonus::isTouch�arriage(const Carriage& �arriage) const {
	if (�arriage.isPointInto(this->x(), this->y()) || �arriage.isPointInto(this->x() + size_, this->y())
		|| �arriage.isPointInto(this->x(), this->y() + size_) || �arriage.isPointInto(this->x() + size_, this->y() + size_)) {
		return true;
	}
	else {
		return false;
	}
}


double AbstractBonus::getSpeed() const {
	return dY_;
}

double AbstractBonus::getSize() const {
	return size_;
}

bool AbstractBonus::isFalling() const {
	return flagFall_;
}

void AbstractBonus::startFall() {
	flagFall_ = true;
}

CarriageSizeBonus::CarriageSizeBonus(double x, double y, double size, double speed, Carriage* �arriage, double sizeMultiplier) : AbstractBonus(x, y, size, speed){
	sizeMultiplier_ = sizeMultiplier;
	�arriage_ = �arriage;
}

void CarriageSizeBonus::bonusActivate() const {
	int temp = (�arriage_->getWidth() * sizeMultiplier_ - �arriage_->getWidth()) / 2;
	�arriage_->setPos(�arriage_->x() - temp, �arriage_->y());
	�arriage_->setSizeSave(�arriage_->getWidth() * sizeMultiplier_, �arriage_->getHeight());
}

BallSpeedBonus::BallSpeedBonus(double x, double y, double size, double speed, Ball* ball, double speedMultiplier) : AbstractBonus(x, y, size, speed) {
	ball_ = ball;
	speedMultiplier_ = speedMultiplier;
}

void BallSpeedBonus::bonusActivate() const {
	ball_->setSpeed(ball_->getDX() * speedMultiplier_, ball_->getDY() * speedMultiplier_);
}

StickyBonus::StickyBonus(double x, double y, double size, double speed, int* stickingCounter, int numOfSticking) : AbstractBonus(x, y, size, speed) {
	stickingCounter_ = stickingCounter;
	numOfSticking_ = numOfSticking;
}

void StickyBonus::bonusActivate() const {
	*stickingCounter_ = numOfSticking_;
}

BottomObstacleBonus::BottomObstacleBonus(double x, double y, double size, double speed, bool * bottomObstacleFlag) : AbstractBonus(x, y, size, speed) {
	bottomObstacleFlag_ = bottomObstacleFlag;
}

void BottomObstacleBonus::bonusActivate() const {
	*bottomObstacleFlag_ = true;
}

RandomTrajectoryBonus::RandomTrajectoryBonus(double x, double y, double size, double speed, Ball * ball) : AbstractBonus(x, y, size, speed) {
	ball_ = ball;
}

void RandomTrajectoryBonus::bonusActivate() const {
	double speed = std::sqrt(ball_->getDX() * ball_->getDX() + ball_->getDY() * ball_->getDY());

	double newDY = static_cast<double>(rand()) * speed * (maxValue - minValue) / RAND_MAX + minValue * speed;

	if (static_cast<double>(rand()) / RAND_MAX < 0.5) {
		newDY *= -1;
	} 

	double newDX = std::sqrt(speed * speed - newDY * newDY);

	if (static_cast<double>(rand()) / RAND_MAX < 0.5) {
		newDX *= -1;
	}
	ball_->setSpeed(newDX, newDY);
}

MovingBlockBonus::MovingBlockBonus(double x, double y, double size, double speed, bool * movingBlockFlag) : AbstractBonus(x, y, size, speed) {
	movingBlockFlag_ = movingBlockFlag;
}

void MovingBlockBonus::bonusActivate() const {
	*movingBlockFlag_ = true;
}
