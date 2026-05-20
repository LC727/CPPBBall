#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    antialiased = false;
    transformed = false;
    pixmap.load(":/images/qt-logo.png");
    this->ballRadius = 15;

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

void RenderArea::setTrajectoryParameters(std::tuple<float, float, float> newTrajectoryParameters){
    this->trajectoryParameters = newTrajectoryParameters;
}

void RenderArea::setFrameVertices(std::vector<QPoint> newVertices){
    this->frameVertices = newVertices;
    update();
}

void RenderArea::drawBall(QPainter* painter){
    int r = this->ballRadius;
    //printf("Ball radius is: %i\n",r);
    QRect ball(this->ballPos+QPoint(15,15), QSize(2*r,2*r));
    //printf("Ball is set to: %i, %i\n",this->ballPos.x(),this->ballPos.y());

    Qt::BrushStyle style = Qt::BrushStyle::Dense1Pattern;
    painter->setBrush(QBrush(Qt::red, style));
    painter->drawEllipse(ball);
}

void RenderArea::drawTrajectory(QPainter* painter){
    int r = this->ballRadius;
    int nSteps = height()-this->ballPos.ry()+15;
    qreal step = width() / nSteps;
    float a = std::get<0>(trajectoryParameters);
    float x0 = std::get<1>(trajectoryParameters);
    float b = std::get<2>(trajectoryParameters);
    QPainterPath painterPath;
    qreal x = 0;
    for(int i = 0 ; i<nSteps ; i++)
    {
        qreal y = a*pow((x-x0),2)+b;
        if(x == 0)
        {
            painterPath.moveTo(x+r+15,y+r+15);
        }
        else
        {
            painterPath.lineTo(x+r+15,y+r+15);
        }
        x += step;
    }
    painter->setPen(QPen(Qt::black));
    painter->setBrush(QBrush(Qt::white));
    painter->drawPath(painterPath);
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
    painter.setBrush(QBrush(Qt::white, style));
    if (antialiased)
        painter.setRenderHint(QPainter::Antialiasing, true);

    painter.drawRect(frame);
    drawBall(&painter);
    drawTrajectory(&painter);

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
