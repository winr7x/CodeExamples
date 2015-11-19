#pragma once

#include <QtCore/QStringList>
#include <QtCore/QTime>

#include <map>

namespace Core
{
	namespace Gps
	{
		class GgaSentence : public QObject
		{
			Q_OBJECT
		public:
			enum FixQuality {
				InvalidFix,
				GpsFix,
				DGpsFix
			};
		
			enum Field {
				ID_FIELD,
				TIME_FIELD,
				LATITUDE_FIELD,
				CARDINAL_NS_FIELD,
				LONGITUDE_FIELD,
				CARDINAL_EW_FIELD,
				FIX_QUALITY_FIELD,
				SATELLITES_USED_FIELD,
				HDOP_FIELD,
				ALTITUDE_FIELD,
				ALTITUDE_METERS_FIELD,
				GEOIDAL_SEPARATION_FIELD,
				SEPARATION_METERS_FIELD,
				CORRECTIONS_AGE_FIELD,
				DIFFERENTIAL_STATION_ID_FIELD,
		
				FIELD_COUNT
			};
		
		public:
			explicit GgaSentence (const QString &sentence, QObject *parent = 0);
			GgaSentence (QObject *parent = 0);
			GgaSentence (const GgaSentence &ggaSentence);
			GgaSentence& operator=(const GgaSentence &sentence);
		
			void print () const;
		
			bool isNull () const;
		
			QTime time () const;
			QString latitude () const;
			QString cardinalNS () const;
			QString longitude () const;
			QString cardinalEW () const;
			FixQuality fixQuality () const;
			int satellitesUsed () const;
			double hdop () const;
			double altitude () const;
			double geoidalSeparation () const;
			int correctionsAge () const;
			int differentialStationId () const;
		
			QString timeString () const;
			QString latitudeString () const;
			QString cardinalNSString () const;
			QString longitudeString () const;
			QString cardinalEWString () const;
			QString fixQualityString () const;
			QString satellitesUsedString () const;
			QString hdopString () const;
			QString altitudeString () const;
			QString geoidalSeparationString () const;
			QString correctionsAgeString () const;
			QString differentialStationIdString () const;
			
			qint32 latitudeInteger () const;
			qint32 longitudeInteger () const;
		
		private:
			void parse (const QString &sentence);
			
		
		private:
			QStringList sentenceFields_;
		
			QTime time_;
			QString latitude_;
			QString cardinalNS_;
			QString longitude_;
			QString cardinalEW_;
			FixQuality fixQuality_;
			mutable std::map<FixQuality, QString> fixQualityToStringMap_;
			int satellitesUsed_;
			double hdop_;
			double altitude_;
			double geoidalSeparation_;
			int correctionsAge_;
			int differentialStationId_;
		};
	}
}
