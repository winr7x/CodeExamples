#include <QtCore/QSize>

#include <QtGui/QGraphicsScene>
#include <QtGui/QSpinBox>

#include <cstdlib>

#include "Axes.h"

int main(int argc, char *argv[])
{
	Q_UNUSED (argc)
	Q_UNUSED (argv)

	QGraphicsScene scene;
	QSize size;
	QSpinBox box1;
	QSpinBox box2;

	Axes axes (scene, size, box1, box2);

	return EXIT_SUCCESS;
}
