#include "SentenceCommon.h"

#include <QtCore/QDebug>
#include <QtCore/QString>

namespace Core
{
	namespace Gps
	{
		qint32 coordinateInteger (bool isLatitude, const QString &coordinate)
		{
			bool isDoubled = false;
			const qint32 result = coordinate.toDouble (&isDoubled) * COORDINATE_DOUBLE_TO_INTEGER_MULTIPLIER;
			if (!isDoubled) {
				qWarning () << "SentenceCommon:" << QString ("%1 QString --> double conversion error")
													.arg (isLatitude ? "latitude" : "longitude");
			}
			return result;
		}
	}
}
