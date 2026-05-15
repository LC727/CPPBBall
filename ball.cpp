#include "ball.h"

Ball::Ball(QPointF pos0, QPointF vel0, int radius) : position(pos0), velocity(vel0), radius(radius) {}

Ball::Ball(float x0, float y0, float dx0, float dy0, int radius) : position(QPointF(x0,y0)), velocity(QPointF(dx0,dy0)), radius(radius) {}

QPointF Ball::getPos() const {
    return position;
}

QPointF Ball::getVel() const {
    return velocity;
}

int Ball::getRadius() const {
    return (radius);
}

QPointF Ball::setPos(QPointF newPos) {
    position = newPos;
    return position;
}

QPointF Ball::setVel(QPointF newVel) {
    velocity = newVel;
    return velocity;
}
