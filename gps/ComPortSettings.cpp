#include "QtSerialPort/qserialport.h"

#include "ApplicationSettings.h"

#include "ComPortSettings.h"

namespace Core
{
	namespace Gps
	{
		ComPortSettings::ComPortSettings ()
		{
		}

		int ComPortSettings::baudRate ()
		{
			bool isIntegered = false;
			return value ("BaudRate", 9600).toInt (&isIntegered);
		}
		
		int ComPortSettings::dataBits ()
		{
			bool isIntegered = false;
			return value ("DataBits", QSerialPort::Data8).toInt (&isIntegered);
		}
		
		int ComPortSettings::parity ()
		{
			bool isIntegered = false;
			return value ("Parity", QSerialPort::NoParity).toInt (&isIntegered);
		}
		
		int ComPortSettings::stopBits()
		{
			bool isIntegered = false;
			return value ("StopBits", QSerialPort::OneStop).toInt (&isIntegered);
		}
		
		int ComPortSettings::flowControl()
		{
			bool isIntegered = false;
			return value ("FlowControl", QSerialPort::NoFlowControl).toInt (&isIntegered);
		}

		bool ComPortSettings::isMockPort ()
		{
			return value ("IsMockPort", false).toBool ();
		}

		QVariant ComPortSettings::value (
			const QString &key,
			const QVariant &defValue)
		{
			return appSettings->value (QSettings::UserScope, QString ("ComPort/%1").arg (key), defValue);
		}
	
		void ComPortSettings::setValue (
			const QString &key,
			const QVariant &value)
		{
			appSettings->setValue (QSettings::UserScope, QString ("ComPort/%1").arg (key), value);
		}
	}
}
