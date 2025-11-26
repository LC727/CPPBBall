#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QGridLayout>
#include "windows.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    renderArea = new RenderArea;
    this->layout()->addWidget(renderArea);
    renderArea->update();
    shapeChanged();
    penChanged();
    brushChanged();
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
        renderArea->setBrush(QBrush(Qt::green, style));
    }
}

void MainWindow::animate(){
    int g = 10;
    int x = 190;
    int y = 90;
    int dx = 5;
    int dy = -30;
    while (true){
        QPoint ballPos(x, y);
        x += dx;
        y += dy;
        dy += g;
        Sleep(500);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

