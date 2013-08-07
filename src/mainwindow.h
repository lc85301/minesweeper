#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_ value

#include <QMainWindow>
#include "minesweeper.h"
#include "qlandbutton.h"

class QAction;
class QLabel;
class QSignalMapper;

const int g_width = 10;
const int g_height = 10;
const int g_minenum = 8;

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow();
protected:
	void closeEvent(QCloseEvent *event);
private slots:
	void newGame();
	void pauseGame();
	void closeGame();
	void showRecord();
	void saveRecord();
	void aboutGame();
	void clickLeftButton(int index);
	void clickRightButton(int index);
private:
	void createActions();
	void createMenus();
	void createStatusBar();
	void createSignalMapper();
	void updateView();
private:
	Minesweeper *m_minesweeper;
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
};
#endif /* end of include guard: _MAINWINDOW_H_ */
