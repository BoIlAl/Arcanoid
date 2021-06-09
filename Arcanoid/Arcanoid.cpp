#include "Arcanoid.h"


Arcanoid::Arcanoid(QWidget *parent) : QMainWindow(parent) {

		this->setFixedSize(c_sceneSize, c_sceneSize);
		scene_ = new QGraphicsScene();
		scene_->setSceneRect(0, 0, c_sceneSize, c_sceneSize);

		view_ = new QGraphicsView(scene_, this);
		view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

		view_->setGeometry(0, 0, c_sceneSize, c_sceneSize);
		view_->show();

		ArcPhysics_ = new ArcanoidPhysics(scene_, c_sceneSize);
		ArcPhysics_->setUp();

		ui.setupUi(this);
}

Arcanoid::~Arcanoid() {
	delete scene_;
	delete view_;
}

void Arcanoid::mousePressEvent(QMouseEvent* event){
	if (!ArcPhysics_->isGameInProgress()) {
		ArcPhysics_->setGameStatus(true);
		ArcPhysics_->gameProcessing();
	}
	switch (event->button()) {
	case Qt::LeftButton:
		ArcPhysics_->moveCarriageEvent(true);
		break;

	case Qt::RightButton:
		ArcPhysics_->moveCarriageEvent(false);
		break;
	case Qt::MiddleButton:
		ArcPhysics_->releaseTheBall();
	}
}

void Arcanoid::mouseReleaseEvent(QMouseEvent* event) {
	switch (event->button()) {
	case Qt::LeftButton:
		ArcPhysics_->stopMoveCarriageEvent();
		break;

	case Qt::RightButton:
		ArcPhysics_->stopMoveCarriageEvent();
		break;
	}
}
