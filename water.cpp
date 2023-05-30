#include "water.h"


void calculateDensityPressure(std::vector<water*> &particles)
{
    Eigen::Vector2d rij={0.f,0.f};

    for(auto& pi: particles)
    {
        pi->isChecked=false;
        pi->rho=0.f;

        for(auto& pj:particles)
            {

                rij={pj->x()-pi->x(),pj->y()-pi->y()};
                float r2=rij.squaredNorm();
                float r1=rij.norm();

                if(r2<HSQ)
                {
                    pi->rho+=MASS*POLY6*pow(HSQ-r2,3.f);
                }

                if(r1<H && &pi!=&pj)
                {
                    pi->contactedParticles.push_back(rij);
                    pi->contactedParticlesParameters.push_back(pj);
                }
            }

       pi->pressure=GAS_CONST*(pi->rho-REST_DENS);
       rij={0.f,0.f};

    }
}

void calculateForce(std::vector<water*> &particles)
{
    Eigen::Vector2d fpress(0.f,0.f);
    Eigen::Vector2d fvisc(0.f,0.f);
    Eigen::Vector2d fpress2Particle(0.f,0.f);
    Eigen::Vector2d fvisc2Particle(0.f,0.f);

    for(auto& pi:particles)
    {

       for(int i=0;i<pi->contactedParticles.size();i++)
        {
            if(pi->contactedParticlesParameters[i]->isChecked==false)
            {
                float r=pi->contactedParticles[i].norm();
                fpress += -pi->contactedParticles[i].normalized()*MASS*(pi->pressure+pi->contactedParticlesParameters[i]->pressure)/(2.f*pi->contactedParticlesParameters[i]->rho)*SPIKY_GRAD*pow(H-r,3.f);
                fvisc += VISC * MASS * (pi->contactedParticlesParameters[i]->velocity - pi->velocity) / pi->contactedParticlesParameters[i]->rho * VISC_LAP * (H - r);
                fpress2Particle = pi->contactedParticles[i].normalized()*MASS*(pi->pressure+pi->contactedParticlesParameters[i]->pressure)/(2.f*pi->rho)*SPIKY_GRAD*pow(H-r,3.f);
                fvisc2Particle = -VISC * MASS * (pi->contactedParticlesParameters[i]->velocity - pi->velocity) / pi->rho * VISC_LAP * (H - r);
            }

            pi->contactedParticlesParameters[i]->force.x()+=fpress2Particle.x()+fvisc2Particle.x();
            pi->contactedParticlesParameters[i]->force.y()+=fpress2Particle.y()+fvisc2Particle.y();
            fpress2Particle={0.f,0.f};
            fvisc2Particle={0.f,0.f};
        }

        float fgrav = G * MASS / pi->rho;
        pi->force.x() += fpress.x() + fvisc.x() ;
        pi->force.y() += fpress.y() + fvisc.y() + fgrav;
        pi->contactedParticles.clear();
        pi->contactedParticlesParameters.clear();
        pi->isChecked=true;
        fpress={0.f,0.f};
        fvisc={0.f,0.f};
    }
}

void checkEdges(std::vector<water*> &particles)
{
    for(auto& i:particles)
    {

        i->velocity+=DT*i->force/i->rho;
        i->force={0.f,0.f};

        i->moveBy(i->velocity.x()*DT,i->velocity.y()*DT);

        if(i->x()>980)
        {
            i->setPos(980,i->y());
            i->velocity.x()*=-0.7;
        }
        if(i->x()<0)
        {
            i->setPos(0,i->y());
            i->velocity.x()*=-0.7;
        }
        if(i->y()>980)
        {
            i->setPos(i->x(),980);
            i->velocity.y()*=-0.7;
        }
        if(i->y()<0)
        {
            i->setPos(i->x(),0);
            i->velocity.y()*=-0.7;
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
        w->setPos(i*10,980);
        particles.push_back(w);

        water* e=new water(0,0,20,20);
        e->setPos(i*10,900);
        particles.push_back(e);

        water* s=new water(0,0,20,20);
        s->setPos(i*10,100);
        particles.push_back(s);

        water* t=new water(0,0,20,20);
        t->setPos(i*10,300);
        particles.push_back(t);

    }
}





