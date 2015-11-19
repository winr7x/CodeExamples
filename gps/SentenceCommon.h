#include <QtCore/QtGlobal>

namespace Core
{
	namespace Gps
	{
		const double COORDINATE_DOUBLE_TO_INTEGER_MULTIPLIER = 1E+5;

		qint32 coordinateInteger (bool isLatitude, const QString &coordinate);
	}
}
