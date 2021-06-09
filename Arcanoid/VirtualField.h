#pragma once
#include "Blocks.h"
//����� �������� ����� � �� �������������� � ����������� �������

class Virtualfield {
private:
	std::vector<AbstractBlock*> field_; //������ ������
	int vectWidth_; //������ ������� ����������� �������
	int vectHeigth_; //������ ������� ����������� �������

	double fieldWidth_; //������ ����������� �������
	double fieldHeigth_; //������ ����������� �������
	double fieldX_; //����� ����� ����������� ������� ������������ �����
	double fieldY_; //������� ����� ����������� ������� ������������ �����

	int indByCoord(double, double) const; //��������������� �����, ������������ ������ � ������� �� �����������
public:
	Virtualfield(int, int, double, double, double, double); //����������� ��������� ������ �� ������ ��������������� (���������������� ���������� � ������� 8-14)
	AbstractBlock* blockAt(double, double) const; //�����, ������������ ����, ����������� � �������������� ����������� ������ ����������� ������� (nullptr, ���� ��� �����)
	void addBlock(AbstractBlock*); //�����, ����������� ���� � �������
	void removeBlock(AbstractBlock*); //�����, ��������� ���� �� �������
	std::pair<double, double> Virtualfield::getRandomEmptyCoord() const; //�����, ������������ ���������� ����� ������� ����� ��������� ��������� ������ 
																																			 //(������������� �������� � ������ ��������� ������ �����)
	bool isInField(double, double) const; //�����, ����������� ��������� �� ����� �� ����������� ������ ������� ������������ ����

	double getFieldX() const;
	double getFieldY() const;
	double getFieldWidth() const;
	double getFieldHeigth() const;
	~Virtualfield();
};