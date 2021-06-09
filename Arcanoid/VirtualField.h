#pragma once
#include "Blocks.h"
//Класс хранящий блоки и их метонахождение в виртуальной таблице

class Virtualfield {
private:
	std::vector<AbstractBlock*> field_; //Вектор блоков
	int vectWidth_; //Ширина матрицы виртуальной таблицы
	int vectHeigth_; //Высота матрицы виртуальной таблицы

	double fieldWidth_; //Ширина виртуальной таблицы
	double fieldHeigth_; //Высота виртуальной таблицы
	double fieldX_; //Левая точка виртуальной таблицы относительно сцены
	double fieldY_; //Верхняя точка виртуальной таблицы относительно сцены

	int indByCoord(double, double) const; //Вспомогательная метод, возвращающая индекс в векторе по координатам
public:
	Virtualfield(int, int, double, double, double, double); //Конструктор принимает данные по своему местонахождению (инициализируются переменные в строках 8-14)
	AbstractBlock* blockAt(double, double) const; //Метод, возвращающий блок, находящийся в соответсвующий координатам ячейке вирутальной таблицы (nullptr, если там пусто)
	void addBlock(AbstractBlock*); //Метод, добавляющий блок в таблицу
	void removeBlock(AbstractBlock*); //Метод, удадяющий блок из таблицы
	std::pair<double, double> Virtualfield::getRandomEmptyCoord() const; //Метод, возвращающий координаты левой верхней точки случайной свободной ячейки 
																																			 //(Отрицательные значения в случае отсутсвия пустых ячеек)
	bool isInField(double, double) const; //Метод, проверяющий находятся ли точка по координатам внутри данного виртуального поля

	double getFieldX() const;
	double getFieldY() const;
	double getFieldWidth() const;
	double getFieldHeigth() const;
	~Virtualfield();
};