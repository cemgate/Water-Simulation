#include "water.h"


qreal distance(const water* p1,const water* p2)
{
    qreal dx = p2->x() - p1->x();
    qreal dy= p2->y() - p1->y();
    return std::sqrt(dx*dx+dy*dy)-p1->rect().width();
}


void SPH(std::vector<water*> &particles)
{

}

void run()
{

}



