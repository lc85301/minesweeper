#include <stdlib.h>
#include <stdio.h>
#include "minesweeper.h"

Minesweeper::Minesweeper(int width, int height, int num)
{
	init(width, height, num);
}

//********************************************
// Function: init
// Description: initial width, height, number, and mine vector
//********************************************
void
Minesweeper::init(int width, int height, int num)
{
	if (width*height < num) 
	{
		exit(1);
	}
	m_width = width;
	m_height = height;
	m_mineNum = num;
	minemap.reserve(width*height);
	initMap();
}

void
Minesweeper::initMap()
{
	int x;
	int y;
	for (int x = 0; x < m_width; ++x) {
		for (int y = 0; y < m_height; ++y) {
			minemap.push_back(NULL);
		}
	}
	for (int i = 0; i < m_mineNum; ++i) {
		while (true) {
			x = rand() % m_width;
			y = rand() % m_height;
			if (minemap[x*m_height+y] == NULL) { break; }
		}
		minemap[x*m_height+y] = new PosMine;
	}
	for (int x = 0; x < m_width; ++x) {
		for (int y = 0; y < m_height; ++y) {
			if (minemap[x*m_height+y] == NULL) {
				minemap[x*m_height+y] = new PosLand;
				minemap[x*m_height+y]->m_land = countNum(x, y);
			}
		}
	}
}

void
Minesweeper::touchLand(int x, int y)
{
	Pos* land = minemap[x*m_height+y];
	if (!land->m_isFound and land->m_mark != MARK) {
		land->m_isFound = true;
		if (land->m_land == MINE) {
			printf("You are DEAD\n");
		}
	}
}

void
Minesweeper::markLand(int x, int y)
{
	Pos* land = minemap[x*m_height+y];
	land->setMark();
}

int Minesweeper::countNum(int x, int y)
{
	int count = 0;
	for (int i = x-1; i <= x+1; ++i) {
		for (int j = y-1; j <= y+1; ++j) {
			if (i<0 or i>=m_width or j<0 or j>=m_height) {
				break;
			} else {
				if (minemap[i*m_height+j]->m_land == MINE) {
					++count;
				}
			}
		}
	}
	return count;
}
