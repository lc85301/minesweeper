#include <QtGui>

#include <stdio.h>

#include "mainwindow.h"
#include "setGameDialog.h"

MainWindow::MainWindow()
{
	//create the view
	createActions();
	createMenus();
	createObject();
	createStatusBar();

	setWindowIcon(QIcon(":/images/icon.png"));

	//create the minesweeper
	m_minesweeper = NULL;
	m_setgamedialog = NULL;
	m_isPause = false;
}

void 
MainWindow::createActions() 
{
	//File menu action 
	m_newAction = new QAction(tr("&new"), this);
	m_newAction->setShortcut(tr("F2"));
	m_newAction->setStatusTip(tr("Start a new game"));
	connect(m_newAction, SIGNAL(triggered()),
			this, SLOT(setGame()));
	
	m_closeAction = new QAction(tr("&close"), this);
	m_closeAction->setShortcut(tr("Ctrl+Q"));
	m_closeAction->setStatusTip(tr("Exit minesweeper"));
	connect(m_closeAction, SIGNAL(triggered()),
			this, SLOT(closeGame()));

	m_pauseAction = new QAction(tr("&pause"), this);
	m_pauseAction->setShortcut(tr("F3"));
	m_pauseAction->setStatusTip(tr("Pause the game"));
	connect(m_pauseAction, SIGNAL(triggered()),
			this, SLOT(pauseGame()));

	m_recordAction = new QAction(tr("&highscore"), this);
	m_recordAction->setStatusTip(tr("See highscore"));
	connect(m_closeAction, SIGNAL(triggered()),
			this, SLOT(showRecord()));

	//Help menu actions
	m_aboutAction = new QAction(tr("&about"), this);
	m_aboutAction->setShortcut(tr("F1"));
	m_aboutAction->setStatusTip(tr("About the game"));
	connect(m_aboutAction, SIGNAL(triggered()),
			this, SLOT(aboutGame()));
}

void 
MainWindow::closeEvent(QCloseEvent *event)
{
	event->accept();
}

void 
MainWindow::createMenus() 
{
	m_fileMenu = menuBar()->addMenu(tr("&Game"));
	m_fileMenu->addAction(m_newAction);
	m_fileMenu->addAction(m_pauseAction);
	m_fileMenu->addAction(m_recordAction);
	m_separateAction = m_fileMenu->addSeparator();
	m_fileMenu->addAction(m_closeAction);

	m_helpMenu = menuBar()->addMenu(tr("help"));
	m_helpMenu->addAction(m_aboutAction);
}

void 
MainWindow::createStatusBar() 
{
	m_mineLabel = new QLabel(QString("mine founded: 0/%1").arg(m_minenum), this);
	m_mineLabel->setAlignment(Qt::AlignHCenter);
	m_mineLabel->setMinimumSize(m_mineLabel->sizeHint());

	m_timeLabel = new QLabel("0", this);

	statusBar()->addWidget(m_mineLabel);
	statusBar()->addWidget(m_timeLabel);
};

void 
MainWindow::createObject() 
{
	// signal mapper
	m_leftSignalMapper = new QSignalMapper(this);
	m_rightSignalMapper = new QSignalMapper(this);
	connect(m_leftSignalMapper, SIGNAL(mapped(int)), this, SLOT(clickLeftButton(int)));
	connect(m_rightSignalMapper, SIGNAL(mapped(int)), this, SLOT(clickRightButton(int)));
	// timer
	m_time = 0;
	m_timer = new QTimer();
	connect(m_timer, SIGNAL(timeout()), 
			this, SLOT(timeOut()));
}

void 
MainWindow::setGame() 
{
	if (okToContinue()) {
		SetGameDialog dialog(this);
		if (dialog.exec()) {
			m_width = dialog.m_width;
			m_height = dialog.m_height;
			m_minenum = dialog.m_mine;
			newGame();
		}
	}
}

void
MainWindow::newGame()
{
	m_minesweeper = new Minesweeper(m_width, m_height, m_minenum);
	m_land = new QLandButton*[m_width*m_height];
	//create layout
	m_window = new QWidget(this);
	QHBoxLayout* row = new QHBoxLayout;
	row->setSpacing(0);
	row->setMargin(0);
	row->setContentsMargins(0,0,0,0);
	for (int x = 0; x < m_width; ++x) {
		QVBoxLayout* column = new QVBoxLayout;
		column->setSpacing(0);
		column->setMargin(0);
		column->setContentsMargins(0,0,0,0);
		for (int y = 0; y < m_height; ++y) {
			m_land[x*m_height+y] = new QLandButton(m_window);
			m_land[x*m_height+y] ->setIcon(QIcon(":/images/null.png"));
			m_land[x*m_height+y] ->setIconSize(QSize(10,10));
			m_leftSignalMapper->setMapping(m_land[x*m_height+y], x*m_height+y);
			m_rightSignalMapper->setMapping(m_land[x*m_height+y], x*m_height+y);
			connect(m_land[x*m_height+y], SIGNAL(clicked()),
					m_leftSignalMapper, SLOT(map()));
			connect(m_land[x*m_height+y], SIGNAL(rightClicked()),
					m_rightSignalMapper, SLOT(map()));
			column->addWidget(m_land[x*m_height+y]);
		}
		row->addLayout(column);
	}
	m_window->setLayout(row);
	setCentralWidget(m_window);
	updateView();
}

void
MainWindow::pauseGame()
{
	if (m_time != (float)0.0) {
		m_isPause = !m_isPause;
		timeOut();
	}
}
void
MainWindow::stopGame()
{
	m_timer->stop();
	m_window->deleteLater();
}

void
MainWindow::closeGame()
{
}

bool
MainWindow::okToContinue() 
{
	if (m_minesweeper != NULL && m_time != (float)0.0) {
		if (!m_isPause) { pauseGame(); }
		int r = QMessageBox::warning(
			this, tr("minesweeper"), tr("The game has been started. Do you want to restart another round?"),
			QMessageBox::Yes | QMessageBox::No);
		if (r == QMessageBox::Yes) {
			if (m_minesweeper != NULL) { delete m_minesweeper; }
			return true;
		} else {
			return false;
		}
	}
	return true;
}

void
MainWindow::showRecord()
{
}
void
MainWindow::saveRecord()
{
}

void
MainWindow::updateView()
{
	//update map layout
	int i = 0;
	for (iter pos = m_minesweeper->begin(); pos != m_minesweeper->end(); ++pos) {
		if (m_isPause) {
			m_land[i]->setIcon(QIcon(":/images/null.png"));
		} else {
			switch((*pos)->m_mark){
			  case QUESTION:
				m_land[i]->setIcon(QIcon(":/images/q.png"));
				break;
			  case MARK:
				m_land[i]->setIcon(QIcon(":/images/flag.png"));
				break;
			  default: 
				if (!((*pos)->m_isFound)) {
					m_land[i]->setIcon(QIcon(":/images/null.png"));
				} else {
					int landType = (*pos)->m_land;
					if (landType == MINE) {
						m_land[i]->setIcon(QIcon(tr(":/images/icon.png")));
					} else {
						m_land[i]->setIcon(QIcon(tr(":/images/%1.png").arg(landType)));
					}

				}
				break;
			}
		}
		++i;
	}
}

void 
MainWindow::updateLabel() 
{
	int i = 0;
	for (iter pos = m_minesweeper->begin(); pos != m_minesweeper->end(); ++pos) {
		if ((*pos)->m_mark == MARK) { ++i; }
	}
	m_mineLabel->setText(QString("mine founded: %1/%2").arg(m_minenum-i).arg(m_minenum));
}

void
MainWindow::aboutGame()
{
	QMessageBox::about(this, tr("About Minesweeper"),
			tr("<h2>Minesweeper 0.9</h2>"
			   "<p>Copyright &copy; 2013 Yodalee"
			   "<p>Minesweeper is a first view minesweeper game"
			   " wish you like it"));
}

void 
MainWindow::clickLeftButton(int index)
{
	printf("Left Click: %d\n", index);
	if (!m_timer->isActive()) { m_timer->start(TIMEINTERVAL); }
	//call minesweeper
	statusType status = m_minesweeper->touchLand(index/m_height, index%m_height);
	switch(status){
	  case statusMINE:
		  printf("This is a mine, BOOM!\n");
		  stopGame();
	      break;
	  case statusEND:
		  printf("You WIN =w=b\n");
		  stopGame();
		  break;
	}
	updateView();
}

void 
MainWindow::clickRightButton(int index)
{
	printf("Right Click: %d\n", index);
	if (!m_timer->isActive()) { m_timer->start(TIMEINTERVAL); }
	//call minesweeper
	m_minesweeper->markLand(index/m_height, index%m_height);
	updateView();
	updateLabel();
}

void 
MainWindow::timeOut() 
{
	if (m_isPause) { return; }
	m_time += (float)TIMEINTERVAL/1000;
	m_timeLabel->setText(QString("%1").arg(m_time));
	m_timer->start(TIMEINTERVAL);
}
