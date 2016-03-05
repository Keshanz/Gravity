typedef struct 
{
	int row;
	int col;
	int width;
	int height;
	int xMove;
	int xLimit1;
	int xLimit2;
	int yMove;
	int yLimit1;
	int yLimit2;
	unsigned short color;
} recObst;

typedef struct 
{
	int row;
	int col;
	int oldRow;
	int oldCol;
	const int width;
	const int height;
	int frame;
	int gravity;
	int grounded;	
} player;

recObst obstacles[10];

extern recObst obstacles[10];
extern int obstSize;

int checkCollision(int row1, int col1, int width1, int height1, int row2, int col2, int width2, int height2);
void generateObstacles();
