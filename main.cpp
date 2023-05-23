#include "mainwindow.h"
#include "water.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <qvector>
#include<iostream>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages)
    {
        const QString baseName = "VV_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    // Tworzenie okna głównego
    MainWindow mainWindow;
    mainWindow.setWindowTitle("VV");
    mainWindow.resize(1500,1200);


    // Tworzenie widoku graficznego
    QGraphicsView view(&mainWindow);
    view.setGeometry(10, 50, 1002, 1002 );
    view.setRenderHint(QPainter::Antialiasing);

    // Tworzenie sceny graficznej
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 1000, 1000);

    // Tworzenie kropli wody
     std::vector<water*> particles;



    generateWater(particles);
    addToScene(particles,scene);


    // Ustawienie sceny graficznej dla widoku graficznego

    view.setScene(&scene);
    qreal smoothingLength=1;
    qreal pressureConstant=1.0;
    qreal restDensity=1000.0;
    qreal timeStep=0.05;




    // Tworzenie animacji ruchu kropli wody
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]()
    {
        if(mainWindow.isStart)
        {

            for(int i=0;i<particles.size();i++)
            {
                particles[i]->velocityY+=.981;
                calculateDensity(particles[i],particles,smoothingLength,restDensity);
            }
            for(int i=0;i<particles.size();i++)
            {
                calculateForce(particles[i],particles,smoothingLength,restDensity,pressureConstant);
            }
            updatePosition(particles,timeStep);
            checkEdges(particles);

        }
    });

    timer.start(10);


    mainWindow.show();
    return a.exec();
}
