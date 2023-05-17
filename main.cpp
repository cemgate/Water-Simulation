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
    mainWindow.resize(1300,1100);


    // Tworzenie widoku graficznego
    QGraphicsView view(&mainWindow);
    view.setGeometry(10, 50, 1000, 1000);
    view.setRenderHint(QPainter::Antialiasing);

    // Tworzenie sceny graficznej
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 900, 900);

    // Tworzenie kropli wody
     std::vector<water*> particles;
    water waterDrop(0, 0, 20, 20);
    waterDrop.setPos(100,100);
    particles.push_back(&waterDrop);
    water waterDrop2(0, 0, 20, 20);
    waterDrop2.setPos(100,110);
    particles.push_back(&waterDrop2);


    // Dodanie kropli wody do sceny
    scene.addItem(&waterDrop);
    scene.addItem(&waterDrop2);


    // Ustawienie sceny graficznej dla widoku graficznego
    view.setScene(&scene);

    // Tworzenie animacji ruchu kropli wody
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]()
    {
        if(mainWindow.isStart)
        {
            particles[0]->moveBy(2,2);
            particles[1]->moveBy(2,2);
            qDebug() << distance(particles[0],particles[1]);


        }
    });

    timer.start(10);

    mainWindow.show();
    return a.exec();
}
