#ifndef PARABOLICTRAJECTORY_H
#define PARABOLICTRAJECTORY_H
#include <vector>
#include <QPointF>

struct PTParameters{
    float a;
    float x0;
    float b;
};

class ParabolicTrajectory
{
public:
    ParabolicTrajectory(float a, float x0, float b);
    std::vector<QPointF> getTrajectory();

private:
    std::vector<QPointF> trajectory;
    std::vector<QPointF> computeTrajectory(float x1, float x2, int nsteps = 100);
    PTParameters trajectoryParameters;
    PTParameters computeTrajectoryParameters(QPointF ballPos, QPointF ballVel, int g);

};

#endif // PARABOLICTRAJECTORY_H
