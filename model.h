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
    void step();
    std::tuple<float, float, float> trajectoryParameters(float x, float y, float dx, float dy, int g);
    std::tuple<float, float, float> trajectoryParameters(Ball ball, int g);


private:
    Ball* ball;
    Frame* frame;
    int gravity;
};

#endif // MODEL_H
