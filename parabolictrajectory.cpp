#include "ParabolicTrajectory.h"

ParabolicTrajectory::ParabolicTrajectory(float a, float x0, float b){
    trajectoryParameters.a = a;
    trajectoryParameters.x0 = x0;
    trajectoryParameters.b = b;
}

std::vector<QPointF> ParabolicTrajectory::getTrajectory(){
    return(trajectory);
}

std::vector<QPointF> ParabolicTrajectory::computeTrajectory(float x1, float x2, int nsteps){
    qreal step = (x2-x1) / (nsteps+1);
    float a = trajectoryParameters.a;
    float x0 = trajectoryParameters.x0;
    float b = trajectoryParameters.b;
    qreal x = x1;
    std::vector<QPointF> newTrajectory;
    for(int i = 0 ; i<nsteps+1 ; i++)
    {
        qreal y = a*pow((x-x0),2)+b;
        newTrajectory.push_back(QPointF(x,y));
        x += step;
    }
    return(newTrajectory);
}

PTParameters ParabolicTrajectory::computeTrajectoryParameters(QPointF ballPos, QPointF ballVel, int g){
    // Veryfying that dx is not 0
    if (std::abs(ballVel.rx()) < 1e-10) {
        throw std::invalid_argument("dx cannot be equal to 0 for this calculation");
    }
    float a = g / (2.0 * ballVel.rx() * ballVel.rx());
    float x0 = ballPos.rx() - (ballVel.rx() * ballVel.ry()) / g;
    float b = ballPos.ry() - a * std::pow(ballPos.rx() - x0, 2);
    PTParameters trajectoryParameters = {a,x0,b};
    return(trajectoryParameters);
}
