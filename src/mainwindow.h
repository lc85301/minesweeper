#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_ value

#include <QMainWindow>
#include "minesweeper.h"
#include "qlandbutton.h"

#define TIMEINTERVAL 100

class QAction;
class QLabel;
class QSignalMapper;
class SetGameDialog;

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow();
protected:
	void closeEvent(QCloseEvent *event);
private slots:
	void setGame();
	void newGame();
	void pauseGame();
	void closeGame();
	void showRecord();
	void saveRecord();
	void aboutGame();
	void clickLeftButton(int index);
	void clickRightButton(int index);
	void timeOut();
private:
	void createActions();
	void createMenus();
	void createStatusBar();
	void createObject();
	void updateView();
	void updateLabel();
	void stopGame();
private:
	float m_time;
	int m_width;
	int m_height;
	int m_minenum;
	bool m_isPause;
	Minesweeper *m_minesweeper;
	SetGameDialog *m_setgamedialog;
	QWidget *m_window;
	QSignalMapper *m_leftSignalMapper;
	QSignalMapper *m_rightSignalMapper;
	QMenu  *m_fileMenu;
	QMenu  *m_helpMenu;
	QAction *m_newAction;
	QAction *m_pauseAction;
	QAction *m_recordAction;
	QAction *m_closeAction;
	QAction *m_aboutAction;
	QAction *m_separateAction;
	QLabel *m_mineLabel;
	QLabel *m_timeLabel;
	QLandButton **m_land;
	QTimer *m_timer;
};
#endif /* end of include guard: _MAINWINDOW_H_ */
