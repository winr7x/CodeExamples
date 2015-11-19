#pragma once

#include <QtCore/QTimer>

#include "AbstractGpsPort.h"
#include "GgaSentence.h"
#include "GllSentence.h"

namespace Core
{
	namespace Gps
	{
		class MockGpsPort : public AbstractGpsPort
		{
			Q_OBJECT
		
		public:
			explicit MockGpsPort (QObject *parent = 0);
			virtual ~MockGpsPort ();
		
		public Q_SLOTS:
			virtual void open (const QString &portName);
		
		private Q_SLOTS:
			void generateSentences ();
		
		private:
			void generateGgaSentence (int coordinateLastDigit);
			void generateGglSentence (int coordinateLastDigit);
		
		private:
			bool isOpened_;
			QTimer sentenceGeneratingTimer_;
		};
	}
}
