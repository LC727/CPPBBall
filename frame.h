#ifndef FRAME_H
#define FRAME_H
#include "vector"
#include "QPointF"

class Frame
{
public:
    Frame(int nVertices = 4, float angle = 0, float rotationSpeed = 0.1);
    int getNVertices();
    int setNVertices(int newNVertices);
    float getAngle();
    float setAngle(float angle);
    float getRotationSpeed();
    float setRotationSpeed(float newRotationSpeed);
    std::vector<QPointF> getVertices();
    void remapVertices();

private:
    int nVertices;
    float angle;
    float rotationSpeed;
    std::vector<QPointF> vertices;

};

#endif // FRAME_H
