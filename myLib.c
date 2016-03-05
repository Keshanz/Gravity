
#include "myLib.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;

void setPixel(int row, int col, unsigned short color)
{
	videoBuffer[OFFSET(row, col, 240)] = color;
}

void drawRect(int row, int col, int width, int height, unsigned short color)
{
	int r;
	for(r = 0; r < height; r++)
	{
		DMA[3].src = &color;
		DMA[3].dst = &videoBuffer[OFFSET(row + r, col, 240)];
		DMA[3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
	}
}

void drawImage3(int row, int col, int width, int height, const unsigned short * image)
{
	int r;
	for(r = 0; r < height; r++)
	{
		DMA[3].src = image + (r * width);
		DMA[3].dst = &videoBuffer[OFFSET(row + r, col, 240)];
		DMA[3].cnt = width | DMA_ON | DMA_SOURCE_INCREMENT;
	}
}

void drawInvertedImage3(int row, int col, int width, int height, const unsigned short * image, int invert)
{
	
	if (invert == 1)
	{
		int r;
		for(r = height; r > 0; r--)
		{
			DMA[3].src = image + (r * width) - 1;
			DMA[3].dst = &videoBuffer[OFFSET(row + (height - r), col, 240)];
			DMA[3].cnt = width | DMA_ON | DMA_SOURCE_DECREMENT;
		}
	}
	else
	{
		drawImage3(row, col, width, height, image);
	}
}

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

void fillScreen(volatile unsigned short color)
{
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 38400 | DMA_ON | DMA_SOURCE_FIXED; 
}


