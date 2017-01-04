#ifndef VISU_WIDGET_HPP
# define VISU_WIDGET_HPP

#include <QPainter>
#include <QWidget>

class VisuWidget : public QWidget
{
	Q_OBJECT
	public:
		VisuWidget();
		~VisuWidget();
	public slots:
		void	getRect(QRect rect, int col);
	protected:
		void 	paintEvent(QPaintEvent *);
		int		_nbBar;
		std::vector<QRect>	_rect;
};

#endif
