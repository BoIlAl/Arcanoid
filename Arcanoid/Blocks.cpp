#include "Blocks.h"

void AbstractBlock::showType() {
	this->setPen(getPen());
}


std::tuple<InteractionOutcomes, Directions, short> SimpleBlock::collisionReact(Ball& ball)  {
	std::tuple<InteractionOutcomes, Directions, short> tuple = { B_NOTHING, D_NO, 0 };
	std::get<1>(tuple) = impactOnBall(ball);
	if (std::get<1>(tuple) != D_NO) {
		std::get<0>(tuple) = B_DESTROYED;
		std::get<2>(tuple) = destrPoints;
	}
	return tuple;
}

QPen SimpleBlock::getPen() const {
	QPen pen;
	pen.setColor(QColor(Qt::green));
	return pen;
}

std::tuple<InteractionOutcomes, Directions, short> IndestructibleBlock::collisionReact(Ball& ball)  {
	std::tuple<InteractionOutcomes, Directions, short> tuple = { B_NOTHING, D_NO, 0 };
	std::get<1>(tuple) = impactOnBall(ball);
	if (std::get<1>(tuple) != D_NO) {
		std::get<0>(tuple) = B_NOTDESTROYED;
		std::get<2>(tuple) = hitPoints;
	}
	return tuple;
}

QPen IndestructibleBlock::getPen() const {
	QPen pen;
	pen.setColor(QColor(Qt::black));
	return pen;
}

std::tuple<InteractionOutcomes, Directions, short> StrongBlock::collisionReact(Ball& ball)  {
	std::tuple<InteractionOutcomes, Directions, short> tuple = { B_NOTHING, D_NO, 0 };
	std::get<1>(tuple) = impactOnBall(ball);
	if (std::get<1>(tuple) != D_NO) {
		--health_;
		if (health_ == 0) {
			std::get<0>(tuple) = B_DESTROYED;
			std::get<2>(tuple) = destrPoints;
		}
		else {
			std::get<0>(tuple) = B_NOTDESTROYED;
			std::get<2>(tuple) = hitPoints;
		}
	}
	return tuple;
}

QPen StrongBlock::getPen() const {
	QPen pen;
	pen.setColor(QColor(Qt::blue));
	return pen;
}


std::tuple<InteractionOutcomes, Directions, short> SpringyBlock::collisionReact(Ball& ball) {
	std::tuple<InteractionOutcomes, Directions, short> tuple = { B_NOTHING, D_NO, 0 };
	std::get<1>(tuple) = impactOnBall(ball);
	if (std::get<1>(tuple) != D_NO) {
		ball.setSpeed(ball.getDX() * speedMultiplier_, ball.getDY() * speedMultiplier_);
		std::get<0>(tuple) = B_DESTROYED;
		std::get<2>(tuple) = destrPoints;
	}
	return tuple;
}

QPen SpringyBlock::getPen() const {
	QPen pen;
	pen.setColor(QColor(Qt::magenta));
	return pen;
}

std::tuple<InteractionOutcomes, Directions, short> BonusBlock::collisionReact(Ball& ball) {
	std::tuple<InteractionOutcomes, Directions, short> tuple = { B_NOTHING, D_NO, 0 };
	std::get<1>(tuple) = impactOnBall(ball);
	if (std::get<1>(tuple) != D_NO) {
		std::get<0>(tuple) = B_DESTROYED;
		std::get<2>(tuple) = destrPoints;
		bonus_->startFall();
	}
	return tuple;
}

QPen BonusBlock::getPen() const {
	QPen pen;
	pen.setColor(QColor(Qt::red));
	return pen;
}

MovingBlock::MovingBlock(double x, double y, double w, double h, unsigned int health, double speed, Directions startDir) : StrongBlock(x, y, w, h, health) { 
	speed_ = speed; dir_ = startDir;
}

std::tuple<InteractionOutcomes, Directions, short> MovingBlock::collisionReact(Ball& ball) {
	std::tuple<InteractionOutcomes, Directions, short> tuple = { B_NOTHING, D_NO, 0 };
	std::get<1>(tuple) = impactOnBall(ball);
	if (std::get<1>(tuple) != D_NO) {
		--health_;
		if (health_ == 0) {
			std::get<0>(tuple) = B_DESTROYED;
			std::get<2>(tuple) = destrPoints;
		}
		else {
			std::get<0>(tuple) = B_NOTDESTROYED;
			std::get<2>(tuple) = hitPoints;
		}
	}
	return tuple;
}

void MovingBlock::setDirection(Directions dir) {
	dir_ = dir;
}

Directions MovingBlock::getDirection() const {
	return dir_;
}

void MovingBlock::move() {
	switch (dir_) {
	case D_DOWN:
		this->setPos(this->x(), this->y() + speed_);
		break;
	case D_UP:
		this->setPos(this->x(), this->y() - speed_);
		break;
	case D_RIGHT:
		this->setPos(this->x() + speed_, this->y());
		break;
	case D_LEFT:
		this->setPos(this->x() - speed_, this->y());
		break;
	}
}

QPen MovingBlock::getPen() const {
	QPen pen;
	pen.setColor(QColor(Qt::blue));
	return pen;
}
