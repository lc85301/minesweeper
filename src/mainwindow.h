#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_ value

#include <QMainWindow>

class QAction;
class QLabel;

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
private:
	void createActions();
	void createMenus();
	void createStatusBar();
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
};
#endif /* end of include guard: _MAINWINDOW_H_ */
