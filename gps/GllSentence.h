#pragma once

#include <QtCore/QStringList>
#include <QtCore/QTime>

#include <map>

namespace Core
{
	namespace Gps
	{
		class GllSentence : public QObject
		{
			Q_OBJECT
		public:
			enum Field {
				ID_FIELD,
				LATITUDE_FIELD,
				CARDINAL_NS_FIELD,
				LONGITUDE_FIELD,
				CARDINAL_EW_FIELD,
				TIME_FIELD,
				STATUS_FIELD,
				MODE_FIELD,
		
				FIELD_COUNT
			};
		
		public:
			explicit GllSentence (const QString &sentence, QObject *parent = 0);
			GllSentence (QObject *parent = 0);
			GllSentence (const GllSentence &gllSentence);
			GllSentence& operator= (const GllSentence &sentence);
			void print () const;

			bool isNull () const;
		
			QTime time () const;
			QString latitude () const;
			QString cardinalNS () const;
			QString longitude () const;
			QString cardinalEW () const;
			QString status () const;
			QString mode () const;
		
			QString latitudeString () const;
			QString cardinalNSString () const;
			QString longitudeString () const;
			QString cardinalEWString () const;
			QString timeString () const;
			QString statusString () const;
			QString modeString () const;

			qint32 latitudeInteger () const;
			qint32 longitudeInteger () const;
		private:
			void parse (const QString &sentence);

		private:
			QStringList sentenceFields_;
		
			QString latitude_;
			QString cardinalNS_;
			QString longitude_;
			QString cardinalEW_;
			QTime time_;
			QString status_;
			QString mode_;
		};
	}
}
