#ifndef _POS_H_
#define _POS_H_ value
enum markType {NOMARK, MARK, QUESTION};
const int MINE=9;
const int NONE=0;

class Pos {
public:
	Pos(){ 
		m_isFound = false;
		m_land = NONE;
		m_mark = NOMARK;
	}
	void setMark(){
		switch(m_mark){
		  case NOMARK:
			  m_mark = MARK;
		      break;
		  case MARK:
			  m_mark = QUESTION;
			  break;
		  case QUESTION:
			  m_mark = NOMARK;
			  break;
		}
	}
	int m_land;
	bool m_isFound;
	enum markType m_mark;
private:
};

class PosMine : public Pos {
public:
	PosMine(): Pos(){ 
		m_land = MINE;
	};
};

class PosLand : public Pos {
public:
	PosLand(): Pos(){
		m_land = NONE;
	}
};
#endif /* end of include guard: _POS_H_ */
