#ifndef BALL_H
#define BALL_H
#include <cmath>
#include <QPointF>

class Ball
{
public:
    Ball(QPointF pos0 = QPointF(100,100),
         QPointF vel0 = QPointF(5,-30),
         int radius = 10);
    Ball(float x0 = 100, float y0 = 100, float dx0 = 5, float dy0 = 30, int radius = 10);
    QPointF getPos() const;
    QPointF getVel() const;
    QPointF setPos(QPointF newPos);
    QPointF setVel(QPointF newVel);
    int getRadius() const;
private:
    QPointF position;
    QPointF velocity;
    int radius;
};

#endif // BALL_H
