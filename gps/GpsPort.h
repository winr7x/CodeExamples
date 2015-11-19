#pragma once

#include <QtCore/QRegExp>
#include <QtCore/QTimer>

#include <QtSerialPort/QSerialPort>

#include <memory>

#include "AbstractGpsPort.h"
#include "GgaSentence.h"
#include "GllSentence.h"

namespace Core
{
	namespace Gps
	{
		class GpsPort : public AbstractGpsPort
		{
			Q_OBJECT
		
		public:
			explicit GpsPort (QObject *parent = 0);
			~GpsPort ();
		
		public Q_SLOTS:
			virtual void open (const QString &portName);
		
		private Q_SLOTS:
			void readData ();
			void clearBuffer ();
		
		private:
			void parseBuffer ();
			void parseSentences ();
			void parseSentenceContent (const QString &sentenceContent);
			bool isSentenceContentParsed (const QString &sentenceContent);
			bool sentenceBeginningFound (int &sentencePos);
			void dropGarbageData (int veryFirstSentencePos);
			void reset ();
			void openPort (const QString &portName);
			bool isOpen () const;
			void close ();
		
		private:
			QTimer bufferOverflowPreventationTimer_;
			std::unique_ptr<QSerialPort> port_;
			QByteArray buffer_;
			bool isSentencesReceivingStarted_; // NMEA sentences
			QRegExp nmeaSentenceRegExp_;
			QRegExp contentRegExp_;
		};
	}
}
