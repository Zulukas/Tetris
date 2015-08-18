#include "box.h"

#include <cstdlib>

Box::Color Box :: genColor() {
	int num = rand() % 7;

	if (num == 0)
		return Box::CYAN;
	else if (num == 1)
		return Box::BLUE;
	else if (num == 2)
		return Box::ORANGE;
	else if (num == 3)
		return Box::YELLOW;
	else if (num == 4)
		return Box::GREEN;
	else if (num == 5)
		return Box::PURPLE;
	else
		return Box::RED;
}

Box :: Box(Shape::Type t) { 
	switch (t) {
		case Shape::I:
			color = CYAN;
			break;
		case Shape::J:
			color = BLUE;
			break;
		case Shape::L:
			color = ORANGE;
			break;
		case Shape::O:
			color = YELLOW;
			break;
		case Shape::S:
			color = GREEN;
			break;
		case Shape::T:
			color = PURPLE;
			break;
		case Shape::Z:
			color = RED;
			break;
	}
	falling = true;
}

Box :: Box(Box::Color color) {
	this->color = color;
	falling = false;
}

Box::Color Box :: getColor() { 
	return color;
}

bool Box :: isFalling() {
	return falling;
}

bool Box :: isClear() {
	return (color == CLEAR);
}

void Box :: setBox() {
	if (falling)
		falling = false;

}