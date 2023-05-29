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




    // Tworzenie animacji ruchu kropli wody
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]()
    {
        if(mainWindow.isStart)
        {
            calculateDensityPressure(particles);
            calculateForce(particles);
            checkEdges(particles);
        }
    });

    timer.start(0);


    mainWindow.show();
    return a.exec();
}
