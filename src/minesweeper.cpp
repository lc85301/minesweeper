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
			}
		}
	}
	for (int x = 0; x < m_width; ++x) {
		for (int y = 0; y < m_height; ++y) {
			minemap[x*m_height+y]->m_land = countNum(x, y);
		}
	}
}

//return true if touch a mine
bool
Minesweeper::touchLand(int x, int y)
{
	bool explode = false;
	Pos* land = minemap[x*m_height+y];
	if (!land->m_isFound and land->m_mark != MARK) {
		land->m_isFound = true;
		if (land->m_land == MINE) {
			return true;
		} else if (land->m_land == NONE) {
			expandLand(x, y);
		}
	}
	return false;
}

void
Minesweeper::markLand(int x, int y)
{
	minemap[x*m_height+y]->setMark();
}

void 
Minesweeper::expandLand(int x, int y) 
{
	for (int i = x-1; i <= x+1; ++i) {
		for (int j = y-1; j <= y+1; ++j) {
			if (xy_isValid(i, j)) {
				touchLand(i,j);
			}
		}
	}
}

int Minesweeper::countNum(int x, int y)
{
	int count = 0;
	if (minemap[x*m_height+y]->m_land == MINE) { return MINE; }
	for (int i = x-1; i <= x+1; ++i) {
		for (int j = y-1; j <= y+1; ++j) {
			if (xy_isValid(i, j)) {
				if (minemap[i*m_height+j]->m_land == MINE) {
					++count;
				}
			}
		}
	}
	return count;
}

inline bool
Minesweeper::xy_isValid(int x, int y)
{
	return !(x<0 or x>=m_width or y<0 or y>=m_height);
}
