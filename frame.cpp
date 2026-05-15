#include "frame.h"
#include <math.h>

Frame::Frame(int nVertices, float angle, float rotationSpeed): nVertices(nVertices), angle(angle), rotationSpeed(rotationSpeed){
    for (int i=0;i<nVertices;i++){
        float offsetAngle = i*M_PI/nVertices;
        QPointF newPoint = QPointF(240,320)+100*QPointF(cos(offsetAngle),sin(offsetAngle));
        vertices.push_back(newPoint);
    }
}

void Frame::remapVertices(){
    for (int i=0;i<nVertices;i++){
        float offsetAngle = angle + i*M_PI/nVertices;
        QPointF newPoint = QPointF(240,320)+100*QPointF(cos(offsetAngle),sin(offsetAngle));
        vertices.push_back(newPoint);
    }
}

int Frame::getNVertices(){
    return nVertices;
}

int Frame::setNVertices(int newNVertices){
    nVertices = newNVertices;
    remapVertices();
    return nVertices;
}

float Frame::getAngle(){
    return angle;
}

float Frame::setAngle(float newAngle){
    angle = newAngle;
    remapVertices();
    return angle;
}

float Frame::getRotationSpeed(){
    return rotationSpeed;
}
float Frame::setRotationSpeed(float newRotationSpeed){
    rotationSpeed = newRotationSpeed;
    return rotationSpeed;
}

std::vector<QPointF> Frame::getVertices(){
    return vertices;
}
