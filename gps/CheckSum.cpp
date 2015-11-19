#include <QtCore/QDebug>

#include "CheckSum.h"

namespace Core
{
	namespace Gps
	{
		CheckSum::CheckSum (QObject *parent)
			: QObject (parent)
		{
		}
		
		CheckSum::~CheckSum ()
		{
		}
		
		bool CheckSum::isCheckSumMatch (const QString data, const QString expectedCheckSum)
		{
			return (formattedCheckSum (data) == expectedCheckSum);
		}
		
		quint16 CheckSum::checkSum (const QString data)
		{
			quint16 result = 0;
			for (const QChar character : data) {
				result ^= character.toAscii ();
			}
			return result;
		}
		
		QString CheckSum::formattedCheckSum (const QString data)
		{
			return stringedCheckSum (checkSum (data));
		}
		
		
		QString CheckSum::stringedCheckSum (quint16 checksum)
		{
			constexpr int checksumWidth = 2;
			constexpr int checksumBase = 16;
			QLatin1Char filler ('0');
			return QString ("%1").arg (checksum, checksumWidth, checksumBase, filler).toUpper();
		}
	}
}
