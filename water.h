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
};

void SPH(std::vector<water*> &particles);
double distance(const water* p1,const water* p2);



#endif // WATER_H
