#include "ArcanoidPhysics.h"

void ArcanoidPhysics::setStartPosForAll() {
	ball_->setPos(ballXInit_, ballYInit_);
	ñarriage_->setPos((sceneSize_ - ñarriage_->getWidth()) / 2, ñarriageYInit_);
	changeScore(0);
	stickingCounter = 1;
	setGameStatus(false);
}

void ArcanoidPhysics::virtualfieldInit() {
	std::srand(unsigned(time(0)));
	int numOfBlockTypes = 5;
	int numOfBonusTypes = 6;
	double x = 0.0;
	double y = 0.0;
	int temp2;

	virtualField_ = new Virtualfield(sceneSize_ / (c_blocksSize + 2 * c_minVicinity), sceneSize_ / 2 / (c_blocksSize + 2 * c_minVicinity), 0, 0, sceneSize_, sceneSize_ / 2);
	for (int i = 0; i < sceneSize_ / (c_blocksSize + 2 * c_minVicinity) * sceneSize_ / 2 /  (c_blocksSize + 2 * c_minVicinity); ++i) {
		int temp1 = round((static_cast<double>(std::rand()) * (numOfBlockTypes - 1) / RAND_MAX));
		AbstractBlock* newBlock;
		switch (temp1) {
		case 0:
			newBlock = new SimpleBlock(0, 0, c_blocksSize, c_blocksSize);
			break;
		case 1:
			newBlock = new StrongBlock(0, 0, c_blocksSize, c_blocksSize, c_strongBlockHealth);
			break;
		case 2:
		  newBlock = new IndestructibleBlock(0, 0, c_blocksSize, c_blocksSize);
			break;
		case 3:
			temp2 = round((static_cast<double>(std::rand()) * (numOfBonusTypes - 1) / RAND_MAX));
			AbstractBonus* newBonus;
			switch (temp2) {
			case 1:
				newBonus = new BallSpeedBonus(0, 0, c_bonusSize, c_bonusSpeed, ball_, c_bonusSpeedMultiplier);
				break;
			case 2:
			  newBonus = new StickyBonus(0, 0, c_bonusSize, c_bonusSpeed, &stickingCounter, c_bonusNumOfSticking);
				break;
			case 3:
				newBonus = new BottomObstacleBonus(0, 0, c_bonusSize, c_bonusSpeed, &bottomObstacleFlag);
				break;
			case 4:
				newBonus = new RandomTrajectoryBonus(0, 0, c_bonusSize, c_bonusSpeed, ball_);
				break;
			case 5:
				newBonus = new MovingBlockBonus(0, 0, c_bonusSize, c_bonusSpeed, &movingBlockFlag);
				break;
			default:
				newBonus = new CarriageSizeBonus(0, 0, c_bonusSize, c_bonusSpeed, ñarriage_, c_bonusWidthMultiplier);
			}
			newBonus->setPos(x + c_minVicinity + (c_blocksSize - c_bonusSize) / 2, y + c_minVicinity + (c_blocksSize - c_bonusSize) / 2);
			bonuses_.push_back(newBonus);
			newBlock = new BonusBlock(0, 0, c_blocksSize, c_blocksSize, newBonus);
			break;
		default:
			newBlock = new SpringyBlock(0, 0, c_blocksSize, c_blocksSize, c_springyBlockMultiplier);
			break;
		}
		newBlock->setPos(x + c_minVicinity, y + c_minVicinity);
		newBlock->showType();
		scene_->addItem(newBlock);
		virtualField_->addBlock(newBlock);
		if ((i + 1) % (int)(sceneSize_ / (c_blocksSize + 2 * c_minVicinity)) == 0 && i != 0) {
			x = 0.0;
			y += c_blocksSize + 2 * c_minVicinity;
		}
		else {
			x += c_blocksSize + 2 * c_minVicinity;
		}
	}
}

void ArcanoidPhysics::defeatProcessing() {
	changeScore(c_defeatPoint);
	setStartPosForAll();
}

void ArcanoidPhysics::changeScore(int points) {
	score_ += points;
	delete scoreTextItem_;
	scoreTextItem_ = new QGraphicsTextItem(QString::number(score_));
	scene_->addItem(scoreTextItem_);
}

void ArcanoidPhysics::bottomObstacleCreate() {
	bottomObstacle_ = new SimpleBlock(0, 0, sceneSize_ + c_minVicinity, c_blocksSize + c_minVicinity);
	scene_->addItem(bottomObstacle_);
	bottomObstacle_->setPos(-c_minVicinity / 2, sceneSize_ - c_blocksSize);
	bottomObstacle_->showType();
}

void ArcanoidPhysics::movingBlockCreate() {
	std::pair<double, double> temp;
	MovingBlock* newBlock;
	temp = virtualField_->getRandomEmptyCoord();
	if (temp.first < 0) {
		return;
	}
	else {
		newBlock = new MovingBlock(0, 0, c_blocksSize, c_blocksSize, c_strongBlockHealth, c_blocksSpeed, D_UP);
		newBlock->setPos(temp.first + c_minVicinity, temp.second + c_minVicinity);
		newBlock->showType();
		scene_->addItem(newBlock);
		virtualField_->addBlock(newBlock);
		movingBlocks_.push_back(newBlock);
	}
}

void ArcanoidPhysics::moveMovingBlock(MovingBlock& block) {
	double eps = 1e-10, temp;
	double eps1 = c_blocksSpeed / (c_blocksSize + 2 * c_minVicinity) * 2;
	double x = block.x();
	double y = block.y();
	double temp1 = std::modf((block.x() - c_minVicinity) / (c_blocksSize + 2 * c_minVicinity), &temp);
	double temp2 = std::modf((block.y() - c_minVicinity) / (c_blocksSize + 2 * c_minVicinity), &temp);
	if ((std::modf((block.x() - c_minVicinity) / (c_blocksSize + 2 * c_minVicinity), &temp) < eps
			|| 1 - std::modf((block.x() - c_minVicinity) / (c_blocksSize + 2 * c_minVicinity), &temp) < eps)
			&& (std::modf((block.y() - c_minVicinity) / (c_blocksSize + 2 * c_minVicinity), &temp) < eps 
			|| 1 - std::modf((block.y() - c_minVicinity) / (c_blocksSize + 2 * c_minVicinity), &temp) < eps)) {
		if (block.getDirection() == D_LEFT) {
			if (block.y() + (c_blocksSize + c_minVicinity) < virtualField_->getFieldY() + virtualField_->getFieldHeigth() - 1
				&& !virtualField_->blockAt(block.x(), block.y() + (c_blocksSize + 2 * c_minVicinity))) {
				block.setDirection(D_DOWN);
			}
			else if (block.x() - (c_blocksSize + c_minVicinity) > virtualField_->getFieldX() && !virtualField_->blockAt(block.x() - (c_blocksSize + 2 * c_minVicinity), block.y())) {
				block.setDirection(D_LEFT);
			}
			else if (block.y() - (c_blocksSize + c_minVicinity) > virtualField_->getFieldY() && !virtualField_->blockAt(block.x(), block.y() - (c_blocksSize + 2 * c_minVicinity))) {
				block.setDirection(D_UP);
			}
			else if (block.x() + (c_blocksSize + c_minVicinity) < virtualField_->getFieldX() + virtualField_->getFieldWidth() - 1
				&& !virtualField_->blockAt(block.x() + (c_blocksSize + 2 * c_minVicinity), block.y())) {
				block.setDirection(D_RIGHT);
			}
		}
		else if (block.getDirection() == D_UP) {
			if (block.x() - (c_blocksSize + c_minVicinity) > virtualField_->getFieldX() && !virtualField_->blockAt(block.x() - (c_blocksSize + c_minVicinity), block.y())) {
				block.setDirection(D_LEFT);
			}
			else if (block.y() - (c_blocksSize + c_minVicinity) > virtualField_->getFieldY() && !virtualField_->blockAt(block.x(), block.y() - (c_blocksSize + c_minVicinity))) {
				block.setDirection(D_UP);
			}
			else if (block.x() + (c_blocksSize + c_minVicinity) < virtualField_->getFieldX() + virtualField_->getFieldWidth() - 1
				&& !virtualField_->blockAt(block.x() + (c_blocksSize + 2 * c_minVicinity), block.y())) {
				block.setDirection(D_RIGHT);
			}
			else if (block.y() + (c_blocksSize + c_minVicinity) < virtualField_->getFieldY() + virtualField_->getFieldHeigth() - 1
				&& !virtualField_->blockAt(block.x(), block.y() + (c_blocksSize + 2 * c_minVicinity))) {
				block.setDirection(D_DOWN);
			}
		}
		else if (block.getDirection() == D_RIGHT) {
			if (block.y() - (c_blocksSize + c_minVicinity) > virtualField_->getFieldY() && !virtualField_->blockAt(block.x(), block.y() - (c_blocksSize + c_minVicinity))) {
				block.setDirection(D_UP);
			}
			else if (block.x() + (c_blocksSize + c_minVicinity) < virtualField_->getFieldX() + virtualField_->getFieldWidth() - 1
				&& !virtualField_->blockAt(block.x() + (c_blocksSize + 2 * c_minVicinity), block.y())) {
				block.setDirection(D_RIGHT);
			}
			else if (block.y() + (c_blocksSize + c_minVicinity) < virtualField_->getFieldY() + virtualField_->getFieldHeigth() - 1
				&& !virtualField_->blockAt(block.x(), block.y() + (c_blocksSize + 2 * c_minVicinity))) {
				block.setDirection(D_DOWN);
			}
			else if (block.x() - (c_blocksSize + c_minVicinity) > virtualField_->getFieldX() && !virtualField_->blockAt(block.x() - (c_blocksSize + c_minVicinity), block.y())) {
				block.setDirection(D_LEFT);
			}
		}
		else if (block.getDirection() == D_DOWN) {
			if (block.x() + (c_blocksSize + c_minVicinity) < virtualField_->getFieldX() + virtualField_->getFieldWidth() - 1
				&& !virtualField_->blockAt(block.x() + (c_blocksSize + 2 * c_minVicinity), block.y())) {
				block.setDirection(D_RIGHT);
			}
			else if (block.y() + (c_blocksSize + c_minVicinity) < virtualField_->getFieldY() + virtualField_->getFieldHeigth() - 1
				&& !virtualField_->blockAt(block.x(), block.y() + (c_blocksSize + 2 * c_minVicinity))) {
				block.setDirection(D_DOWN);
			}
			else if (block.x() - (c_blocksSize + c_minVicinity) > virtualField_->getFieldX() && !virtualField_->blockAt(block.x() - (c_blocksSize + c_minVicinity), block.y())) {
				block.setDirection(D_LEFT);
			}
			else if (block.y() - (c_blocksSize + c_minVicinity) > virtualField_->getFieldY() && !virtualField_->blockAt(block.x(), block.y() - (c_blocksSize + c_minVicinity))) {
				block.setDirection(D_UP);
			}
		}
	} 
	else if (std::modf(block.x() / (c_blocksSize + 2 * c_minVicinity), &temp) < eps1) {
		if ((block.getDirection() == D_LEFT) && (block.x() - virtualField_->getFieldX() < eps1 
			|| (virtualField_->blockAt(block.x() - c_minVicinity, block.y()) && &block != virtualField_->blockAt(block.x() - c_minVicinity, block.y())))) {
			block.setDirection(D_RIGHT);
		}
	}
	else if (std::modf(block.y() / (c_blocksSize + 2 * c_minVicinity), &temp) < eps1) {
		if ((block.getDirection() == D_UP) && (block.y() - virtualField_->getFieldY() < eps1 
			|| (virtualField_->blockAt(block.x(), block.y() - c_minVicinity) && &block != virtualField_->blockAt(block.x(), block.y() - c_minVicinity)))) {
			block.setDirection(D_DOWN);
		}
	}
	else if (1 - std::modf((block.x() + c_blocksSize) / (c_blocksSize + 2 * c_minVicinity), &temp) < eps1) {
		if ((block.getDirection() == D_RIGHT) && (virtualField_->getFieldX() + virtualField_->getFieldWidth() - block.x() - c_blocksSize < eps1 * (c_blocksSize + 2 * c_minVicinity) * 4
			|| (virtualField_->blockAt(block.x() + block.getWidth() + c_minVicinity, block.y()) && &block != virtualField_->blockAt(block.x() + block.getWidth() + c_minVicinity, block.y())))) {
			block.setDirection(D_LEFT);
		}
	}
	else if (1 - std::modf((block.y() + c_blocksSize) / (c_blocksSize + 2 * c_minVicinity), &temp) < eps1) {
		if ((block.getDirection() == D_DOWN) && (virtualField_->getFieldY() + virtualField_->getFieldHeigth() - block.y() - c_blocksSize < eps1 * (c_blocksSize + 2 * c_minVicinity) * 4
			|| (virtualField_->blockAt(block.x(), block.y() + block.getHeight() + c_minVicinity) && &block != virtualField_->blockAt(block.x(), block.y() + block.getHeight() + c_minVicinity)))) {
			block.setDirection(D_UP);
		}
	}

	virtualField_->removeBlock(&block);
	block.move();
	virtualField_->addBlock(&block);
}

void ArcanoidPhysics::detOfResultingDirection(const std::vector<Directions>& allImpact) {
	bool flagL = false;
	bool flagR = false;
	bool flagD = false;
	bool flagU = false;
	for (int i = 0; i < allImpact.size(); ++i) {
		if (allImpact[i] == D_RIGHT && !flagR) {
			flagR = true;
			if (ball_->getDX() < 0) {
				ball_->setSpeed(-ball_->getDX(), ball_->getDY());
			}
		} else if (allImpact[i] == D_UP && !flagU) {
			flagU = true;
			if (ball_->getDY() > 0) {
				ball_->setSpeed(ball_->getDX(), -ball_->getDY());
			}
		} else if (allImpact[i] == D_LEFT && !flagL) {
			flagL = true;
			if (ball_->getDX() > 0) {
				ball_->setSpeed(-ball_->getDX(), ball_->getDY());
			}
		} else if (allImpact[i] == D_DOWN && !flagD) {
			flagD = true;
			if (ball_->getDY() < 0) {
				ball_->setSpeed(ball_->getDX(), -ball_->getDY());
			}
		}
	}
}

Directions ArcanoidPhysics::interWithOne(AbstractBlock* block) {
	std::tuple<InteractionOutcomes, Directions, short> tuple = block->collisionReact(*ball_);
	switch (std::get<0>(tuple)) {
	case B_NOTHING:
		break;
	case B_DESTROYED:
		for (int i = 0; i < movingBlocks_.size(); ++i) {
			if (movingBlocks_[i] == block) {
				movingBlocks_[i] = nullptr;
			}
		}
		virtualField_->removeBlock(block);
		delete block;
	case B_NOTDESTROYED:
	default:
		changeScore(std::get<2>(tuple));
	}
	return std::get<1>(tuple);
}

std::vector<Directions> ArcanoidPhysics::interactionWithBlocks() {
	AbstractBlock* block1 = nullptr;
	AbstractBlock* block2 = nullptr;
	AbstractBlock* block3 = nullptr;
	AbstractBlock* block4 = nullptr;

	std::vector<Directions> impacts;

	if (virtualField_->isInField(ball_->x(), ball_->y())) {
		block1 = virtualField_->blockAt(ball_->x(), ball_->y());
	}
	if (virtualField_->isInField(ball_->x() + c_ballSize, ball_->y())) {
		block2 = virtualField_->blockAt(ball_->x() + c_ballSize, ball_->y());
	}
	if (virtualField_->isInField(ball_->x(), ball_->y() + c_ballSize)) {
		block3 = virtualField_->blockAt(ball_->x(), ball_->y() + c_ballSize);
	}
	if (virtualField_->isInField(ball_->x() + c_ballSize, ball_->y() + c_ballSize)) {
		block4 = virtualField_->blockAt(ball_->x() + c_ballSize, ball_->y() + c_ballSize);
	}

	if (block1 && block4) {
		if (block1 != block4) {
			impacts.push_back(interWithOne(block1));
		}
		impacts.push_back(interWithOne(block4));
	} else if (block2 && block3) {
		if (block2 != block3) {
			impacts.push_back(interWithOne(block2));
		}
		impacts.push_back(interWithOne(block3));
	} else if (block1 && block2) {
		if (block1 != block2) {
			impacts.push_back(interWithOne(block1));
		}
		impacts.push_back(interWithOne(block2));
	} else if (block1 && block3) {
		if (block1 != block3) {
			impacts.push_back(interWithOne(block1));
		}
		impacts.push_back(interWithOne(block3));
	} else if (block4 && block2) {
		if (block4 != block2) {
			impacts.push_back(interWithOne(block4));
		}
		impacts.push_back(interWithOne(block2));
	} else if (block4 && block3) {
		if (block4 != block3) {
			impacts.push_back(interWithOne(block4));
		}
		impacts.push_back(interWithOne(block3));
	} else if (block1) {
		impacts.push_back(interWithOne(block1));
	} else if (block2) {
		impacts.push_back(interWithOne(block2));
	} else if (block3) {
		impacts.push_back(interWithOne(block3));
	} else if (block4) {
		impacts.push_back(interWithOne(block4));
	}
	return impacts;
}


Directions ArcanoidPhysics::interactionWithBorders() {
	if (ball_->x() <= 0) {
		return D_RIGHT;
	}
	else if (ball_->x() >= sceneSize_ - c_ballSize) {
		return D_LEFT;
	}
	else if (ball_->y() <= 0) {
		return D_DOWN;
	}
	else {
		return D_NO;
	}
}

ArcanoidPhysics::ArcanoidPhysics(QGraphicsScene* scene, int sceneSize) {
	scene_ = scene;
	sceneSize_ = sceneSize;
	ballXInit_ = (sceneSize_ - c_ballSize) / 2;
	ballYInit_ = sceneSize_ - c_ballSize - c_ñarriageHeight - c_blocksSize;
	ñarriageYInit_ = sceneSize_ - c_ñarriageHeight - c_blocksSize;
}

void ArcanoidPhysics::setUp() {
	ball_ = new Ball(0, 0, c_ballSize, c_ballMaxSpeed);
	ñarriage_ = new Carriage(0, 0, c_ñarriageWidth, c_ñarriageHeight, c_ñarriageStartSpeed, sceneSize_ / 2);

	setStartPosForAll();
	virtualfieldInit();

	scene_->addItem(ball_);
	scene_->addItem(ñarriage_);
	ball_->setSpeed(c_ballStartSpeedX, c_ballStartSpeedY);
 
	fTimer_ = new QTimer;
	sTimer_ = new QTimer;
	connect(fTimer_, &QTimer::timeout, this, &ArcanoidPhysics::gameProcessing);
	connect(sTimer_, &QTimer::timeout, this, &ArcanoidPhysics::moveCarriage);
}

void ArcanoidPhysics::moveCarriageEvent(bool side) {
	ñarriageMoveFlag = true;
	ñarriageSide = side;
	moveCarriage();
}

void ArcanoidPhysics::stopMoveCarriageEvent() {
	ñarriageMoveFlag = false;
}

bool ArcanoidPhysics::isGameInProgress() {
	return gameStatus;
}

void ArcanoidPhysics::releaseTheBall() {
	if (stickingCounter && ñarriage_->isBallOnTop(ball_)){
		if (ball_->getDY() > 0) {
			ball_->setSpeed(ball_->getDX(), -ball_->getDY());
		}

		ball_->setPos(ball_->x() + ball_->getDX(), ball_->y() + ball_->getDY());
		stickingCounter--;
	}
}


void ArcanoidPhysics::setGameStatus(bool status) {
	gameStatus = status;
}


ArcanoidPhysics::~ArcanoidPhysics() {
	delete ball_;
	delete ñarriage_;
	delete fTimer_;
	delete sTimer_;
	delete virtualField_;
	delete bottomObstacle_;
	delete scoreTextItem_;
}

void ArcanoidPhysics::gameProcessing() {
	if (fallingBonuses_.size() || gameStatus) {
		if (!(stickingCounter && ñarriage_->isBallOnTop(ball_))) {
			ball_->setPos(ball_->x() + ball_->getDX(), ball_->y() + ball_->getDY());

			if (ball_->y() + c_ballSize >= sceneSize_ || ball_->x() + c_ballSize <= 0 || ball_->x() >= sceneSize_ || ball_->y() + c_ballSize <= 0) {
				defeatProcessing();
			}

			std::vector<Directions> imacts = interactionWithBlocks();

			if (ball_->y() + c_ballSize >= ñarriageYInit_) {
				imacts.push_back(ñarriage_->impactOnBall(*ball_));
			}
			imacts.push_back(interactionWithBorders());

			if (bottomObstacle_) {
				std::tuple<InteractionOutcomes, Directions, short> tuple = bottomObstacle_->collisionReact(*ball_);
				if (std::get<0>(tuple) == B_DESTROYED) {
					delete bottomObstacle_;
					bottomObstacle_ = nullptr;
				}
				imacts.push_back(std::get<1>(tuple));
			}

			detOfResultingDirection(imacts);

		}

		for (int i = 0; i < movingBlocks_.size(); ++i) {
			if (movingBlocks_[i]) {
				moveMovingBlock(*movingBlocks_[i]);
			}
		}

		for (int i = 0; i < bonuses_.size(); ++i) {
			if (bonuses_[i] && bonuses_[i]->isFalling()) {
				scene_->addItem(bonuses_[i]);
				fallingBonuses_.push_back(bonuses_[i]);
				bonuses_[i] = nullptr;
			}
		}

		for (int i = 0; i < fallingBonuses_.size(); ++i) {
			if (fallingBonuses_[i]) {
				fallingBonuses_[i]->setPos(fallingBonuses_[i]->x(), fallingBonuses_[i]->y() + fallingBonuses_[i]->getSpeed());

				if (fallingBonuses_[i]->isTouchÑarriage(*ñarriage_)) {
					fallingBonuses_[i]->bonusActivate();
					delete fallingBonuses_[i];
					fallingBonuses_[i] = nullptr;
				}
				else if (fallingBonuses_[i]->y() >= sceneSize_) {
					delete fallingBonuses_[i];
					fallingBonuses_[i] = nullptr;
				}
			}
		}

		if (bottomObstacleFlag) {
			if (!bottomObstacle_) {
				bottomObstacleCreate();
			}
			bottomObstacleFlag = false;
		}

		if (movingBlockFlag) {
			movingBlockCreate();
			movingBlockFlag = false;
		}

		scoreTextItem_->setPos(ñarriage_->x() + ñarriage_->getWidth() / 2, ñarriage_->y() + ñarriage_->getHeight() / 2);

		scene_->update();
		fTimer_->start(c_timeInterval);
	}
}


void ArcanoidPhysics::moveCarriage() {
	if (ñarriageMoveFlag) {
		ñarriage_->move(ñarriageSide);
		if (ñarriage_->x() < 0) {
			ñarriage_->setPos(0, ñarriage_->y());
		}
		else if (ñarriage_->x() + ñarriage_->getWidth() > sceneSize_) {
			ñarriage_->setPos(sceneSize_ - ñarriage_->getWidth(), ñarriage_->y());
		}
		else if (stickingCounter && ñarriage_->isBallOnTop(ball_)) {
			if (ñarriageSide) {
				ball_->setPos(ball_->x() - ñarriage_->getSpeed(), ball_->y());
			}
			else {
				ball_->setPos(ball_->x() + ñarriage_->getSpeed(), ball_->y());
			}
		}

		sTimer_->start(c_timeInterval);
	}
}

