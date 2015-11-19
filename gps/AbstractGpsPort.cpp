#include <QtCore/QDebug>

#include "GpsPort.h"
#include "MockGpsPort.h"

#include "AbstractGpsPort.h"

namespace Core
{
	namespace Gps
	{
		AbstractGpsPort::AbstractGpsPort (QObject *parent)
			: QObject (parent)
		{
		}
		
		AbstractGpsPort::~AbstractGpsPort ()
		{
		}
		
		AbstractGpsPort* AbstractGpsPort::createGpsPort (AbstractGpsPort::GpsPortType type)
		{
			AbstractGpsPort *result = nullptr;
			switch (type) {
			case REAL_GPS_PORT:
				result = new GpsPort;
				break;
			case MOCK_GPS_PORT:
				result = new MockGpsPort;
				break;
			}
		
			if (result == nullptr) {
				qCritical() << "AbstractGpsPort:" << "Unknown GpsPortType";
			}
		
			return result;
		}
	}
}
