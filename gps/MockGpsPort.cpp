#include <QtCore/QDebug>
#include <QtCore/QDateTime>

#include "CheckSum.h"
#include "ComPortSettings.h"

#include "MockGpsPort.h"

namespace Core
{
	namespace Gps
	{
		MockGpsPort::MockGpsPort (QObject *parent)
			: AbstractGpsPort (parent)
			, isOpened_ (false)
		{
			constexpr int generatingInterval = 1000;
			sentenceGeneratingTimer_.setInterval (generatingInterval);
			connect (&sentenceGeneratingTimer_, SIGNAL (timeout ()), SLOT (generateSentences ()));
		}
		
		MockGpsPort::~MockGpsPort ()
		{
		}
		
		void MockGpsPort::open (const QString &portName)
		{
			Q_UNUSED (portName)
			if (!isOpened_) {
				isOpened_ = true;
				sentenceGeneratingTimer_.start ();
			}
		}
		
		void MockGpsPort::generateSentences ()
		{
			static int counter = 0;
		
			const int coordinateLastDigit = counter % 10;
		
			generateGgaSentence (coordinateLastDigit);
			generateGglSentence (coordinateLastDigit);
		
			++counter;
		}
		
		void MockGpsPort::generateGgaSentence (int coordinateLastDigit)
		{
			const QString ggaChecksumedData = QString ("GPGGA,%1.00,5958.6281%2,N,03021.8690%3,E,2,06,1.53,61.4,M,15.8,M,,0000")
					.arg (QDateTime::currentDateTimeUtc().toString("hhmmss"))
					.arg (coordinateLastDigit)
					.arg (coordinateLastDigit);
		
			if (ggaChecksumedData.contains ("5958.62813")
				|| ggaChecksumedData.contains ("5958.62814")
				|| ggaChecksumedData.contains ("5958.62815")
				|| ggaChecksumedData.contains ("5958.62816")) {
				return;
			}
			
			emit sentenceReady (ggaChecksumedData + '*' + CheckSum::formattedCheckSum (ggaChecksumedData));
			const GgaSentence ggaSentence (ggaChecksumedData);
			emit ggaSentenceReceived (ggaSentence);
		}
		
		void MockGpsPort::generateGglSentence (int coordinateLastDigit)
		{
			const QString gllChecksumedData = QString ("GPGLL,5958.6281%1,N,03021.8690%2,E,%3.00,A,D")
					.arg (coordinateLastDigit)
					.arg (coordinateLastDigit)
					.arg (QDateTime::currentDateTimeUtc().toString("hhmmss"));
		
			emit sentenceReady (gllChecksumedData + '*' + CheckSum::formattedCheckSum (gllChecksumedData));
			const GllSentence gllSentence (gllChecksumedData);
			emit gllSentenceReceived (gllSentence);
		}
	}
}
