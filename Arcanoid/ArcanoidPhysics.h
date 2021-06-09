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
	double const c_ballSize = 25.0; //������ ������
	double const c_ballStartSpeedX = -1; //��������� �������� ������ �� X 
	double const c_ballStartSpeedY = -1.1; //��������� �������� ������ �� Y 
	double const c_ballMaxSpeed = 3; //������������ �������� �������� ������

	double const c_�arriageStartSpeed = 2; //�������� �������
	double const c_�arriageWidth = 150; //��������� ������ �������
	double const c_�arriageHeight = 50; //������ �������

	double const c_blocksSize = 60; //������ ������ (�������)
	double const c_minVicinity = 20; //������ ������ ������� ������ ������ 

	double const c_bonusSize = 20; //������ �������
	double const c_bonusSpeed = 1; //�������� �������
	double const c_bonusWidthMultiplier = 1.2; //�������� ��������� ������ �������
	double const c_bonusSpeedMultiplier = 1.1; //�������� ��������� �������� ������
	int const c_bonusNumOfSticking = 3; //���������� ���������� �� ������

	int const c_strongBlockHealth = 2; //���������� �������� ������ �� ���������
	double const c_springyBlockMultiplier = 1.1; //��������� �������� ������ �� �����
	double const c_blocksSpeed = 0.2; //�������� ���������� ������

	int const c_defeatPoint = -10; //���������� ����� �� ���������

	int const c_timeInterval = 1; //������� ���������� � �������������
	
	double ballXInit_; //��������� ��������� ������ �� X
	double ballYInit_; //��������� ��������� ������ �� Y
	double �arriageYInit_; //��������� ��������� ������� �� Y

	QGraphicsScene* scene_ = nullptr; //��������� �� ����� � ������� �������� �����
	double sceneSize_; //������ ����� (����� �������� � ���������)

	//
	QTimer* fTimer_ = nullptr;
	QTimer* sTimer_ = nullptr;
	Ball* ball_ = nullptr;
	Carriage* �arriage_ = nullptr;
	Virtualfield* virtualField_ = nullptr;
	SimpleBlock* bottomObstacle_ = nullptr;
	QGraphicsTextItem* scoreTextItem_ = nullptr;
	

	std::vector<AbstractBonus*> bonuses_; //������ ������� � ������
	std::vector<AbstractBonus*> fallingBonuses_; //������ �������� ������� � ������
	std::vector<MovingBlock*> movingBlocks_; //������ ���������� ������
	
	int score_ = 0;
	bool gameStatus = false; //���� ��������� ����, ���������� ����� �� � �������� ����� ����������� �������� ��������� ������

	bool �arriageMoveFlag = false; //����, ������������ �������� �� ������� � ������ ������
	bool �arriageSide; //����, ������������, � ����� ������� �������� ������� (true - �����, false - ������)

	int stickingCounter = 1; //������� ���������� ���������� ������ � �������
	bool bottomObstacleFlag = false; //����, ������������ ������������� �������� ������������ ���
	bool movingBlockFlag = false; //����, ������������ ������������� �������� ������ ����������� �����

	void setStartPosForAll(); //�����, ����������� ���� � ��������� ���������. �� ������ �� �����.
	void virtualfieldInit(); //�����, ���������������� ����������� ����, ����������� ��� �������. ����� ������� ��� ��������� �����, ��������� ������ ���������� �������

	void defeatProcessing(); //��������� ���������. ���������� ���� � ��������� ���������, ���������� ������ ����
	void changeScore(int); //�����, ����������� � �������� ���������� ����� ��������� ��������

	void bottomObstacleCreate(); //����� �������� ������������ ���
	void movingBlockCreate(); //����� �������� ����������� �����, ������� ��� ������������ ����������� � �������������� ������
	void moveMovingBlock(MovingBlock&); //����� ����������� ������ ����������� ����������� �����

	void detOfResultingDirection(const std::vector<Directions>&); //����� ����������� ������ ���� ����������� ��� ������� ������. 
																																			 //��������� �������� ����������� ��������� ��� �������� � ������������� ������ ��.
	Directions interWithOne(AbstractBlock*); //��������������� �����, ������������ �������������� ������ � ���������� ������. ���������� �����������. � ������� ���� ��������� �����
	std::vector<Directions> interactionWithBlocks(); //�����, ������������ �������������� ������ �� ����� �������. ���������� ������ ���� �����������, � ������� ����� ���������� �����
	Directions interactionWithBorders(); //�����, ������������ �������������� ������ � ��������� ����. ���������� �����������, � ������� ������� ���������� �����

public:
	ArcanoidPhysics(QGraphicsScene*, int); //����������� ��������� ����� � �� ������, ����������� ��������� ��������� ���������
	void setUp(); //����� ������������ ��� �������� �������� ���� �� ��������� �������, ���������������� ����������� ���� ������, ��������� ������� � �� �������
	void moveCarriageEvent(bool); //�����, ����������� �������� ������� � ��������������� ����������� 
	void stopMoveCarriageEvent(); //�����, ��������������� �������� �������
	bool isGameInProgress(); //����� ������������ gameStatus
	void releaseTheBall(); //����� ������������� �����, ���� �� � ������ ������ ��������� � �������
	void setGameStatus(bool); //����� ��������������� �������� gameStatus
	~ArcanoidPhysics();

public slots:
	void gameProcessing(); //�������� ���� ����
	void moveCarriage(); //��������������� ���� ����, �������������� �������� �������
};