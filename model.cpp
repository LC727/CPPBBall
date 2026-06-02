#include <cmath>
#include "model.h"
#include <stdexcept>
#include <QPoint>
#include <cmath>
#include <iostream>

Model::Model() {
    ball = new Ball(QPointF(200,200), QPointF(15,-30),15);
    frame = new Frame();
    gravity = 1;
    stepGap = 1;
    height = 480;
    width = 640;
}

QPointF Model::getBallPos(){
    return(ball->getPos());
}

std::tuple<float, float, float> Model::getTrajectoryParameters(){
    return(trajectoryParameters);
}

std::vector<QPointF> Model::getFrameVertices(){
    return(frame->getVertices());
}

/*std::tuple<float, float, float> computeTrajectory(float x, float y, float dx, float dy, int g) {
    // Veryfying that dx is not 0
    if (std::abs(dx) < 1e-10) {
        throw std::invalid_argument("dx cannot be equal to 0 for this calculation");
    }
    double a = -g / (2.0 * dx * dx);
    double x0 = x + (dx * dy) / g;
    double b = y - a * std::pow(x - x0, 2);
    return std::make_tuple(a, x0, b);
}*/

std::tuple<float, float, float> Model::computeTrajectory(Ball* ball, int g) {
    QPointF ballVel = ball->getVel();
    // Veryfying that dx is not 0
    if (std::abs(ballVel.rx()) < 1e-10) {
        throw std::invalid_argument("dx cannot be equal to 0 for this calculation");
    }
    QPointF ballPos = ball->getPos();
    double a = g / (2.0 * ballVel.rx() * ballVel.rx());
    double x0 = ballPos.rx() - (ballVel.rx() * ballVel.ry()) / g;
    double b = ballPos.ry() - a * std::pow(ballPos.rx() - x0, 2);
    return std::make_tuple(a, x0, b);
}

Ball* Model::ballFunction(qreal x){
    double a = std::get<0>(trajectoryParameters);
    double x0 = std::get<1>(trajectoryParameters);
    double b = std::get<2>(trajectoryParameters);
    int directionSign = ball->getVel().rx()/abs(ball->getVel().rx());
    return(new Ball(QPointF(x,a*std::pow(x-x0,2)+b),QPointF(ball->getVel().rx(),2*a*(x-x0)*directionSign)));
}

void Model::step(){
    qreal newX = ball->getPos().rx() + ball->getVel().rx();
    Ball* newBall = ballFunction(newX);
    QPointF ballVel = newBall->getVel();
    int radius = ball->getRadius();
    QPointF newPos = newBall->getPos();
    if ((newPos.ry()>height-radius and ballVel.ry()>0) or (newPos.ry()<radius and ballVel.ry()<0)){
        std::cout << "top/bottom collision\n";
        ballVel.setY(-ballVel.y());
        if (newPos.y()>height-radius){
            newPos.setY(2*(height-radius)-newPos.y());
        } else{
            newPos.setY(-newPos.y());
        }
        ballVel = ballVel*95/100;
        trajectoryParameters = computeTrajectory(new Ball(newPos,ballVel,radius), gravity);
    }
    if ((newPos.rx()>width-radius and ballVel.rx()>0) or (newPos.rx()<radius and ballVel.rx()<0)){
        std::cout << "side collision\n";
        ballVel.setX(-ballVel.x());
        if (newPos.x()>width-radius){
            newPos.setX(2*(width-radius)-newPos.x());
        } else{
            newPos.setX(-newPos.x());
        }
        ballVel = ballVel*95/100;
        trajectoryParameters = computeTrajectory(new Ball(newPos,ballVel,radius), gravity);
    }
    ball->setPos(newPos);
    ball->setVel(ballVel);
    delete newBall;
}


void Model::oldStep(){
    QPointF ballPos = ball->getPos();
    QPointF ballVel = ball->getVel();
    QPointF newPos = ballPos + ballVel;
    int radius = ball->getRadius();
    //printf("Ball x speed is: %f\n",ballVel.rx());
    //printf("Ball y speed is: %f\n",ballVel.ry());
    if ((newPos.ry()>height-radius and ballVel.ry()>0) or (newPos.ry()<radius and ballVel.ry()<0)){
        ballVel.setY(-ballVel.y());
        if (newPos.y()>height-radius){
            newPos.setY(2*(height-radius)-newPos.y());
        } else{
            newPos.setY(-newPos.y());
        }
        ballVel = ballVel*9/10;
    }
    if ((newPos.rx()>width-radius and ballVel.rx()>0) or (newPos.rx()<radius and ballVel.rx()<0)){
        ballVel.setX(-ballVel.x());
        if (newPos.x()>width-radius){
            newPos.setX(2*(width-radius)-newPos.x());
        } else{
            newPos.setX(-newPos.x());
        }
        ballVel = ballVel*9/10;
    }
    ball->setPos(newPos);
    ballVel.setY(ballVel.y() + gravity);
    ball->setVel(ballVel);
    trajectoryParameters = computeTrajectory(ball,gravity);
}
