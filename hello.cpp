#include <QApplication>
#include <QThread>
#include "Spectre.hpp"
#include "VisuWidget.hpp"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	Spectre	*spectre = new Spectre;
	QThread	*thread = new QThread;
	VisuWidget	widget;
	spectre->moveToThread(thread);
	QObject::connect(thread, SIGNAL (started()), spectre, SLOT (process()));
	QObject::connect(spectre, SIGNAL (newRect(QRect, int)), &widget, SLOT (getRect(QRect, int)));
	QObject::connect(spectre, SIGNAL (update()), &widget, SLOT (update()));

	widget.showFullScreen();
	thread->start();
	return app.exec();
}
