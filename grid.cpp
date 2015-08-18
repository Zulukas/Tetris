#include "grid.h"

/*********************************************************************
 * Constructor: Allocate all the boxes to the clear box.
 ********************************************************************/
Grid :: Grid() {
	collision = false;
	clear = new Box(Box::CLEAR);

	for (int y = 0; y < Grid::HEIGHT; y++) 
		for (int x = 0; x < Grid::WIDTH; x++) {
			grid[y][x] = clear;
		}
}

/*********************************************************************
 * Destructor: Boxes are dynamically allocated and as a result need
 * to be properly destroyed upon grid destruction.
 ********************************************************************/
Grid :: ~Grid() {
	delete clear;
	clear = NULL;

	for (int y = 0; y < Grid::HEIGHT; y++) 
		for (int x = 0; x < Grid::WIDTH; x++) {
			if (grid[y][x] != NULL) {
				Box *thisBox = grid[y][x];
				delete thisBox;
				thisBox = NULL;
			}
		}
}

/*********************************************************************
 * Return the box object at the coordinate arguments
 ********************************************************************/
Box * Grid :: getBoxAtLocation(int x, int y) {
	return grid[y][x];
}

/*********************************************************************
 * Return the color of the box argument.
 ********************************************************************/
Box::Color Grid :: getBoxColor(Box *box) {
	return box->getColor();
}

/*********************************************************************
 * Check to see if all boxes on this row are not clear.  If they are,
 * delete the row and shift every above it down.
 ********************************************************************/
bool Grid :: isRowComplete(int row) {
	for (int i = 0; i < Grid::WIDTH; i++)
		if (getBoxColor(grid[row][i]) == Box::CLEAR)
			return false;

	return true;
}

/*********************************************************************
 * Return the collision flag, if the collision flag is set then the 
 * game is over.
 ********************************************************************/
bool Grid :: isGameOver() {
	return collision;
}

/*********************************************************************
 * Shift the falling shape left if it can without going out of bounds
 * or conflicting with another box to the left.
 ********************************************************************/
void Grid :: shiftLeft() {
	for (int y = 0; y < Grid::HEIGHT; y++)
		for (int x = 0; x < Grid::WIDTH; x++) {
			Box *temp = grid[y][x];

			if (temp->isFalling()) {
				if (x == 0 || !grid[y][x - 1]->isClear())
					continue;
				else
					grid[y][x - 1] = temp;
					grid[y][x] = Grid::clear;
			}
		}
}

/*********************************************************************
 * Shift the falling shape right if it can without going out of bounds
 * or conflicting with another box to the right.
 ********************************************************************/
void Grid :: shiftRight() {
	for (int y = 0; y < Grid::HEIGHT; y++)
		for (int x = Grid::WIDTH; x >= 0; x++) {
			Box *temp = grid[y][x];

			if (temp->isFalling()) {
				if (x == Grid::WIDTH - 1 || !grid[y][x + 1]->isClear())
					continue;
				else
					grid[y][x + 1] = temp;
					grid[y][x] = Grid::clear;
			}
		}
}

/*********************************************************************
 * Rotate the shape left if it can without conflicting with another
 * block.  If the block is on a width boundary, rotating should 
 * cause it to adjust it's location provided that it will not conflict
 * with another block in doing so.
 ********************************************************************/
void Grid :: rotateLeft() {
	//Determine the top left shape, treating the shape as a generic
	//quadrilateral

	


}

/*********************************************************************
 * Rotate the shape right if it can without conflicting with another
 * block. If the block is on a width boundary, rotating should 
 * cause it to adjust it's location provided that it will not conflict
 * with another block in doing so.
 ********************************************************************/
void Grid :: rotateRight() {

}

/*********************************************************************
 * Cause all falling blocks to fall one block.
 ********************************************************************/
void Grid :: tick() {
	//Scan the grid from the bottom-right corner up (right to left, bottom to top)
	for (int y = Grid::HEIGHT - 1; y >= 0; y--) {
		for (int x = Grid::WIDTH - 1; x >= 0; x--) { 
			Box *temp = grid[y][x]; //Store the current box conveniently

			//If this box is not clear and is falling...
			if (!temp->isClear() && temp->isFalling()) {
				//If the box below this box is clear, shift down
				if (grid[y + 1][x]->isClear()) {
					grid[y + 1][x] = temp;
					grid[y][x] = Grid::clear;
				}
				else { //Otherwise set the falling flag to false to halt the box
					temp->setBox();
				}
			}
		}
	}

	//Now let's delete any completed rows...
	deleteCompletedRows();
}

/*********************************************************************
 * Delete any completed rows using dropRow(int row).
 ********************************************************************/
void Grid :: deleteCompletedRows() {
	for (int y = Grid::HEIGHT - 1; y >= 0; y++) {
		if (isRowComplete(y)) {
			dropRow(y);
		}
	}
}

/*********************************************************************
 * Recursively shift the rows down
 ********************************************************************/
 void Grid :: dropRow(int row) {
 	if (row == 0) {
 		for (int x = 0; x < Grid::WIDTH; x++)
 			grid[0][x] = Grid::clear;

 		return;
 	}

 	for (int x = 0; x < Grid::WIDTH; x++)
 		grid[row][x] = grid[row - 1][x];

 	dropRow(row - 1);
 }

void Grid :: draw(Painter p) {
	//stubbed
}

/*********************************************************************
 * Generate a new shape in the grid.  Do error checking to see if the
 * new shape is conflicting with any existing box in it's spawn space.
 * If it is, the collision flag is set and the function returns 
 * prematurely, causing the game to end.
 ********************************************************************/
void Grid :: genShape() {
	Shape newShape;
	currentShape = newShape;
	shapeOrigin.x = 4;
	shapeOrigin.y = 0;

	Shape::Type t = newShape.getType();
	Shape::Rotation r = newShape.getRotation();

	//All shapes start at row 0, column 4 (or are at least referenced there)

	switch (t) {
		case Shape::I:
			if (r == Shape::UP || r == Shape::DOWN) {
				if (!grid[0][4]->isClear() || !grid[1][4]->isClear() ||
					!grid[2][4]->isClear() || !grid[3][4]->isClear()) {
					collision = true;
					return;
				}
				else {
					place_I_Veritcal(4, 0);
				}
			}
			else if (r == Shape::LEFT || r == Shape::RIGHT) {
				if ((!grid[0][4]->isClear()) || (!grid[0][5]->isClear()) ||
					(!grid[0][6]->isClear()) || (!grid[0][7]->isClear())) {
					collision = true;
					return;
				}
				else {
					place_I_Horizontal(4, 0);
				}
			}				
			break;			
		case Shape::J:
			if (r == Shape::UP) {
				if ((!grid[0][5]->isClear()) || (!grid[1][5]->isClear()) ||
					(!grid[2][4]->isClear()) || (!grid[2][5]->isClear())) {
					collision = true;
					return;
				} 
				else {
					place_J_Up(0, 4);
				}
			}
			else if (r == Shape::DOWN) {
				if ((!grid[0][4]->isClear()) || (!grid[0][5]->isClear()) ||
					(!grid[1][4]->isClear()) || (!grid[2][4]->isClear())) {
					collision = true;
					return;
				}
				else {
					place_J_Down(0, 4);	
				}
			}
			else if (r == Shape::LEFT) {
				if ((!grid[0][4]->isClear()) || (!grid[0][5]->isClear()) ||
					(!grid[0][6]->isClear()) || (!grid[1][6]->isClear())) {
					collision = true;
					return;
				}
				else {
					place_J_Left(0, 4);
				}
			}
			else if (r == Shape::RIGHT) {
				if ((!grid[0][4]->isClear()) || (!grid[1][4]->isClear()) ||
					(!grid[1][5]->isClear()) || (!grid[1][6]->isClear())) {
					collision = true;
					return;
				}
				else {
					place_J_Right(0, 4);
				}
			}
			break;
		case Shape::L:
			if (r == Shape::UP) {
				if ((!grid[0][4]->isClear()) || (!grid[1][4]->isClear()) ||
					(!grid[2][4]->isClear()) || (!grid[2][5]->isClear())) {
					collision = true;
					return;
				} 
				else {
					place_L_Up(0, 4);
				}
			}
			else if (r == Shape::DOWN) {
				if ((!grid[0][4]->isClear()) || (!grid[0][5]->isClear()) ||
					(!grid[1][5]->isClear()) || (!grid[2][5]->isClear())) {
					collision = true;
					return;
				}
				else {
					place_L_Down(0, 4);
				}
			}
			else if (r == Shape::LEFT) {
				if ((!grid[1][4]->isClear()) || (!grid[1][5]->isClear()) ||
					(!grid[1][6]->isClear()) || (!grid[0][6]->isClear())) {
					collision = true;
					return;
				}
				else {
					place_L_Left(0, 4);
				}
			}
			else if (r == Shape::RIGHT) {
				if ((!grid[0][4]->isClear()) || (!grid[1][4]->isClear()) ||
					(!grid[0][5]->isClear()) || (!grid[0][6]->isClear())) {
					collision = true;
					return;
				}
				else {
					place_L_Right(0, 4);
				}
			}
			break;
		case Shape::O:
			if ((!grid[0][4]->isClear()) || (!grid[0][5]->isClear()) ||
				(!grid[1][4]->isClear()) || (!grid[1][5]->isClear())) {
				collision = true;
				return;
			}
			else {
				place_O(0, 4);
			}
			break;
		case Shape::S:
			if (r == Shape::UP || r == Shape::DOWN) {
				if ((!grid[0][4]->isClear()) || (!grid[1][4]->isClear()) ||
				(!grid[1][5]->isClear()) || (!grid[2][5]->isClear())) {
					collision = true;
					return;
				}
				else {
					place_S_Vertical(0, 4);
				}
			}
			if (r == Shape::LEFT || r == Shape::RIGHT) {
				if ((!grid[0][4]->isClear()) || (!grid[0][5]->isClear()) ||
				(!grid[1][5]->isClear()) || (!grid[1][6]->isClear())) {
					collision = true;
					return;
				}
				else {
					place_S_Horizontal(0, 4);
				}	
			}
			break;			
		case Shape::T:
			if (r == Shape::UP) {
				if ((!grid[0][5]->isClear()) || (!grid[1][4]->isClear()) ||
					(!grid[1][5]->isClear()) || (!grid[1][6]->isClear())) {
					collision = true;
					return;
				}
				else {
					place_T_Up(0, 4);
				}
			}
			else if (r == Shape::DOWN) {
				if ((!grid[0][4]->isClear()) || (!grid[0][5]->isClear()) ||
					(!grid[0][6]->isClear()) || (!grid[1][5]->isClear())) {
					collision = true;
					return;
				}
				else {
					place_T_Down(0, 4);
				}
			}
			else if (r == Shape::LEFT) {
				if ((!grid[0][5]->isClear()) || (!grid[1][4]->isClear()) ||
					(!grid[1][5]->isClear()) || (!grid[1][6]->isClear())) {
					collision = true;
					return;
				}
				else {
					place_T_Left(0, 4);
				}
			}
			else if (r == Shape::RIGHT) {
				if ((!grid[0][4]->isClear()) || (!grid[1][4]->isClear()) ||
					(!grid[2][4]->isClear()) || (!grid[1][5]->isClear())) {
					collision = true;
					return;
				}
				else {
					place_T_Right(0, 4);
				}
			}
			break;			
		case Shape::Z:
			if (r == Shape::UP || r == Shape::DOWN) {
				if ((!grid[0][5]->isClear()) || (!grid[1][4]->isClear()) ||
					(!grid[1][5]->isClear()) || (!grid[2][4]->isClear())) {
					collision = true;
					return;
				}
				else {
					place_Z_Vertical(0, 4);
				}
			}
			else if (r == Shape::LEFT || r == Shape::RIGHT) {
				if ((!grid[0][4]->isClear()) || (!grid[0][5]->isClear()) ||
					(!grid[1][5]->isClear()) || (!grid[1][6]->isClear())) {
					collision = true;
					return;
				}
				else {
					place_Z_Horizontal(0, 4);
				}
			}
			break;
	}
}

/*********************************************************************
 * All member functions below are the spawn patterns of the variations
 * of the shapes.
 ********************************************************************/

void Grid :: place_I_Horizontal(int x, int y) {
	Shape::Type t = Shape::I;
	Box *b = new Box(t);

	grid[0 + y][0 + x] = b;
	grid[0 + y][1 + x] = b;
	grid[0 + y][2 + x] = b;
	grid[0 + y][3 + x] = b;
}
void Grid :: place_I_Veritcal(int x, int y) {
	Shape::Type t = Shape::I;
	Box *b = new Box(t);

	grid[0 + y][0 + x] = b;
	grid[1 + y][0 + x] = b;
	grid[2 + y][0 + x] = b;
	grid[3 + y][0 + x] = b;
}

void Grid :: place_J_Up(int x, int y) {
	Shape::Type t = Shape::J;
	Box *b = new Box(t);

	grid[0 + y][1 + x] = b;
	grid[1 + y][1 + x] = b;
	grid[2 + y][1 + x] = b;
	grid[2 + y][0 + x] = b;
}
void Grid :: place_J_Left(int x, int y) {
	Shape::Type t = Shape::J;
	Box *b = new Box(t);

	grid[0 + y][0 + x] = b;
	grid[0 + y][1 + x] = b;
	grid[0 + y][2 + x] = b;
	grid[1 + y][2 + x] = b;
}
void Grid :: place_J_Down(int x, int y) {
	Shape::Type t = Shape::J;
	Box *b = new Box(t);

	grid[0 + y][0 + x] = b;
	grid[0 + y][1 + x] = b;
	grid[1 + y][0 + x] = b;
	grid[2 + y][0 + x] = b;
}
void Grid :: place_J_Right(int x, int y) {
	Shape::Type t = Shape::J;
	Box *b = new Box(t);

	grid[0 + y][0 + x] = b;
	grid[1 + y][0 + x] = b;
	grid[1 + y][1 + x] = b;
	grid[1 + y][2 + x] = b;
}

void Grid :: place_L_Up(int x, int y) {
	Shape::Type t = Shape::L;
	Box *b = new Box(t);

	grid[0 + y][0 + x] = b;
	grid[1 + y][0 + x] = b;
	grid[2 + y][0 + x] = b;
	grid[2 + y][1 + x] = b;
}
void Grid :: place_L_Left(int x, int y) {
	Shape::Type t = Shape::L;
	Box *b = new Box(t);

	grid[0 + y][2 + x] = b;
	grid[1 + y][0 + x] = b;
	grid[1 + y][1 + x] = b;
	grid[1 + y][2 + x] = b;
}
void Grid :: place_L_Down(int x, int y) {
	Shape::Type t = Shape::L;
	Box *b = new Box(t);

	grid[0 + y][0 + x] = b;
	grid[0 + y][1 + x] = b;
	grid[1 + y][1 + x] = b;
	grid[2 + y][1 + x] = b;
}
void Grid :: place_L_Right(int x, int y) {
	Shape::Type t = Shape::L;
	Box *b = new Box(t);

	grid[0 + y][0 + x] = b;
	grid[1 + y][0 + x] = b;
	grid[0 + y][1 + x] = b;
	grid[0 + y][2 + x] = b;
}

void Grid :: place_O(int x, int y) {
	Shape::Type t = Shape::O;
	Box *b = new Box(t);

	grid[0 + y][0 + x] = b;
	grid[0 + y][1 + x] = b;
	grid[1 + y][0 + x] = b;
	grid[1 + y][1 + x] = b;
}

void Grid :: place_S_Horizontal(int x, int y) {
	Shape::Type t = Shape::S;
	Box *b = new Box(t);

	grid[0 + y][1 + x] = b;
	grid[0 + y][2 + x] = b;
	grid[1 + y][0 + x] = b;
	grid[1 + y][1 + x] = b;
}
void Grid :: place_S_Vertical(int x, int y) {
	Shape::Type t = Shape::S;
	Box *b = new Box(t);

	grid[0 + y][0 + x] = b;
	grid[1 + y][0 + x] = b;
	grid[1 + y][1 + x] = b;
	grid[2 + y][1 + x] = b;
}

void Grid :: place_T_Up(int x, int y) {
	Shape::Type t = Shape::T;
	Box *b = new Box(t);

	grid[0 + y][1 + x] = b;
	grid[1 + y][0 + x] = b;
	grid[1 + y][1 + x] = b;
	grid[1 + y][2 + x] = b;
}
void Grid :: place_T_Left(int x, int y) {
	Shape::Type t = Shape::T;
	Box *b = new Box(t);

	grid[0 + y][1 + x] = b;
	grid[1 + y][1 + x] = b;
	grid[1 + y][0 + x] = b;
	grid[2 + y][1 + x] = b;
}
void Grid :: place_T_Down(int x, int y) {
	Shape::Type t = Shape::T;
	Box *b = new Box(t);

	grid[0 + y][0 + x] = b;
	grid[0 + y][1 + x] = b;
	grid[0 + y][2 + x] = b;
	grid[1 + y][1 + x] = b;
}
void Grid :: place_T_Right(int x, int y) {
	Shape::Type t = Shape::T;
	Box *b = new Box(t);

	grid[0 + y][0 + x] = b;
	grid[0 + y][1 + x] = b;
	grid[1 + y][1 + x] = b;
	grid[1 + y][2 + x] = b;
}

void Grid :: place_Z_Horizontal(int x, int y) {
	Shape::Type t = Shape::Z;
	Box *b = new Box(t);

	grid[0 + y][0 + x] = b;
	grid[0 + y][1 + x] = b;
	grid[1 + y][1 + x] = b;
	grid[1 + y][2 + x] = b;
}
void Grid :: place_Z_Vertical(int x, int y) {
	Shape::Type t = Shape::Z;
	Box *b = new Box(t);

	grid[0 + y][1 + x] = b;
	grid[1 + y][0 + x] = b;
	grid[1 + y][1 + x] = b;
	grid[2 + y][1 + x] = b;
}