#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QGridLayout>
#include <QTimer>
#include <chrono>
#include <ctime>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    renderArea = new RenderArea;
    model = new Model();
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::step));
    this->layout()->addWidget(renderArea);
    renderArea->update();
    timer->start(17);
}

void MainWindow::shapeChanged()
{
    RenderArea::Shape shape = RenderArea::Ellipse;
    renderArea->setShape(shape);
}

void MainWindow::penChanged()
{
    int width = 1;
    Qt::PenStyle style = Qt::PenStyle::SolidLine;
    Qt::PenCapStyle cap = Qt::PenCapStyle::RoundCap;
    Qt::PenJoinStyle join = Qt::PenJoinStyle::RoundJoin;

    renderArea->setPen(QPen(Qt::blue, width, style, cap, join));
}

void MainWindow::brushChanged()
{
    Qt::BrushStyle style = Qt::BrushStyle::Dense1Pattern;
    if (style == Qt::LinearGradientPattern) {
        QLinearGradient linearGradient(0, 0, 100, 100);
        linearGradient.setColorAt(0.0, Qt::white);
        linearGradient.setColorAt(0.2, Qt::green);
        linearGradient.setColorAt(1.0, Qt::black);
        renderArea->setBrush(linearGradient);
    } else if (style == Qt::RadialGradientPattern) {
        QRadialGradient radialGradient(50, 50, 50, 70, 70);
        radialGradient.setColorAt(0.0, Qt::white);
        radialGradient.setColorAt(0.2, Qt::green);
        radialGradient.setColorAt(1.0, Qt::black);
        renderArea->setBrush(radialGradient);
    } else if (style == Qt::ConicalGradientPattern) {
        QConicalGradient conicalGradient(50, 50, 150);
        conicalGradient.setColorAt(0.0, Qt::white);
        conicalGradient.setColorAt(0.2, Qt::green);
        conicalGradient.setColorAt(1.0, Qt::black);
        renderArea->setBrush(conicalGradient);
    } else if (style == Qt::TexturePattern) {
        renderArea->setBrush(QBrush(QPixmap(":/images/brick.png")));
    } else {
        renderArea->setBrush(QBrush(Qt::white, style));
    }
}

void MainWindow::step(){
    //auto start = std::chrono::system_clock::now();
    model->oldStep();
    QPointF newPos = model->getBallPos();
    renderArea->setBallPos(newPos.toPoint());
    std::tuple<float, float, float> trajectoryParameters = model->getTrajectoryParameters();
    renderArea->setTrajectoryParameters(trajectoryParameters);
    std::vector<QPointF> newVerticesF = model->getFrameVertices();
    std::vector<QPoint> newVertices;
    for (QPointF vertex : newVerticesF){
        newVertices.push_back(vertex.toPoint());
        }
    renderArea->setFrameVertices(newVertices);
    /*auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << elapsed_seconds.count() << std::endl;*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

