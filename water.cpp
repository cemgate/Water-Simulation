#include "water.h"


qreal distance(const water* p1,const water* p2)
{
    qreal dx = p2->x() - p1->x();
    qreal dy= p2->y() - p1->y();
    return std::sqrt(dx*dx+dy*dy)-20;
}

void calculateDensity(water* p1,std::vector<water*> &particles,qreal smoothingLength,qreal restDensity)
{
    qreal density=0.0;
    for(auto& i:particles)
    {
        if(i!=p1)
        {
            qreal dist=distance(p1,i);
            if(dist<smoothingLength)
            {
                double q = 1.0 - (dist/smoothingLength);
                density+=i->mass*q*q;
            }
        }
    }
    p1->density=density+restDensity;
}

void calculateForce(water* p1,std::vector<water*> &particles,qreal smoothingLength,qreal restDensity, qreal pressureConstant)
{
    qreal pressure = pressureConstant * (p1->density-restDensity);
    qreal forceX=0.0;
    qreal forceY=0.0;
    for(auto& i:particles)
    {
        if(i!=p1)
        {
            qreal dist=distance(i,p1);
            if(dist<smoothingLength && dist!=0)
            {
                qreal q=10.0-(dist/smoothingLength);

                qreal pressureForce = -1*i->mass*(pressure/(2.0*i->density))*q*q*q;

                qreal viscosityForce =(i->mass/i->density)*(p1->velocityX-i->velocityX)*(1.0-q);

                forceX+=(pressureForce*(p1->x()-i->x()))/dist+viscosityForce*(p1->velocityX-i->velocityX);

                forceY+=(pressureForce*(p1->y()-i->y()))/dist+viscosityForce*(p1->velocityY-i->velocityY);


            }
        }
    }
    p1->velocityX+=10*forceX/p1->density;
    p1->velocityY+=10*forceY/p1->density;

}

void updatePosition(std::vector<water*> &particles, qreal timeStep)
{
    for(auto& i:particles)
    {
        i->moveBy(i->velocityX*timeStep,i->velocityY*timeStep);
    }
}


void checkEdges(std::vector<water*> &particles)
{
    for(auto& i:particles)
    {
        if(i->x()>980)
        {
            i->setPos(980,i->y());
            i->velocityX=-0.7*(i->velocityX);
        }
        if(i->x()<0)
        {
            i->setPos(0,i->y());
            i->velocityX=-0.7*(i->velocityX);
        }
        if(i->y()>980)
        {
            i->setPos(i->x(),980);
            i->velocityY=-0.7*(i->velocityY);
        }
        if(i->y()<0)
        {
            i->setPos(i->x(),0);
            i->velocityY=-0.7*(i->velocityY);
        }
    }
}

void addToScene(std::vector<water*> &particles,QGraphicsScene &scene)
{
    for(auto& i:particles)
    {
        scene.addItem(i);
    }
}

void generateWater(std::vector<water*> &particles)
{
    for(int i=0;i<100;i++)
    {
        water* w=new water(0,0,20,20);
        w->setPos(i*10,i*10);
        particles.push_back(w);
    }
}





