#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include<QDebug>
#include <QTimer>
#include <QRandomGenerator>
#include <Dense>
#include <cstdlib>

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

/**
 * @class water
 * @brief Klasa reprezentująca kroplę wody.
 */
class water : public QGraphicsEllipseItem
{
public:
/**
     * @brief Konstruktor klasy water.
     * @param x Pozycja x kropli wody.
     * @param y Pozycja y kropli wody.
     * @param width Szerokość kropli wody.
     * @param height Wysokość kropli wody.
     */
    water(float x, float y, qreal width, qreal height) :
        QGraphicsEllipseItem(x, y, width, height)
    {
        // Ustawienie koloru krawędzi i wypełnienia kropli wody
        setPen(QPen(Qt::transparent));
        setBrush(QBrush(QColor(0, 0, 60, 255)));
        contactedParticles.reserve(8);
        contactedParticlesParameters.reserve(8);
    }
 float mass=1.0; /**< Masa kropli wody. */
    Eigen::Vector2d velocity={0.f,0.f}; /**< Wektor prędkości kropli wody. */
    Eigen::Vector2d force={0.f,0.f}; /**< Wektor siły działający na kroplę wody. */
    float rho=0; /**< Gęstość kropli wody. */
    float pressure=0; /**< Ciśnienie w kropli wody. */

    std::vector<Eigen::Vector2d> contactedParticles; /**< Wektor kontaktujących się cząstek. */
    std::vector<water*> contactedParticlesParameters; /**< Wektor wskaźników na parametry kontaktujących się cząstek. */

    bool isChecked=false; /**< Flaga określająca, czy kropla została sprawdzona. */

    /**
     * @brief Metoda zmieniająca kolor kropli wody.
     * @param controlerAcceleration Wektor przyspieszenia kontrolera.
     */
    void changeColor(Eigen::Vector2d siema);
};

/**
 * @brief Sprawdza granice sceny i obsługuje kolizje z nimi.
 * @param particles Wektor wskaźników na cząstki wody.
 * @param ax Wartość przyspieszenia w osi x.
 * @param ay Wartość przyspieszenia w osi y.
 */
void checkEdges(std::vector<water*> &particles, int ax, int ay);

/**
 * @brief Oblicza gęstość i ciśnienie cząstek wody.
 * @param particles Wektor wskaźników na cząstki wody.
 */
void calculateDensityPressure(std::vector<water*> &particles);

/**
 * @brief Oblicza siłę działającą na cząstki wody.
 * @param particles Wektor wskaźników na cząstki wody.
 */
void calculateForce(std::vector<water*> &particles);

/**
 * @brief Aktualizuje pozycję cząstek wody na podstawie obliczonych sił.
 * @param particles Wektor wskaźników na cząstki wody.
 * @param timeStep Krok czasowy.
 */
void updatePosition(std::vector<water*> &particles, qreal timeStep);

/**
 * @brief Dodaje cząstki wody do sceny.
 * @param particles Wektor wskaźnik
*/
void addToScene(std::vector<water*> &particles,QGraphicsScene &scene);

/**
 * @brief Funkcja do generowania cząstek wody.
 * @param particles Wektor wskaźników na cząstki wody.
 */
void generateWater(std::vector<water*> &particles);

/**
 * @brief Funkcja do usuniecia cząstek wody i wyczyszczenia wektora czastek.
 * @param particles Wektor wskaźników na cząstki wody.
 */
void clearWater(std::vector<water*> &particles);





#endif // WATER_H
