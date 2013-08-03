#include "qlandbutton.h"

QLandButton::QLandButton(QWidget *parent)
	: QPushButton(parent)
{
}

void 
QLandButton::mousePressEvent(QMouseEvent *e) 
{
	if (e->button() == Qt::RightButton) {
		emit rightClicked();
	} else if (e->button() == Qt::LeftButton) {
		emit clicked();
	}
}
