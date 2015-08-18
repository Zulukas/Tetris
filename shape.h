#ifndef SHAPE_H
#define SHAPE_H

#include <cstdlib>

class Shape {
public:
	enum Type { I, J, L, O, S, T, Z };
	enum Rotation { UP, LEFT, DOWN, RIGHT };

	Shape();
	Type getType();
	Rotation getRotation();

	void rotateClockwise();
	void rotateCounterClockwise();
private:
	Type t;
	Rotation r;

	Type genRandomType();
	Rotation genRandomRotation();
};

#endif