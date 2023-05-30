#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include<QDebug>
#include <QTimer>
#include <QRandomGenerator>
#include <Eigen/Dense>

#ifndef WATER_H
#define WATER_H
const static float G=9.81f;            // gravity
const static float REST_DENS = 300.f;  // rest density
const static float GAS_CONST = 2000.f; // const for equation of state
const static float H = 16.f;           // kernel radius
const static float HSQ = H * H;        // radius^2 for optimization
const static float MASS = 2.5f;        // assume all particles have the same mass
const static float VISC = 200.f;       // viscosity constant
const static float DT = 0.0007f;       // integration timestep


// smoothing kernels defined in Müller and their gradients
// adapted to 2D per "SPH Based Shallow Water Simulation" by Solenthaler et al.
const static float POLY6 = 4.f / (M_PI * pow(H, 8.f));
const static float SPIKY_GRAD = -10.f / (M_PI * pow(H, 5.f));
const static float VISC_LAP = 40.f / (M_PI * pow(H, 5.f));

class water : public QGraphicsEllipseItem
{
public:
    water(float x, float y, qreal width, qreal height) :
        QGraphicsEllipseItem(x, y, width, height)
    {
        // Ustawienie koloru krawędzi i wypełnienia kropli wody
        setPen(QPen(Qt::transparent));
        setBrush(QBrush(QColor(255, 120, 255, 255)));
        contactedParticles.reserve(8);
        contactedParticlesParameters.reserve(8);
    }

    float mass=1.0;
    Eigen::Vector2d velocity={0.f,0.f};
    Eigen::Vector2d force={0.f,0.f};
    float rho=0;
    float pressure=0;

    std::vector<Eigen::Vector2d> contactedParticles;
    std::vector<water*> contactedParticlesParameters;

    bool isChecked=false;
};

void checkEdges(std::vector<water*> &particles);
double distance(const water* p1,const water* p2);
double squaredNorm(const water* p1, const water* p2);
void calculateDensityPressure(std::vector<water*> &particles);
void calculateForce(std::vector<water*> &particles);
void updatePosition(std::vector<water*> &particles, qreal timeStep);
void addToScene(std::vector<water*> &particles,QGraphicsScene &scene);
//void addParticles(std::vector<water*> &particles, const int numberOfParticles);
void generateWater(std::vector<water*> &particles);






#endif // WATER_H
