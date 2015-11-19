#pragma once

#include <QtCore/QVariant>

namespace Core
{
	namespace Gps 
	{
		class ComPortSettings
		{
		public:
			ComPortSettings ();
			static int baudRate ();
			static int dataBits ();
			static int parity ();
			static int stopBits ();
			static int flowControl ();
			static bool isMockPort ();

		private:
			static QVariant value (const QString &key, const QVariant &defValue);
			static void setValue (const QString &key, const QVariant &value);
		};
	}
}
