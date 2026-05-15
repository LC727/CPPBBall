#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include "model.h"

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    enum Shape { Line, Points, Polyline, Polygon, Rect, RoundedRect, Ellipse, Arc,
                 Chord, Pie, Path, Text, Pixmap };

    RenderArea(QWidget *parent = 0);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void setBallPos(const QPoint newPos);
    void setFrameVertices(std::vector<QPoint> newVertices);
    void initialize(Model* model);

public slots:
    void setShape(Shape shape);
    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);
    void setAntialiased(bool antialiased);
    void setTransformed(bool transformed);
    void drawBall(QPainter* painter);
    void drawFrame(QPainter* painter);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Shape shape;
    QPen pen;
    QBrush brush;
    bool antialiased;
    bool transformed;
    QPixmap pixmap;
    QPoint ballPos;
    int ballRadius;
    std::vector<QPoint> frameVertices;
};
#endif // RENDERAREA_H
