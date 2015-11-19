#pragma once

#include "GgaSentence.h"
#include "GllSentence.h"

namespace Core
{
	namespace Gps
	{
		class AbstractGpsPort : public QObject
		{
			Q_OBJECT
		
		public:
			enum GpsPortType {
				REAL_GPS_PORT,
				MOCK_GPS_PORT
			};
		
			explicit AbstractGpsPort (QObject *parent = 0);
			virtual ~AbstractGpsPort ();
		
			// Factory Method
			static AbstractGpsPort* createGpsPort (GpsPortType type);
		
		public Q_SLOTS:
			virtual void open (const QString &portName) = 0;
		
		Q_SIGNALS:
			void sentenceReady (QString sentence);
			void ggaSentenceReceived (GgaSentence ggaSentence);
			void gllSentenceReceived (GllSentence gllSentence);
		};
	}
}
