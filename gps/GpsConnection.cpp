#include <QtCore/QDebug>

#include "ApplicationSettings.h"
#include "AbstractGpsPort.h"
#include "ComPortSettings.h"
#include "SettingConstant.h"

#include "GpsConnection.h"

namespace Core
{
	namespace Gps
	{
		GpsConnection *GpsConnection::instance_ = nullptr;

		GpsConnection::GpsConnection (QObject *parent)
			: QObject (parent)
			, isExpired_ (true)
			, gpsPort_ (AbstractGpsPort::createGpsPort (ComPortSettings::isMockPort ()
														? AbstractGpsPort::MOCK_GPS_PORT
														: AbstractGpsPort::REAL_GPS_PORT))
		{
			constexpr int currentCoordinatesExpireTime = 1500;
			coordinatesExpireTimer_.setInterval (currentCoordinatesExpireTime);

			connect (&coordinatesExpireTimer_, SIGNAL (timeout ()), SLOT (setExpired ()));

			connect (gpsPort_.get (), SIGNAL (ggaSentenceReceived (GgaSentence)),
					 SLOT (rememberCoordinates (GgaSentence)));

			connect (gpsPort_.get (), SIGNAL (sentenceReady (QString)), SLOT (showSentence (QString)));
		}

		GpsConnection::~GpsConnection ()
		{
		}

		GpsConnection* GpsConnection::instance ()
		{
			return instance_ ? instance_ : instance_ = new GpsConnection;
		}

		GgaSentence GpsConnection::coordinates () const
		{
			return isExpired_ ? GgaSentence () : coordinates_;
		}

		void GpsConnection::reconnect (const QString &port)
		{
			gpsPort_->open (port);
		}
		
		int GpsConnection::connectionState() const
		{
			const GgaSentence sentence = coordinates ();
			int result = 0;
			if (!sentence.isNull ()) {
				result = sentence.fixQuality () == GgaSentence::InvalidFix ? 1 : 2;
			}
			return result;
		}

		void GpsConnection::rememberCoordinates (GgaSentence ggaSentence)
		{
			coordinatesExpireTimer_.stop ();
			coordinates_ = ggaSentence;
			emit connectionStateChanged ();
			isExpired_ = false;
			coordinatesExpireTimer_.start ();
		}

		void GpsConnection::setExpired ()
		{
			isExpired_ = true;
			emit connectionStateChanged ();
		}

		void GpsConnection::showSentence (QString sentence) const
		{
			qDebug () << sentence;
		}
	}
}
