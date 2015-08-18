#include "shape.h"

Shape::Type Shape :: genRandomType() {
	int num = rand() % 7;

	if (num == 0) 
		return Shape::I;
	else if (num == 1)
		return Shape::J;
	else if (num == 2)
		return Shape::L;
	else if (num == 3)
		return Shape::O;
	else if (num == 4)
		return Shape::S;
	else if (num == 5)
		return Shape::T;
	else
		return Shape::Z;
}

Shape::Rotation Shape :: genRandomRotation() {
	int num = rand() % 4;

	if (num == 0)
		return Shape::UP;
	else if (num == 1)
		return Shape::LEFT;
	else if (num == 2)
		return Shape::DOWN;
	else
		return Shape::RIGHT;
}

Shape :: Shape () {
	t = genRandomType();
	r = genRandomRotation();
}

Shape::Type Shape :: getType() { 
	return this->t;
}

Shape::Rotation Shape :: getRotation() {
	return this->r;
}

void Shape :: rotateClockwise() {
	if (r == Shape::UP)
		r = Shape::RIGHT;
	else if (r == Shape::RIGHT)
		r = Shape::DOWN;
	else if (r == Shape::DOWN)
		r = Shape::LEFT;
	else if (r == Shape::LEFT)
		r = Shape::UP;
}

void Shape :: rotateCounterClockwise() {
	if (r == Shape::UP)
		r = Shape::LEFT;
	else if (r == Shape::LEFT)
		r = Shape::DOWN;
	else if (r == Shape::DOWN)
		r = Shape::RIGHT;
	else if (r == Shape::RIGHT)
		r = Shape::UP;
}