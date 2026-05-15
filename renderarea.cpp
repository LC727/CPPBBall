#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    antialiased = false;
    transformed = false;
    pixmap.load(":/images/qt-logo.png");
    this->ballRadius = 30;

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(false);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

void RenderArea::setShape(Shape shape)
{
    this->shape = shape;
    update();
}

void RenderArea::setPen(const QPen &pen)
{
    this->pen = pen;
    update();
}

void RenderArea::setBrush(const QBrush &brush)
{
    this->brush = brush;
    update();
}

void RenderArea::setAntialiased(bool antialiased)
{
    this->antialiased = antialiased;
    update();
}

void RenderArea::setTransformed(bool transformed)
{
    this->transformed = transformed;
    update();
}

void RenderArea::setBallPos(const QPoint newPos){
    this->ballPos = newPos;
    update();
}


void RenderArea::setFrameVertices(std::vector<QPoint> newVertices){
    this->frameVertices = newVertices;
    update();
}

void RenderArea::drawBall(QPainter* painter){
    int r = this->ballRadius;
    //printf("Ball radius is: %i\n",r);
    QRect ball(this->ballPos, QSize(r,r));
    //printf("Ball is set to: %i, %i\n",this->ballPos.x(),this->ballPos.y());

    Qt::BrushStyle style = Qt::BrushStyle::Dense1Pattern;
    painter->setBrush(QBrush(Qt::red, style));
    painter->drawEllipse(ball);
}

void RenderArea::drawFrame(QPainter* painter){

}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QRect frame(0, 0, width(), height());
    //printf("Frame size: %i, %i",width(),height());

    QPainter painter(this);
    Qt::BrushStyle style = Qt::BrushStyle::Dense1Pattern;
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::blue, style));
    if (antialiased)
        painter.setRenderHint(QPainter::Antialiasing, true);

    painter.drawRect(frame);
    drawBall(&painter);

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
