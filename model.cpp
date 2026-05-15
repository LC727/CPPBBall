#include <cmath>
#include "model.h"
#include <stdexcept>
#include <QPoint>

Model::Model() {
    ball = new Ball(QPointF(200,200), QPointF(15,-30),30);
    frame = new Frame();
    gravity = 60;
}

QPointF Model::getBallPos(){
    return(ball->getPos());
}

std::vector<QPointF> Model::getFrameVertices(){
    return(frame->getVertices());
}

std::tuple<float, float, float> trajectoryParameters(float x, float y, float dx, float dy, int g) {
    // Veryfying that dx is not 0
    if (std::abs(dx) < 1e-10) {
        throw std::invalid_argument("dx cannot be equal to 0 for this calculation");
    }
    double a = -g / (2.0 * dx * dx);
    double x0 = x + (dx * dy) / g;
    double b = y - a * std::pow(x - x0, 2);
    return std::make_tuple(a, x0, b);
}

std::tuple<float, float, float> trajectoryParameters(Ball ball, int g) {
    QPointF ballVel = ball.getVel();
    // Veryfying that dx is not 0
    if (std::abs(ballVel.rx()) < 1e-10) {
        throw std::invalid_argument("dx cannot be equal to 0 for this calculation");
    }
    QPointF ballPos = ball.getPos();
    double a = -g / (2.0 * ballVel.rx() * ballVel.rx());
    double x0 = ballPos.rx() + (ballVel.rx() * ballVel.ry()) / g;
    double b = ballPos.ry() - a * std::pow(ballPos.rx() - x0, 2);
    return std::make_tuple(a, x0, b);
}

void Model::step(){
    QPointF ballPos = ball->getPos();
    QPointF ballVel = ball->getVel();
    QPointF newPos = ballPos + ballVel;
    int dy;
    printf("Ball x speed is: %f\n",ballVel.rx());
    printf("Ball y speed is: %f\n",ballVel.ry());
    if ((newPos.ry()>450 and ballVel.ry()>0) or (newPos.ry()<0 and ballVel.ry()<0)){
        ballVel.setY(-ballVel.y());
        if (newPos.y()>450){
            newPos.setY(900-newPos.y());
        } else{
            newPos.setY(-newPos.y());
        }
        ballVel = ballVel*9/10;
    }
    if ((newPos.rx()>610 and ballVel.rx()>0) or (newPos.rx()<0 and ballVel.rx()<0)){
        ballVel.setX(-ballVel.x());
        if (newPos.x()>610){
            newPos.setX(1220-newPos.x());
        } else{
            newPos.setX(-newPos.x());
        }
        ballVel = ballVel*9/10;
    }
    dy = ballVel.y() + 1;
    ball->setPos(newPos);
    printf("%i",dy);
    ballVel.setY(dy);
    ball->setVel(ballVel);
}
