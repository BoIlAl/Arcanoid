#include "VirtualField.h"

int Virtualfield::indByCoord(double x, double y) const {
	std::pair<int, int> coord;
	if (x == fieldWidth_ + fieldX_) {
		coord.first = vectWidth_ - 1;
	}
	else {
		coord.first = floor(x / ((fieldWidth_ - fieldX_) / vectWidth_));
	}
	if (y == fieldHeigth_ + fieldY_) {
		coord.second = vectHeigth_ - 1;
	}
	else {
		coord.second = floor(y / ((fieldHeigth_ - fieldY_) / vectHeigth_));
	}
	
	return coord.first + coord.second * vectWidth_;
}

Virtualfield::Virtualfield(int width, int heigth, double x, double y, double w, double h) {
	vectWidth_ = width;
	vectHeigth_ = heigth;
	fieldX_ = x;
	fieldY_ = y;
	fieldWidth_ = w;
	fieldHeigth_ = h;

	for (int i = 0; i < width * heigth; ++i) {
		field_.push_back(nullptr);
	}
}

AbstractBlock* Virtualfield::blockAt(double x, double y) const {
	int ind;
	ind = indByCoord(x, y);
	return field_[ind];
}

void Virtualfield::addBlock(AbstractBlock* newItem) {
	int ind1;
	int ind2;
	int ind3;
	int ind4;
	ind1 = indByCoord(newItem->x(), newItem->y());
	ind2 = indByCoord(newItem->x() + newItem->getWidth(), newItem->y());
	ind3 = indByCoord(newItem->x(), newItem->y() + newItem->getHeight());
	ind4 = indByCoord(newItem->x() + newItem->getWidth(), newItem->y() + newItem->getHeight());

	field_[ind1] = newItem;
	field_[ind2] = newItem;
	field_[ind3] = newItem;
	field_[ind4] = newItem;
}

void Virtualfield::removeBlock(AbstractBlock* block) {
	for (int i = 0; i < field_.size(); ++i) {
		if (field_[i] == block) {
			field_[i] = nullptr;
		}
	}
}

std::pair<double, double> Virtualfield::getRandomEmptyCoord() const {
	std::vector<int> tempV;
	for (int i = 1; i < field_.size(); ++i) {
		if (field_[i] == nullptr) {
			tempV.push_back(i);
		}
	}
	std::pair<double, double> coordDouble = {-1.0, -1.0};
	if (field_.size()) {
		int tempI = tempV[round(static_cast<double>(std::rand()) * (tempV.size() - 1) / RAND_MAX)];
		std::pair<int, int> coordInt;
		coordInt.second = tempI / vectWidth_;
		coordInt.first = tempI - coordInt.second * vectWidth_;
		coordDouble.first = fieldX_ + coordInt.first * ((fieldWidth_ - fieldX_) / vectWidth_);
		coordDouble.second = fieldY_ + coordInt.second * ((fieldHeigth_ - fieldY_) / vectHeigth_);
		return coordDouble;
	} else {
		return coordDouble;
	}
}

bool Virtualfield::isInField(double x, double y) const {
	if (x < fieldX_ || y < fieldY_ || x > (fieldX_ + fieldWidth_) || y > (fieldY_ + fieldHeigth_)) {
		return false;
	}
	return true;
}

double Virtualfield::getFieldX() const {
	return fieldX_;
}

double Virtualfield::getFieldY() const {
	return fieldY_;
}

double Virtualfield::getFieldWidth() const {
	return fieldWidth_;
}

double Virtualfield::getFieldHeigth() const {
	return fieldHeigth_;
}

Virtualfield::~Virtualfield() {
	for (int i = 0; i < field_.size(); ++i) {
		delete field_[i];
	}
}
