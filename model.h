#ifndef MODEL_H
#define MODEL_H
#include "ball.h"
#include "frame.h"

class Model
{
public:
    Model();
    QPointF getBallPos();
    std::vector<QPointF> getFrameVertices();
    std::tuple<float, float, float> getTrajectoryParameters();
    void oldStep();
    void step();
    //std::tuple<float, float, float> computeTrajectory(float x, float y, float dx, float dy, int g);


private:
    std::tuple<float, float, float> computeTrajectory(Ball* ball, int g);
    Ball* ballFunction(qreal x);
    Ball* ball;
    Frame* frame;
    std::tuple<float, float, float> trajectoryParameters;
    int gravity;
    int stepGap;
    int width;
    int height;
};

#endif // MODEL_H
