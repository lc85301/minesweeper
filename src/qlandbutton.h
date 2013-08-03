#ifndef _QLANDBUTTON_H_
#define _QLANDBUTTON_H_ value

#include <QPushButton>
#include <QMouseEvent>

class QLandButton : public QPushButton
{
	Q_OBJECT
public:
	explicit QLandButton(QWidget *parent = 0);
private slots:
	void mousePressEvent(QMouseEvent *e);
signals:
	void rightClicked();
	void clicked();
};

#endif /* end of include guard: _QLANDBUTTON_H_ */
