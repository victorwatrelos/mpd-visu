#include <QApplication>
#include <QLabel>


int main(int argc, char **argv) {
	QApplication app(argc, argv);
	QLabel label("Hello, world!");
	label.showFullScreen();
	label.show();
	return app.exec();
}
