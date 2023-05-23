#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include<QDebug>
#include <QTimer>
#include <QRandomGenerator>

#ifndef WATER_H
#define WATER_H


class water : public QGraphicsEllipseItem
{
public:
    water(qreal x, qreal y, qreal width, qreal height) :
        QGraphicsEllipseItem(x, y, width, height)
    {
        // Ustawienie koloru krawędzi i wypełnienia kropli wody
        setPen(QPen(Qt::transparent));
        setBrush(QBrush(QColor(255, 120, 255, 255)));
    }
    qreal mass=1.0;
    qreal density;
    qreal velocityX=0;
    qreal velocityY=0;
};

void checkEdges(std::vector<water*> &particles);
double distance(const water* p1,const water* p2);
void calculateDensity(water* p1,std::vector<water*> &particles,qreal smoothingLength,qreal restDensity);
void calculateForce(water* p1,std::vector<water*> &particles,qreal smoothingLength,qreal restDensity, qreal pressureConstant);
void updatePosition(std::vector<water*> &particles, qreal timeStep);
void addToScene(std::vector<water*> &particles,QGraphicsScene &scene);
void addParticles(std::vector<water*> &particles, const int numberOfParticles);
void generateWater(std::vector<water*> &particles);






#endif // WATER_H
