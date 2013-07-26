#include <QtGui>

#include "mainwindow.h"

MainWindow::MainWindow()
{
	createActions();
	createMenus();
	createStatusBar();

	setWindowIcon(QIcon(":/images/icon.png"));
}

void 
MainWindow::createActions() 
{
	//File menu action 
	m_newAction = new QAction(tr("&new"), this);
	m_newAction->setShortcut(tr("F2"));
	m_newAction->setStatusTip(tr("Start a new game"));
	connect(m_newAction, SIGNAL(triggered()),
			this, SLOT(newGame()));
	
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
	m_mineLabel = new QLabel("xxxx xxxxxx: www/www");
	m_mineLabel->setAlignment(Qt::AlignHCenter);
	m_mineLabel->setMinimumSize(m_mineLabel->sizeHint());

	m_timeLabel = new QLabel;

	statusBar()->addWidget(m_mineLabel);
	statusBar()->addWidget(m_timeLabel);
};

void MainWindow::newGame(){}
void MainWindow::pauseGame(){}
void MainWindow::closeGame(){}
void MainWindow::showRecord(){}
void MainWindow::saveRecord(){}

void
MainWindow::aboutGame()
{
	QMessageBox::about(this, tr("About Minesweeper"),
			tr("<h2>Minesweeper 0.9</h2>"
			   "<p>Copyright &copy; 2013 Yodalee"
			   "<p>Minesweeper is a first view minesweeper game"
			   " wish you like it"));
}
