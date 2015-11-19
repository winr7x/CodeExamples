#include <QtGui/QLabel>
#include <QtGui/QGraphicsLineItem>
#include <QtGui/QGraphicsScene>
#include <QtGui/QSpinBox>

#include "Axes.h"

constexpr double FRAME_SCALE_FACTOR = 0.5;
constexpr int TICK_LENGTH = 10;

const double Axes::yTickIndent = 4;

Axes::Axes (QGraphicsScene &scene, QSize &originalSize, QSpinBox &xMaxSpinBox, QSpinBox &yMaxSpinBox)
	: scene_ (scene)
	, originalSize_ (originalSize)
	, xMaxSpinBox_ (xMaxSpinBox)
	, yMaxSpinBox_ (yMaxSpinBox)
{
}

void Axes::setVisible (bool visible)
{
	for (auto tick : xTicks_) {
		tick->setVisible (visible);
	}

	for (auto label : xLabels_) {
		label->setVisible (visible);
	}

	for (auto label : yLabels_) {
		label->setVisible (visible);
	}

	for (auto tick : yTicks_) {
		tick->setVisible (visible);
	}

	if (xBackground_.get ()) {
		xBackground_->setVisible (visible);
	}

	if (yBackground_.get ()) {
		yBackground_->setVisible (visible);
	}
}

void Axes::drawTicksAndLabelsX()
{
	removeTicksAndLabels (xTicks_, xLabels_);

	const int nAxisXTicks =  nSegments (X) + 1;

	for (int i = 0; i < nAxisXTicks; ++i) {
		if ( (i == 0) || (i == nAxisXTicks - 1)) {
			continue;
		}

		const double tickX = FRAME_SCALE_FACTOR * i * segment (X);
		xTicks_.push_back (scene_.addLine (tickX, FRAME_SCALE_FACTOR * (originalSize_.height () - 1),
										   tickX, FRAME_SCALE_FACTOR * (originalSize_.height () - 1 - TICK_LENGTH), axisTickPen ()));

		QGraphicsSimpleTextItem *text = scene_.addSimpleText (QString::number (i * tickCost (X)));
		const int labelX = tickX - text->boundingRect ().width () / 2;
		const int labelY = FRAME_SCALE_FACTOR * (originalSize_.height () - 1 - TICK_LENGTH) - text->boundingRect ().height ();
		text->setPos (labelX, labelY);
		xLabels_.push_back (text);
	}
}

void Axes::drawTicksAndLabelsY ()
{
	removeTicksAndLabels (yTicks_, yLabels_);

	const int nTicks = nSegments (Y) + 1;

	for (int i = 0; i < nTicks; ++i) {
		if ( (i == 0) || (i == nTicks - 1)) {
			continue;
		}

		const double tickY = FRAME_SCALE_FACTOR * (originalSize_.height () - 1) - FRAME_SCALE_FACTOR * i * segment (Y);
		yTicks_.push_back (scene_.addLine (0, tickY, TICK_LENGTH, tickY, axisTickPen ()));

		QGraphicsSimpleTextItem *text = scene_.addSimpleText (QString::number (i * tickCost (Y)));
		const int labelX = TICK_LENGTH + yTickIndent;
		const int labelY = tickY  - text->boundingRect ().height () / 2;
		text->setPos (labelX, labelY);
		yLabels_.push_back (text);
	}
}

void Axes::drawBackgroundX ()
{
	if (!xBackground_.get ()) {
		const int y = (originalSize_.height () - 1) * FRAME_SCALE_FACTOR - backgroundWidth (X);
		xBackground_.reset (scene_.addRect (0, y, std::round (originalSize_.width () * FRAME_SCALE_FACTOR), 100, QPen (QBrush (), 0), whiteBackground ()));
	}
}

void Axes::drawBackgroundY ()
{
	if (!yBackground_.get ()) {
		yBackground_.reset (scene_.addRect (0, 0, backgroundWidth (Y), std::round (FRAME_SCALE_FACTOR * originalSize_.height()), QPen (QBrush (), 0), whiteBackground ()));
	}
}

void Axes::removeTicksAndLabels (std::vector<QGraphicsLineItem *> &ticks, std::vector<QGraphicsSimpleTextItem *> &labels)
{
	for (auto tick : ticks) {
		scene_.removeItem (tick);
		delete tick;
	}

	for (auto label : labels) {
		scene_.removeItem (label);
		delete label;
	}

	ticks.clear ();
	labels.clear ();
}

QPen Axes::axisTickPen ()
{
	QPen result;
	result.setWidth (4);
	result.setColor (Qt::darkBlue);
	return result;
}

int Axes::backgroundWidth (Axis axis)
{
	static const QLabel label ("00000.0");
	static const int widthY = label.minimumSizeHint ().width () + TICK_LENGTH + yTickIndent;

	return (axis == X ? 22 : widthY);
}

QColor Axes::whiteBackground ()
{
	QColor result ("white");
	result.setAlpha (150);
	return result;
}

double Axes::tickCost (Axis axis) const
{
	return (axis == X
			? xMaxSpinBox_.singleStep ()
			: yMaxSpinBox_.value () / static_cast<double> (nSegments (axis)));
}

int Axes::nSegments (Axis axis) const
{
	static constexpr int fixedSegmentsCount = 10;
	return (axis == X
			? xMaxSpinBox_.value () / tickCost (axis)
			: fixedSegmentsCount);
}

double Axes::segment (Axis axis) const
{
	return (axis == X
			? originalSize_.width () / static_cast<double> (nSegments (axis))
			: originalSize_.height () / static_cast<double> (nSegments (axis)));
}
