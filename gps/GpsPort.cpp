#include <QtCore/QDebug>

#include "ApplicationSettings.h"
#include "ComPortSettings.h"

#include "CheckSum.h"

#include "GpsPort.h"

namespace Core
{
	namespace Gps
	{
		GpsPort::GpsPort (QObject *parent)
			: AbstractGpsPort (parent)
			, port_ (new QSerialPort)
			, isSentencesReceivingStarted_ (false)
			, nmeaSentenceRegExp_ ("(\\$(.*)\r\n)")
			, contentRegExp_ ("^(([A-Z]{5})(.+))\\*([0-9a-fA-F]{2})$")
		{
			nmeaSentenceRegExp_.setMinimal (true);

			constexpr int bufferOverflowCheckInterval = 10000;
			bufferOverflowPreventationTimer_.setInterval (bufferOverflowCheckInterval);

			connect (port_.get (), SIGNAL (readyRead ()), this, SLOT (readData ()));
			connect (&bufferOverflowPreventationTimer_, SIGNAL (timeout ()), SLOT (clearBuffer ()));
		}
		
		GpsPort::~GpsPort ()
		{
			close ();
		}
		
		void GpsPort::open (const QString &portName)
		{
			if (isOpen ()) {
				if (port_->portName () != portName) {
					close ();
					openPort (portName);
				}
			} else {
				openPort (portName);
			}
		}
		
		bool GpsPort::isOpen () const
		{
			return port_->isOpen ();
		}
		
		void GpsPort::close ()
		{
			if (isOpen ()) {
				port_->close ();
				reset ();
			}
		}
		
		void GpsPort::readData ()
		{
			buffer_ += port_->readAll ();
			parseBuffer ();
		}
		
		void GpsPort::clearBuffer ()
		{
			static const int extraLargeBufferSize = 500;

			if (buffer_.size () > extraLargeBufferSize) {
				qWarning () << metaObject ()->className () << ':' << "Buffer overflow";
				buffer_.clear ();
			}
		}
		
		void GpsPort::parseBuffer ()
		{
			if (isSentencesReceivingStarted_) {
				parseSentences ();
			} else {
				int sentencePos = 0;
				if (sentenceBeginningFound (sentencePos)) {
					isSentencesReceivingStarted_ = true;
					dropGarbageData (sentencePos);
					parseSentences ();
				}
			}
		}
		
		void GpsPort::parseSentences ()
		{
			int tailPos = 0;
			int sentencePos = 0;
			while ((sentencePos = nmeaSentenceRegExp_.indexIn (buffer_, sentencePos)) != -1) {
				const QString sentenceContent = nmeaSentenceRegExp_.cap (2);
				parseSentenceContent (sentenceContent);
				emit sentenceReady (sentenceContent);
				sentencePos += nmeaSentenceRegExp_.matchedLength ();
				tailPos = sentencePos;
			}
		
			buffer_.remove (0, tailPos);
		}
		
		void GpsPort::parseSentenceContent (const QString &sentenceContent)
		{
			if (isSentenceContentParsed (sentenceContent)) {
				const QString checkSum = contentRegExp_.cap (4);
				const QString checksummedData = contentRegExp_.cap (1);
				if (CheckSum::isCheckSumMatch (checksummedData, checkSum)) {
					const QString header = contentRegExp_.cap (2);
					if (header == "GPGGA") {
						const GgaSentence ggaSentence (checksummedData);
						emit ggaSentenceReceived (ggaSentence);
					} else if (header == "GPGLL") {
						const GllSentence gllSentence (checksummedData);
						emit gllSentenceReceived (gllSentence);
					} else {
						qDebug () << "Unknown setntence ID received";
					}
				} else {
					qDebug () << metaObject ()->className () << ':' << "Checksum error. Data:" << checksummedData;
				}
			} else {
				qWarning () << metaObject ()->className () << ':' << "Can't parse sentence content:" << sentenceContent;
			}
		}
		
		bool GpsPort::isSentenceContentParsed (const QString &sentenceContent)
		{
			return (contentRegExp_.exactMatch (sentenceContent) && contentRegExp_.captureCount () == 4);
		}
		
		bool GpsPort::sentenceBeginningFound (int &sentencePos)
		{
			sentencePos = buffer_.indexOf('$');
			return (sentencePos != -1);
		}
		
		void GpsPort::dropGarbageData (int veryFirstSentencePos)
		{
			buffer_.remove (0, veryFirstSentencePos);
		}
		
		void GpsPort::reset ()
		{
			buffer_.clear ();
			isSentencesReceivingStarted_ = false;
		}
		
		void GpsPort::openPort (const QString &portName)
		{
			port_->setPortName (portName);
			port_->setBaudRate (ComPortSettings::baudRate ());
			port_->setDataBits (static_cast<QSerialPort::DataBits>(ComPortSettings::dataBits ()));
			port_->setParity (static_cast<QSerialPort::Parity>(ComPortSettings::parity ()));
			port_->setStopBits (static_cast<QSerialPort::StopBits>(ComPortSettings::stopBits ()));
			port_->setFlowControl(static_cast<QSerialPort::FlowControl>(ComPortSettings::flowControl ()));
			if (port_->open(QIODevice::ReadWrite)) {
				qDebug () << QString ("Connected to %1 : %2, %3, %4, %5, %6")
								.arg (port_->portName ())
								.arg (port_->baudRate ())
								.arg (port_->dataBits ())
								.arg (port_->parity ())
								.arg (port_->stopBits ())
								.arg (port_->flowControl ());
				bufferOverflowPreventationTimer_.start ();
			} else {
				qDebug () << "Port connection error:" << port_->errorString();
			}
		}
	}
}
