#ifndef CONTENER_H
#define CONTENER_H
#include "qgraphicsitem.h"
#include "QPainter"


class contener : public QGraphicsItem
{
public:
    QRectF boundingRect() const override
    {
        return QRectF(0, 0, 400, 400);  // Dostosuj wymiary prostokąta
    }

    void setRotationAngle(int degrees)
    {
        angle += degrees;
        update(); // Wywołanie funkcji update() spowoduje ponowne narysowanie obiektu
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);


        painter->eraseRect(boundingRect());


        // Rysowanie kontenera w kształcie prostokąta z przezroczystą górną ścianą
        QPainterPath path;
        path.moveTo(0, 0);
        path.lineTo(0, boundingRect().height());
        path.lineTo(boundingRect().width(), boundingRect().height());
        path.lineTo(boundingRect().width(), 0);

        QPen pen(Qt::black);
        pen.setWidth(4);

        QBrush brush(Qt::transparent);
        painter->fillPath(path, brush);

        painter->save(); // Zapisz aktualne ustawienia obiektu QPainter
        painter->setPen(pen);
        // Obrót rysunku o zadany kąt
        painter->translate(boundingRect().center());
        painter->rotate(angle);
        painter->translate(-boundingRect().center());

        painter->drawPath(path);

        painter->restore(); // Przywróć ustawienia obiektu QPainter sprzed obrótów
    }

private:
    int angle=0;
};

#endif // CONTENER_H
