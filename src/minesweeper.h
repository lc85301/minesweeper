#ifndef _MINESWEEPER_H_
#define _MINESWEEPER_H_

#include <vector>
using namespace std;

#include "pos.h"
typedef vector<Pos*>::iterator iter;

enum statusType {statusMINE, statusEND, statusNONE};

class Minesweeper {
public:
	Minesweeper (int width, int height, int num);
	void init(int width, int height, int num);
	void initMap();
	statusType touchLand(int x, int y);
	void markLand (int x, int y);
	void expandLand(int x, int y);

	bool xy_isValid(int x, int y);
	//typedef vector<Pos*>::const_iterator iter;
	iter begin(){ return minemap.begin();}
	iter end(){ return minemap.end();}
private:
	int countNum(int x, int y);
public:
	int m_width;
	int m_height;
	int m_mineNum;
	int m_numOpen;
private:
	vector<Pos*> minemap;
};
#endif /* end of include guard: _MINESWEEPER_H_ */
