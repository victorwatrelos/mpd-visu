#include "VisuWidget.hpp"

VisuWidget::VisuWidget()
{
	QPalette palette(VisuWidget::palette());
	palette.setColor(backgroundRole(), Qt::white);
	palette.setColor(QPalette::Background, Qt::black);
	this->setAutoFillBackground(true);
	this->setPalette(palette);
	this->_nbBar = 0;
	this->_rect.resize(this->_nbBar);
}

VisuWidget::~VisuWidget()
{
}

void	VisuWidget::getRect(QRect rect, int col)
{
	if (this->_rect.size() < col + 1)
		this->_rect.resize(col + 10);
	if (this->_nbBar < col)
		this->_nbBar = col;
	this->_rect[col] = rect;
}

void VisuWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	QBrush brush(Qt::red, Qt::SolidPattern);

	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::darkGreen);
	for (int i = 0; i < this->_nbBar; i++)
	{
		painter.drawRect(this->_rect[i]);
		painter.fillRect(this->_rect[i], brush);
	}
}
