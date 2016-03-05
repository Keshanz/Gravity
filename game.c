#include "game.h"
#include "myLib.h"
#include <stdlib.h>

//check collision of two rectangles
int checkCollision(int row1, int col1, int width1, int height1, int row2, int col2, int width2, int height2)
{
	return (col1 <= col2 + width2 - 1 && col1 + width1 - 1 >= col2 && row1 <= row2 + height2 - 1 && row1 + height1 - 1 >= row2);
}

//randomly generate obstacles on the field
void generateObstacles()
{
	int r = rand() % 100;
	if (r < 20)
	{
		recObst r1 = {0, 0, 90, 10, 0, 0, 0, 0, 0, 0, BLUE};
		recObst r2 = {0, 150, 90, 10, 0, 0, 0, 0, 0, 0, BLUE};
		recObst r3 = {70, 90, 60, 10, 0, 0, 0, 0, 0, 0, BLUE};
		recObst r4 = {140, 0, 90, 10, 0, 0, 0, 0, 0, 0, BLUE};
		recObst r5 = {140, 150, 90, 10, 0, 0, 0, 0, 0, 0, BLUE};
		obstacles[0] = r1;
		obstacles[1] = r2;
		obstacles[2] = r3;
		obstacles[3] = r4;
		obstacles[4] = r5;
		obstSize = 5;
	}
	else if (r < 30)
	{
		recObst r1 = {0, 0, 240, 10, 0, 0, 0, 0, 0, 0, WHITE};
		recObst r2 = {140, 0, 240, 10, 0, 0, 0, 0, 0, 0, WHITE};
		recObst r3 = {11 + (rand() % 70), 30 + (rand() % 150), 50, 50, 1, 0, 240, 1, 10, 139, WHITE};
		recObst r4 = {11 + (rand() % 70), 30 + (rand() % 150), 50, 50, 1, 0, 240, -1, 10, 139, WHITE};
		
		obstacles[0] = r1;
		obstacles[1] = r2;
		obstacles[2] = r3;
		obstacles[3] = r4;
		obstSize = 4;
	}
	else if (r < 40)
	{
		recObst r1 = {0, 0, 240, 10, 0, 0, 0, 0, 0, 0, RED};
		recObst r2 = {140, 0, 240, 10, 0, 0, 0, 0, 0, 0, RED};
		recObst r3 = {(rand() % 60) + 11, 90, 10, 65, 0, 0, 0, -1, 10, 139, RED};
		recObst r4 = {(rand() % 60) + 11, 180, 10, 65, 0, 0, 0, 1, 10, 139, RED};
		obstacles[0] = r1;
		obstacles[1] = r2;
		obstacles[2] = r3;
		obstacles[3] = r4;
		obstSize = 4;
	}
	else if (r < 50)
	{
		recObst r1 = {0, 0, 240, 10, 0, 0, 0, 0, 0, 0, MAGENTA};
		recObst r2 = {140, 0, 240, 10, 0, 0, 0, 0, 0, 0, MAGENTA};
		recObst r3 = {70, 70, 170, 10, 0, 0, 0, 0, 0, 0, MAGENTA};
		recObst r4 = {(rand() % 2) * 75, 230, 10, 75, 0, 0, 0, 0, 0, 0, MAGENTA};
		
		obstacles[0] = r1;
		obstacles[1] = r2;
		obstacles[2] = r3;
		obstacles[3] = r4;
		obstSize = 4;
	}
	else if (r < 65)
	{
		recObst r1 = {0, 0, 240, 10, 0, 0, 0, 0, 0, 0, CYAN};
		recObst r2 = {140, 0, 240, 10, 0, 0, 0, 0, 0, 0, CYAN};
		int ra = 3 + (rand() % 84); 
		recObst r3 = {10, 100, 100, ra, 0, 0, 0, 0, 0, 0, CYAN};
		recObst r4 = {ra + 50, 100, 100, 90 - ra, 0, 0, 0, 0, 0, 0, CYAN};
		obstacles[0] = r1;
		obstacles[1] = r2;
		obstacles[2] = r3;
		obstacles[3] = r4;
		obstSize = 4;
	}
	else if (r < 80)
	{
		recObst r1 = {0, 0, 240, 10, 0, 0, 0, 0, 0, 0, YELLOW};
		recObst r2 = {140, 0, 240, 10, 0, 0, 0, 0, 0, 0, YELLOW};
		recObst r3 = {10, 70 + (rand() % 80), 50, 20, -1, 0, 240, 0, 0, 0, YELLOW};
		recObst r4 = {120, 70 + (rand() % 80), 50, 20, -1, 0, 240, 0, 0, 0, YELLOW};
		
		obstacles[0] = r1;
		obstacles[1] = r2;
		obstacles[2] = r3;
		obstacles[3] = r4;
		obstSize = 4;
	}
	else if (r < 95)
	{
		recObst r1 = {0, 0, 40, 10, 0, 0, 0, 0, 0, 0, GREEN};
		recObst r2 = {0, 200, 40, 10, 0, 0, 0, 0, 0, 0, GREEN};
		recObst r3 = {140, 0, 40, 10, 0, 0, 0, 0, 0, 0, GREEN};
		recObst r4 = {140, 200, 40, 10, 0, 0, 0, 0, 0, 0, GREEN};
		recObst r5 = {40, 90, 100, 10, -1, 30, 210, 0, 0, 0, GREEN};
		recObst r6 = {100, 90, 100, 10, 1, 30, 210, 0, 0, 0, GREEN};

		obstacles[0] = r1;
		obstacles[1] = r2;
		obstacles[2] = r3;
		obstacles[3] = r4;
		obstacles[4] = r5;
		obstacles[5] = r6;
		obstSize = 6;
	}
	else
	{
		recObst r1 = {0, 0, 240, 10, 0, 0, 0, 0, 0, 0, RED};
		recObst r2 = {140, 0, 240, 10, 0, 0, 0, 0, 0, 0, RED};
		
		obstacles[0] = r1;
		obstacles[1] = r2;
		obstSize = 2;
	}
}