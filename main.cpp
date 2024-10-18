/*#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}*/
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>
#include <QgsApplication.h>
#include <QgsMapCanvas.h>
#include <QgsVectorLayer.h>
#include <QgsCoordinateReferenceSystem.h>

int main(int argc, char *argv[]) {
    QgsApplication app(argc, argv);
    app.initQgis();

    QMainWindow mainWindow;
    QWidget *centralWidget = new QWidget(&mainWindow);
    mainWindow.setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QgsMapCanvas *mapCanvas = new QgsMapCanvas();
    layout->addWidget(mapCanvas);

    QgsVectorLayer *vectorLayer = new QgsVectorLayer("C:\Users\glebu\Documents\tiles\osm-2020-02-10-v3.11_russia_moscow.mbtiles", "My Shapefile Layer", "ogr");
    if (!vectorLayer->isValid()) {
        return -1;
    } else {
        mapCanvas->setLayers(QList<QgsMapLayer *>() << vectorLayer);
        mapCanvas->setExtent(vectorLayer->extent());
        mapCanvas->refresh();
    }

    // Параметры окна
    mainWindow.resize(800, 600);
    mainWindow.show();

    // Запуск приложения
    return app.exec();
}
