#include <QtCore/QDebug>

#include <QtSerialPort/QSerialPortInfo>

#include "ComPorts.h"

namespace Core
{
	namespace Gps
	{
		QStringList comPorts ()
		{
			QStringList sortedPorts;
			for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts ()) {
				sortedPorts.append (info.portName ());
			}
		
			sortedPorts.sort ();
			return sortedPorts;
		}
	}
}
