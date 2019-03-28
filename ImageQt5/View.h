#pragma once

#include <QWidget>
class MainWindow;
class Document;

#define IMAGE_MARGIN	100
#define IMAGE_MAX_ZOOM	10.0f
#define IMAGE_MIN_ZOOM	0.1f

class View : public QWidget
{
	Q_OBJECT

public:
	explicit View(QWidget *parent = 0);

	// Fit to window
	void zoomFitWindow();

	void zoomChanged(float zoomFactor, float oldFactor);

	QRect getImageRect();

	// Logic point to Image point
	QPoint LPtoIP(const QPoint& point);

	// Image point to Logic point
	QPoint IPtoLP(const QPoint& point);
	QPointF IPtoLP(const QPointF& point);

	// Reset image center point
	void resetImageCenter();

protected:
	void paintEvent(QPaintEvent*);

	void resizeEvent(QResizeEvent*);

	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);

private:
	MainWindow* getMainWindow() const;

	Document* getDocument() const;

	// Restrict image edge
	void restrictImageEdge();

	// Show pixel status
	void showPixelStatus(const QPoint& point);

signals:

public slots:

private:
	QPoint imageCenter;

	QPoint mousePos;

	bool dragImage;
};
