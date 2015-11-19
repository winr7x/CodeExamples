#pragma once

#include <QtGui/QGraphicsRectItem>

#include <iostream>
#include <vector>
#include <memory>

class QColor;
class QSpinBox;
class QGraphicsLineItem;
class QGraphicsSimpleTextItem;
class QGraphicsScene;
class QSize;
class QPen;

class Axes
{
public:
	Axes (QGraphicsScene &scene, QSize &originalSize, QSpinBox &xMaxSpinBox, QSpinBox &yMaxSpinBox);

	void setVisible (bool visible);
	void drawTicksAndLabelsX ();
	void drawTicksAndLabelsY ();
	void drawBackgroundX ();
	void drawBackgroundY ();
	void removeTicksAndLabels (std::vector<QGraphicsLineItem *> &ticks, std::vector<QGraphicsSimpleTextItem *> &labels);

private:
	Q_DISABLE_COPY (Axes)

	enum Axis {
		X,
		Y
	};

	static QPen axisTickPen ();
	static int backgroundWidth (Axis);
	static QColor whiteBackground ();

	double tickCost (Axis) const;
	int nSegments (Axis axis) const;
	double segment(Axis axis) const;

private:
	static const double yTickIndent;

	std::vector<QGraphicsLineItem *> xTicks_;
	std::vector<QGraphicsLineItem *> yTicks_;
	std::vector<QGraphicsSimpleTextItem *> xLabels_;
	std::vector<QGraphicsSimpleTextItem *> yLabels_;
	std::unique_ptr<QGraphicsRectItem> xBackground_;
	std::unique_ptr<QGraphicsRectItem> yBackground_;

	QGraphicsScene &scene_;
	QSize &originalSize_;
	QSpinBox &xMaxSpinBox_;
	QSpinBox &yMaxSpinBox_;
};
