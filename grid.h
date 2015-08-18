#ifndef GRID_H
#define GRID_H

#include "box.h"
#include "shape.h"
#include "painter.h"

class Grid {
public:
	enum { WIDTH = 10, HEIGHT = 22 };

	Grid();
	~Grid();

	Box * getBoxAtLocation(int x, int y);
	
	Box::Color getBoxColor(Box *box);

	
	bool isGameOver();
	
	void tick();

	void shiftLeft();
	void shiftRight();

	void rotateLeft();
	void rotateRight();

private:
	Box *grid[HEIGHT][WIDTH];
	Box *clear;

	Shape currentShape;

	struct {
		int x, y;
	} shapeOrigin;

	bool collision;

	bool isRowComplete(int row);

	void genShape();

	void deleteCompletedRows();
	void dropRow(int row);

	void draw(Painter p);

	void place_I_Horizontal(int x, int y);
	void place_I_Veritcal(int x, int y);

	void place_J_Up(int x, int y);
	void place_J_Left(int x, int y);
	void place_J_Down(int x, int y);
	void place_J_Right(int x, int y);

	void place_L_Up(int x, int y);
	void place_L_Left(int x, int y);
	void place_L_Down(int x, int y);
	void place_L_Right(int x, int y);

	void place_O(int x, int y);

	void place_S_Horizontal(int x, int y);
	void place_S_Vertical(int x, int y);

	void place_T_Up(int x, int y);
	void place_T_Left(int x, int y);
	void place_T_Down(int x, int y);
	void place_T_Right(int x, int y);

	void place_Z_Horizontal(int x, int y);
	void place_Z_Vertical(int x, int y);
};

#endif