#include <stdlib.h>
#include "myLib.h"
#include "text.h"
#include "game.h"
#include "images.h"

int obstSize = 0;

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	
	player pl = {0, 0, 0, 0, 5, 5, 0, 1, 0};
	
	while(1)
	{
		int frame = 0;
		int timer = 0;
		while(!KEY_DOWN_NOW(BUTTON_START))
		{
			waitForVblank();
			if (frame < 40) drawImage3(0, 0, 240, 160, g1);
			else if (frame < 80) drawImage3(0, 0, 240, 160, g2);
			else if (frame < 120) drawImage3(0, 0, 240, 160, g3);
			else if (frame < 160) drawImage3(0, 0, 240, 160, g4);
			else frame = -1;
			drawString(130, 30, "PRESS START", YELLOW);
			frame++;
			timer++;
		}
		srand(timer);
		fillScreen(BLACK);
		pl.row = 130;
		pl.col = 0;
		
		pl.gravity = 1;
		pl.grounded = 1;

		recObst r1 = {0, 0, 240, 10, 0, 0, 0, 0, 0, 0, RED};
		recObst r2 = {140, 0, 240, 10, 0, 0, 0, 0, 0, 0, RED};
		
		obstacles[0] = r1;
		obstacles[1] = r2;
		obstSize = 2;

		int score = 0;
		int alive = 1;
		while(alive) 
		{
			score++;
			pl.oldRow = pl.row;
			pl.oldCol = pl.col;

			if(KEY_DOWN_NOW(BUTTON_UP))
			{
				if (pl.grounded) 
				{
					pl.gravity = -1;
					pl.grounded = 0;
				}
			}
			if(KEY_DOWN_NOW(BUTTON_DOWN))
			{
				if (pl.grounded)
				{
					pl.gravity = 1;
					pl.grounded = 0;
				} 
			}

			int hasCollided = 0;
			
			int rowBottom = (pl.row + pl.height / 2 - 1) + (pl.gravity * (pl.height / 2 + 2));
			
			for(int i = 0; i < obstSize; i++)
			{
				recObst * obs = obstacles + i;
				
				if (checkCollision(pl.row, pl.col, pl.width, pl.height, obs->row, obs->col, obs->width, obs->height))
				{
					alive = 0;
					continue;
				}
				if (obs->xMove != 0)
				{	
					if (obs->col + obs->width - 1 >= obs->xLimit2 || obs->col <= obs->xLimit1) obs->xMove = -obs->xMove;
					obs->col += obs->xMove;
				}
				if (obs->yMove != 0)
				{	
					if (obs->row + obs->height - 1 >= obs->yLimit2 || obs->row <= obs->yLimit1) obs->yMove = -obs->yMove;
					obs->row += obs->yMove;
				}
				if (checkCollision(rowBottom, pl.col, pl.width, 3, obs->row, obs->col, obs->width, obs->height))
				{
					pl.grounded = 1;
					hasCollided = 1;
					if (pl.gravity == -1) pl.row = obs->row + obs->height;
					else pl.row = obs->row - pl.height;
				}
				
			}
			
			if (!(hasCollided))
			{
				pl.grounded = 0;
				pl.row += pl.gravity * 3;
			}


			if (pl.col + pl.width - 1 >= 239)
			{
				pl.col = 0;	
				fillScreen(BLACK);
				generateObstacles();		
			}
			else
			{
				pl.col++;
			}

			if (pl.row <= 0 || pl.row + pl.height - 1 >= 149)
			{
				alive = 0;
				continue;
			}

			waitForVblank();
			for(int i = 0; i < obstSize; i++)
			{
				recObst * rec = obstacles + i;
				if (rec->xMove != 0 || rec->yMove != 0)
				{
					drawRect(rec->row - rec->yMove, rec->col - rec->xMove, rec->width, rec->height, BLACK);
				}
			}
			for(int i = 0; i < obstSize; i++)
			{
				recObst * rec = obstacles + i;
				drawRect(rec->row, rec->col, rec->width, rec->height, rec->color);
			}
			drawRect(pl.oldRow, pl.oldCol, pl.width, pl.height, BLACK);
			if (pl.frame >= 10)
			{
				drawInvertedImage3(pl.row, pl.col, pl.width, pl.height, player1, -pl.gravity);
			}
			else 
			{
				drawInvertedImage3(pl.row, pl.col, pl.width, pl.height, player2, -pl.gravity);
			}
			drawRect(150, 0, 240, 10, GRAY);
			drawString(152, 3, "SCORE: ", BLUE);
			drawNum(152, 38, score, BLUE);

			if (pl.frame >= 20)
			{
				pl.frame = 0;
			}
			else
			{
				pl.frame++;
			}
		} 
		fillScreen(BLACK);
		drawImage3(0, 0, 240, 160, gg);
		drawRect(150, 0, 240, 10, GRAY);
		drawString(152, 3, "SCORE: ", BLUE);
		drawNum(152, 38, score, BLUE);
		while(!KEY_DOWN_NOW(BUTTON_START));
		volatile int wait = 0;
		while (wait <= 50000)
		{
			wait++;
		}
		fillScreen(BLACK);

	}

}  


