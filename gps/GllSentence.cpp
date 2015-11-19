#include <QtCore/QDebug>

#include "SentenceCommon.h"

#include "GllSentence.h"

namespace Core
{
	namespace Gps
	{
		GllSentence::GllSentence (const QString &sentence, QObject *parent)
			: QObject (parent)
		{
			parse (sentence);
		}
		
		GllSentence::GllSentence (QObject *parent)
			: QObject (parent)
		{
		}
		
		GllSentence::GllSentence (const GllSentence &gllSentence)
			: QObject ()
			, sentenceFields_ (gllSentence.sentenceFields_)
			, latitude_ (gllSentence.latitude_)
			, cardinalNS_ (gllSentence.cardinalNS_)
			, longitude_ (gllSentence.longitude_)
			, cardinalEW_ (gllSentence.cardinalEW_)
			, time_ (gllSentence.time_)
			, status_ (gllSentence.status_)
			, mode_ (gllSentence.mode_)
		{
		}
		
		GllSentence &GllSentence::operator= (const GllSentence &sentence)
		{
			if (this != &sentence) {
				sentenceFields_ = sentence.sentenceFields_;
				latitude_ = sentence.latitude_;
				cardinalNS_ = sentence.cardinalNS_;
				longitude_ = sentence.longitude_;
				cardinalEW_ = sentence.cardinalEW_;
				time_ = sentence.time_;
				status_ = sentence.status_;
				mode_ = sentence.mode_;
			}
			return *this;
		}
		
		void GllSentence::parse (const QString &sentence)
		{
			sentenceFields_ = sentence.split (',');
		
			if (sentenceFields_.size() == FIELD_COUNT) {
				latitude_ = sentenceFields_ [LATITUDE_FIELD];
		
				cardinalNS_ = sentenceFields_ [CARDINAL_NS_FIELD];
		
				longitude_ = sentenceFields_ [LONGITUDE_FIELD];
		
				cardinalEW_ = sentenceFields_ [CARDINAL_EW_FIELD];
		
				const char thirdMsecDigit = '0';
				time_ = QTime::fromString (sentenceFields_ [TIME_FIELD] + thirdMsecDigit, "hhmmss.zzz");
		
				status_ = sentenceFields_ [STATUS_FIELD];
		
				mode_ = sentenceFields_ [MODE_FIELD];
			} else {
				qWarning () << metaObject ()->className () << ':' << "Wrong field count in sentence" << sentence;
			}
		}
		
		void GllSentence::print () const
		{
			qDebug () << "Latitude:" << latitude_ << cardinalNS_;
			qDebug () << "Longitude:" << longitude_ << cardinalEW_;
			qDebug () << "Utc of position:" << time_;
			qDebug () << "Status:" << status_;
			qDebug () << "Mode:" << mode_;
		}
		
		bool GllSentence::isNull() const
		{
			return sentenceFields_.isEmpty ();
		}
		
		QTime GllSentence::time () const
		{
			return time_;
		}
		
		QString GllSentence::latitude () const
		{
			return latitude_;
		}
		
		QString GllSentence::cardinalNS () const
		{
			return cardinalNS_;
		}
		
		QString GllSentence::longitude () const
		{
			return longitude_;
		}
		
		QString GllSentence::cardinalEW () const
		{
			return cardinalEW_;
		}
		
		QString GllSentence::timeString () const
		{
			return sentenceFields_.size () > TIME_FIELD ? sentenceFields_ [TIME_FIELD] : QString::null;
		}
		
		QString GllSentence::statusString () const
		{
			return sentenceFields_.size () > STATUS_FIELD ? sentenceFields_ [STATUS_FIELD] : QString::null;
		}
		
		QString GllSentence::modeString () const
		{
			return sentenceFields_.size () > MODE_FIELD ? sentenceFields_ [MODE_FIELD] : QString::null;
		}
		
		qint32 GllSentence::latitudeInteger () const
		{
			return coordinateInteger (true, latitudeString ());
		}
		
		qint32 GllSentence::longitudeInteger () const
		{
			return coordinateInteger (false, longitudeString ());
		}
		
		QString GllSentence::latitudeString () const
		{
			return sentenceFields_.size () > LATITUDE_FIELD ? sentenceFields_ [LATITUDE_FIELD] : QString::null;
		}
		
		QString GllSentence::cardinalNSString () const
		{
			return sentenceFields_.size () > CARDINAL_NS_FIELD ? sentenceFields_ [CARDINAL_NS_FIELD] : QString::null;
		}
		
		QString GllSentence::longitudeString () const
		{
			return sentenceFields_.size () > LONGITUDE_FIELD ? sentenceFields_ [LONGITUDE_FIELD] : QString::null;
		}
		
		QString GllSentence::cardinalEWString () const
		{
			return sentenceFields_.size () > CARDINAL_EW_FIELD ? sentenceFields_ [CARDINAL_EW_FIELD] : QString::null;
		}
	}
}
