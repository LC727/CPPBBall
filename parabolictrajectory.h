#ifndef PARABOLICTRAJECTORY_H
#define PARABOLICTRAJECTORY_H
#include <vector>
#include <QPointF>
#include <tuple>

class ParabolicTrajectory
{
public:
    ParabolicTrajectory();
    std::vector<QPointF> getTrajectory();

private:
    std::vector<QPointF> trajectory;
    std::vector<QPointF> computeTrajectory;
    std::tuple<float,float,float> trajectoryParameters;
    std::tuple<float,float,float> computeTrajectoryParameters(QPointF ballPos, QPointF ballVel, int g);

};

#endif // PARABOLICTRAJECTORY_H
