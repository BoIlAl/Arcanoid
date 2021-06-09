#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "Ball.h"
#include "Carriage.h"
#include "VirtualField.h"
#include "Bonus.h"
#include "Blocks.h"


class ArcanoidPhysics : public QObject{

	Q_OBJECT

private:
	double const c_ballSize = 25.0; //Размер шарика
	double const c_ballStartSpeedX = -1; //Стартовая скорость шарика по X 
	double const c_ballStartSpeedY = -1.1; //Стартовая скорость шарика по Y 
	double const c_ballMaxSpeed = 3; //Максимальное значение скорости шарика

	double const c_сarriageStartSpeed = 2; //Скорость каретки
	double const c_сarriageWidth = 150; //Начальная ширина каретки
	double const c_сarriageHeight = 50; //Высота каретки

	double const c_blocksSize = 60; //Размер блоков (Квадрат)
	double const c_minVicinity = 20; //Размер пустой области вокруг блоков 

	double const c_bonusSize = 20; //Размер бонусов
	double const c_bonusSpeed = 1; //Скорость бонусов
	double const c_bonusWidthMultiplier = 1.2; //Бонусный множитель ширины каретки
	double const c_bonusSpeedMultiplier = 1.1; //Бонусный множитель скорости шарика
	int const c_bonusNumOfSticking = 3; //Количество прилипаний от бонуса

	int const c_strongBlockHealth = 2; //Количество здоровья блоков со здоровьем
	double const c_springyBlockMultiplier = 1.1; //Множитель скорости шарика от блока
	double const c_blocksSpeed = 0.2; //Скорость движущихся блоков

	int const c_defeatPoint = -10; //Количество очков за поражение

	int const c_timeInterval = 1; //Частота обновления в миллисекундах
	
	double ballXInit_; //Стартовое положение шарика по X
	double ballYInit_; //Стартовое положение шарика по Y
	double сarriageYInit_; //Стартовое положение каретки по Y

	QGraphicsScene* scene_ = nullptr; //Указатель на сцену с которой работает класс
	double sceneSize_; //Размер сцены (Класс работает с квадратом)

	//
	QTimer* fTimer_ = nullptr;
	QTimer* sTimer_ = nullptr;
	Ball* ball_ = nullptr;
	Carriage* сarriage_ = nullptr;
	Virtualfield* virtualField_ = nullptr;
	SimpleBlock* bottomObstacle_ = nullptr;
	QGraphicsTextItem* scoreTextItem_ = nullptr;
	

	std::vector<AbstractBonus*> bonuses_; //Вектор бонусов в блоках
	std::vector<AbstractBonus*> fallingBonuses_; //Вектор падающих бонусов в блоках
	std::vector<MovingBlock*> movingBlocks_; //Вектор движущихся блоков
	
	int score_ = 0;
	bool gameStatus = false; //Флаг состояния игры, определяет будет ли в основном цикле выполняться пересчет положения шарика

	bool сarriageMoveFlag = false; //Флаг, определяющий движется ли каретка в данный момент
	bool сarriageSide; //Флаг, определяющий, в какую сторону движется каретка (true - влево, false - вправо)

	int stickingCounter = 1; //Счетчик количества прилипаний шарика к каретке
	bool bottomObstacleFlag = false; //Флаг, определяющий необходимость создания одноразового дна
	bool movingBlockFlag = false; //Флаг, определяющий необходимость создания нового движущегося блока

	void setStartPosForAll(); //Метод, переводящий поле в стартовое состояние. Не влияет на блоки.
	void virtualfieldInit(); //Метод, инициализирующий виртуальное поле, наполняющий его блоками. Также создает все стартовые блоки, наполняет вектор неактивных бонусов

	void defeatProcessing(); //Обработка поражения. Выставляет поле в начальное поражение, выставляет статус игры
	void changeScore(int); //Метод, добавляющий к текущему количеству очков указанное значение

	void bottomObstacleCreate(); //Метод создания одноразового дна
	void movingBlockCreate(); //Метод создания движущегося блока, который для отслеживания добавляется в соответсвующий вектор
	void moveMovingBlock(MovingBlock&); //Метод реализующий логику перемещения движущегося блока

	void detOfResultingDirection(const std::vector<Directions>&); //Метод принимающий вектор всех направлений для данного шарика. 
																																			 //Вычисляет итоговое направление компонент его скорости и соответсвенно меняет их.
	Directions interWithOne(AbstractBlock*); //Вспомогательный метод, определяющий взаимодействие шарика с конкретным блоком. Возвращает направление. в которое блок оттолкнул шарик
	std::vector<Directions> interactionWithBlocks(); //Метод, определяющий взаимодействие шарика со всеми блоками. Возвращает вектор всех направлений, в которые блоки оттолкнули шарик
	Directions interactionWithBorders(); //Метод, определяющий взаимодействие шарика с границами поля. Возвращает направление, в которые граница оттолкнула шарик

public:
	ArcanoidPhysics(QGraphicsScene*, int); //конструктор принимает сцену и ее размер, высчитывает начальные положения элементов
	void setUp(); //Метод выставляющий все элементы игрового поля на стартовые позиции, инициализирующий виртуальное поле блоков, связывает таймеры с их циклами
	void moveCarriageEvent(bool); //Метод, запускающий движение каретки в соответствующем направлении 
	void stopMoveCarriageEvent(); //Метод, останавливающий движение каретки
	bool isGameInProgress(); //Метод возвращающий gameStatus
	void releaseTheBall(); //Метод освобождающий шарик, если он в данный момент прилеплен к каретке
	void setGameStatus(bool); //Метод устанавливающий значение gameStatus
	~ArcanoidPhysics();

public slots:
	void gameProcessing(); //Основной цикл игры
	void moveCarriage(); //Вспомогательный цикл игры, обеспечивающий движение каретки
};