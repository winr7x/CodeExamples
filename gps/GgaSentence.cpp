#include <QtCore/QDebug>

#include "SentenceCommon.h"

#include "GgaSentence.h"

namespace Core
{
	namespace Gps
	{
		GgaSentence::GgaSentence (const QString &sentence, QObject *parent)
			: QObject (parent)
			, fixQualityToStringMap_ ({{InvalidFix, "Invalid"},
									   {GpsFix, "Gps"},
									   {DGpsFix, "DGps"}})
		{
			parse (sentence);
		}
		
		GgaSentence::GgaSentence (QObject *parent)
			: QObject (parent)
		{
		}
		
		GgaSentence::GgaSentence (const GgaSentence &ggaSentence)
			: QObject ()
			, sentenceFields_ (ggaSentence.sentenceFields_)
			, time_ (ggaSentence.time_)
			, latitude_ (ggaSentence.latitude_)
			, cardinalNS_ (ggaSentence.cardinalNS_)
			, longitude_ (ggaSentence.longitude_)
			, cardinalEW_ (ggaSentence.cardinalEW_)
			, fixQuality_ (ggaSentence.fixQuality_)
			, fixQualityToStringMap_ (ggaSentence.fixQualityToStringMap_)
			, satellitesUsed_ (ggaSentence.satellitesUsed_)
			, hdop_ (ggaSentence.hdop_)
			, altitude_ (ggaSentence.altitude_)
			, geoidalSeparation_ (ggaSentence.geoidalSeparation_)
			, correctionsAge_ (ggaSentence.correctionsAge_)
			, differentialStationId_ (ggaSentence.differentialStationId_)
		{
		}
		
		GgaSentence &GgaSentence::operator= (const GgaSentence &sentence)
		{
			if (this != &sentence) {
				sentenceFields_ = sentence.sentenceFields_;
				time_ = sentence.time_;
				latitude_ = sentence.latitude_;
				cardinalNS_ = sentence.cardinalNS_;
				longitude_ = sentence.longitude_;
				cardinalEW_ = sentence.cardinalEW_;
				fixQuality_ = sentence.fixQuality_;
				fixQualityToStringMap_ = sentence.fixQualityToStringMap_;
				satellitesUsed_ = sentence.satellitesUsed_;
				hdop_ = sentence.hdop_;
				altitude_ = sentence.altitude_;
				geoidalSeparation_ = sentence.geoidalSeparation_;
				correctionsAge_ = sentence.correctionsAge_;
				differentialStationId_ = sentence.differentialStationId_;
			}
			return *this;
		}
		
		void GgaSentence::parse (const QString &sentence)
		{
			sentenceFields_ = sentence.split (',');
		
			if (sentenceFields_.size () == FIELD_COUNT) {
				const char thirdMsecDigit = '0';
				time_ = QTime::fromString (sentenceFields_ [TIME_FIELD] + thirdMsecDigit, "hhmmss.zzz");
		
				latitude_ = sentenceFields_ [LATITUDE_FIELD];
		
				cardinalNS_ = sentenceFields_ [CARDINAL_NS_FIELD];
		
				longitude_ = sentenceFields_ [LONGITUDE_FIELD];
		
				cardinalEW_ = sentenceFields_ [CARDINAL_EW_FIELD];
		
				bool isQualityOk = false;
				const FixQuality quality = static_cast<FixQuality>(sentenceFields_[FIX_QUALITY_FIELD].toInt (&isQualityOk));
				fixQuality_ = isQualityOk ? quality : InvalidFix;
		
				bool isSatellitesUsedOk = false;
				const int satellitesUsed = sentenceFields_ [SATELLITES_USED_FIELD].toInt (&isSatellitesUsedOk);
				satellitesUsed_ = isSatellitesUsedOk ? satellitesUsed : 0;
		
				bool isHdopOk = false;
				const double hdop = sentenceFields_ [HDOP_FIELD].toDouble (&isHdopOk);
				hdop_ = isHdopOk ? hdop : 0;
		
				bool isAltitudeOk = false;
				const double altitude = sentenceFields_ [ALTITUDE_FIELD].toDouble (&isAltitudeOk);
				altitude_ = isAltitudeOk ? altitude : 0;
		
				// ALTITUDE_METERS_FIELD
		
				bool isGeoidalSeparationIsOk = false;
				const double geoidalSeparation = sentenceFields_ [GEOIDAL_SEPARATION_FIELD].toDouble (&isGeoidalSeparationIsOk);
				geoidalSeparation_ = isGeoidalSeparationIsOk ? geoidalSeparation : 0;
		
				// SEPARATION_METERS_FIELD
		
				bool isAgeOfCorrectionsOk = false;
				const int ageOfCorrections = sentenceFields_ [CORRECTIONS_AGE_FIELD].toInt (&isAgeOfCorrectionsOk);
				correctionsAge_ = isAgeOfCorrectionsOk ? ageOfCorrections : 0;
		
				bool isDifferentialStationIdOk = false;
				const int differentialStationId = sentenceFields_ [DIFFERENTIAL_STATION_ID_FIELD].toInt (&isDifferentialStationIdOk);
				differentialStationId_ = isDifferentialStationIdOk ? differentialStationId : 0;
			} else {
				qWarning () << metaObject ()->className () << ':' << "Wrong field count in sentence" << sentence;
			}
		}
		
		void GgaSentence::print () const
		{
			qDebug () << "Utc of position:" << time_;
			qDebug () << "Latitude:" << latitude_ << cardinalNS_;
			qDebug () << "Longitude:" << longitude_ << cardinalEW_;
			if (fixQualityToStringMap_.count(fixQuality_) > 0) {
				qDebug () << "Fix type:" << fixQualityToStringMap_ [fixQuality_];
			} else {
				qWarning () << metaObject()->className() << ':' << "Unknown key for fixQualityToStringMap";
			}
			qDebug () << "Satellites used:" << satellitesUsed_;
			qDebug () << "HDOP:" << hdop_;
			qDebug () << "Altitude:" << altitude_ << "M";
			qDebug () << "Age of corrections:" << correctionsAge_;
			qDebug () << "Differential station ID:" << differentialStationId_;
		}
		
		bool GgaSentence::isNull () const
		{
			return sentenceFields_.isEmpty ();
		}
		
		QTime GgaSentence::time () const
		{
			return time_;
		}
		
		QString GgaSentence::latitude () const
		{
			return latitude_;
		}
		
		QString GgaSentence::cardinalNS () const
		{
			return cardinalNS_;
		}
		
		QString GgaSentence::longitude () const
		{
			return longitude_;
		}
		
		QString GgaSentence::cardinalEW () const
		{
			return cardinalEW_;
		}
		
		GgaSentence::FixQuality GgaSentence::fixQuality () const
		{
			return fixQuality_;
		}
		
		int GgaSentence::satellitesUsed () const
		{
			return satellitesUsed_;
		}
		
		double GgaSentence::hdop () const
		{
			return hdop_;
		}
		
		double GgaSentence::altitude () const
		{
			return altitude_;
		}
		
		double GgaSentence::geoidalSeparation () const
		{
			return geoidalSeparation_;
		}
		
		int GgaSentence::correctionsAge () const
		{
			return correctionsAge_;
		}
		
		int GgaSentence::differentialStationId () const
		{
			return differentialStationId_;
		}
		
		QString GgaSentence::timeString () const
		{
			return sentenceFields_.size () > TIME_FIELD ? sentenceFields_ [TIME_FIELD] : QString::null;
		}
		
		QString GgaSentence::latitudeString () const
		{
			return sentenceFields_.size () > LATITUDE_FIELD ? sentenceFields_ [LATITUDE_FIELD] : QString::null;
		}
		
		QString GgaSentence::cardinalNSString () const
		{
			return sentenceFields_.size () > CARDINAL_NS_FIELD ? sentenceFields_ [CARDINAL_NS_FIELD] : QString::null;
		}
		
		QString GgaSentence::longitudeString () const
		{
			return sentenceFields_.size () > LONGITUDE_FIELD ? sentenceFields_ [LONGITUDE_FIELD] : QString::null;
		}
		
		QString GgaSentence::cardinalEWString () const
		{
			return sentenceFields_.size () > CARDINAL_EW_FIELD ? sentenceFields_ [CARDINAL_EW_FIELD] : QString::null;
		}
		
		QString GgaSentence::fixQualityString () const
		{
			return sentenceFields_.size () > FIX_QUALITY_FIELD ? sentenceFields_ [FIX_QUALITY_FIELD] : QString::null;
		}
		
		QString GgaSentence::satellitesUsedString () const
		{
			return sentenceFields_.size () > SATELLITES_USED_FIELD ? sentenceFields_ [SATELLITES_USED_FIELD] : QString::null;
		}
		
		QString GgaSentence::hdopString() const
		{
			return sentenceFields_.size () > HDOP_FIELD ? sentenceFields_ [HDOP_FIELD] : QString::null;
		}
		
		QString GgaSentence::altitudeString() const
		{
			return sentenceFields_.size () > ALTITUDE_FIELD ? sentenceFields_ [ALTITUDE_FIELD] : QString::null;
		}
		
		QString GgaSentence::geoidalSeparationString () const
		{
			return sentenceFields_.size () > GEOIDAL_SEPARATION_FIELD ? sentenceFields_ [GEOIDAL_SEPARATION_FIELD] : QString::null;
		}
		
		QString GgaSentence::correctionsAgeString () const
		{
			return sentenceFields_.size () > CORRECTIONS_AGE_FIELD ? sentenceFields_ [CORRECTIONS_AGE_FIELD] : QString::null;
		}
		
		QString GgaSentence::differentialStationIdString () const
		{
			return sentenceFields_.size () > DIFFERENTIAL_STATION_ID_FIELD ? sentenceFields_ [DIFFERENTIAL_STATION_ID_FIELD] : QString::null;
		}
		
		qint32 GgaSentence::latitudeInteger () const
		{
			return coordinateInteger (true, latitudeString ());
		}
		
		qint32 GgaSentence::longitudeInteger () const
		{
			return coordinateInteger (false, longitudeString ());
		}
	}
}
