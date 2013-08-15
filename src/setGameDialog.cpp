#include <QtGui>

#include "setGameDialog.h"

SetGameDialog::SetGameDialog(QWidget* parent)
	: QDialog(parent)
{
	setupUi(this);
	connect(m_easyButton, SIGNAL(clicked()), 
			this, SLOT(updateText()));
	connect(m_normalButton, SIGNAL(clicked()), 
			this, SLOT(updateText()));
	connect(m_hardButton, SIGNAL(clicked()), 
			this, SLOT(updateText()));
	connect(okButton, SIGNAL(clicked()),
			this, SLOT(accept()));
	connect(cancelButton, SIGNAL(clicked()),
			this, SLOT(reject()));
	m_easyButton->setChecked(true);
	updateText();
}

void 
SetGameDialog::updateText() 
{
	int setting[3][3] = { {8,8,10},{16,16,40},{30,16,99} };
	if (m_easyButton->isChecked()) {
		m_width = setting[0][0];
		m_height= setting[0][1];
		m_mine  = setting[0][2];
	}
	if (m_normalButton->isChecked()) {
		m_width = setting[1][0];
		m_height= setting[1][1];
		m_mine  = setting[1][2];
	}
	if (m_hardButton->isChecked()) {
		m_width = setting[2][0];
		m_height= setting[2][1];
		m_mine  = setting[2][2];
	}
	m_labelWidth->setText(QString("%1").arg(m_width));
	m_labelHeight->setText(QString("%1").arg(m_height));
	m_labelMine->setText(QString("%1").arg(m_mine));
}
