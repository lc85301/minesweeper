#ifndef _MINESWEEPER_H_
#define _MINESWEEPER_H_

#include <vector>
using namespace std;

#include "pos.h"

class Minesweeper {
public:
	Minesweeper (int width, int height, int num);
	void init(int width, int height, int num);
	void initMap();
	void touchLand(int x, int y);
	void markLand (int x, int y);

	typedef vector<Pos>::const_iterator iter;
private:
	int countNum(int x, int y);
private:
	int m_width;
	int m_height;
	int m_mineNum;
	vector<Pos*> minemap;
};
#endif /* end of include guard: _MINESWEEPER_H_ */
