#pragma once

#include "QtCore/QObject"
#include "QtCore/QTimer"

#include <memory>

class AbstractGpsPort;

#include "GgaSentence.h"

#define GpsConnectionInstance Core::Gps::GpsConnection::instance ()

namespace Core
{
	namespace Gps
	{
		class GpsConnection : public QObject
		{
			Q_OBJECT
		
		public:
			Q_PROPERTY(int connectionState READ connectionState NOTIFY connectionStateChanged)
			
			explicit GpsConnection (QObject *parent = 0);
			~GpsConnection ();

			static GpsConnection* instance ();
			GgaSentence coordinates () const;

			Q_INVOKABLE void reconnect (const QString &port);
		
			int connectionState () const;

		Q_SIGNALS:
			void connectionStateChanged ();

		private Q_SLOTS:
			void rememberCoordinates (GgaSentence ggaSentence);
			void setExpired ();
			void showSentence (QString sentence) const;
		
		private:
			Q_DISABLE_COPY (GpsConnection)
		
			bool isExpired_;
			QTimer coordinatesExpireTimer_;
			GgaSentence coordinates_;
			static GpsConnection *instance_;
			std::unique_ptr<AbstractGpsPort> gpsPort_;
		};
	}
}
