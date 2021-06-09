#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>
#include "ui_Arcanoid.h"
#include "ArcanoidPhysics.h"



class Arcanoid : public QMainWindow
{
  

public:
  Arcanoid(QWidget *parent = Q_NULLPTR);
	~Arcanoid();
private:
	const double c_sceneSize = 800.0; //Игровое поле - квадрат

	QGraphicsScene* scene_ = nullptr;
	QGraphicsView* view_ = nullptr;
	ArcanoidPhysics* ArcPhysics_ = nullptr;
  Ui::ArcanoidClass ui;

protected:

	//Реализуются следующие элементы управления: ПКМ - движение каретки вправо, ЛКМ - движение каретки влево, Центральная кнопка мыши - отлипание шарика от каретки/старт игры
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
};
