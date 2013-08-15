#ifndef _SETGAMEDIALOG_H_
#define _SETGAMEDIALOG_H_ value

#include <QDialog>

#include "ui_setGameDialog.h"

class SetGameDialog : public QDialog, public Ui::SetGameDialog {
	Q_OBJECT
public:
	SetGameDialog (QWidget *parent = 0);
	int	m_width;
	int	m_height;
	int	m_mine;
private slots:
	void updateText();
};


#endif /* end of include guard: _SETGAMEDIALOG_H_ */
