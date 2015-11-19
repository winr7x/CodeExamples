#pragma once

#include <QtCore/QObject>

namespace Core
{
	namespace Gps
	{
		class CheckSum : public QObject
		{
			Q_OBJECT
		
		public:
			explicit CheckSum (QObject *parent = 0);
			~CheckSum ();
		
			static bool isCheckSumMatch (const QString data, const QString expectedCheckSum);
			static QString formattedCheckSum (const QString data);
		
		private:
			static quint16 checkSum (const QString data);
			static QString stringedCheckSum (quint16 checksum);
		};
	}
}
