#ifndef BOX_H
#define BOX_H

#include "shape.h"

class Box {
public:
	enum Color { CLEAR, CYAN, BLUE, ORANGE, YELLOW, GREEN, PURPLE, RED, WHITE };

	Box(Shape::Type t);
	Box(Color color);
	Color getColor();

	bool isFalling();
	bool isClear();

	void setBox();

private:
	Color color;
	bool falling;

	Color genColor();
};

#endif