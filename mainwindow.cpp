#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "window.hpp"
#include <QPainter>
#include <osmscoutmapqt/MapPainterQt.h>
#include <osmscoutmap/MapService.h>
#include <osmscoutclientqt/OSMScoutQt.h>
#include <osmscout/projection/Projection.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPainter qpainter(this);

    //Разобраться с тем что делают {NAME}Ref классы - Скорее всего Ref классы это умные указатели.
    osmscout::StyleConfig* style; //Класс определяющий стиль карты https://libosmscout.sourceforge.net/documentation/stylesheet/
    osmscout::MapPainterQt* painter; //Класс, рисующий карту в Qt виджетах
    osmscout::MapService* mapservice; //Не совсем ясно, но видимо позволяет работать с свойствами карты
    osmscout::Database* database; //Класс, позволяющий загрузить в себя дб карты(видимо те же тайлы), но не совсем ясно дб какого формата подходят, есть что-то об этом в документации - https://libosmscout.sourceforge.net/documentation/database/
    osmscout::MapRenderer* render; //Класс работающий с QT API, прогружает QML карту, не ясно позволяет ли работать с оффлайн ресурсами, тк в примере в документации в качестве источника приводится флаг provider с онлайн источником https://libosmscout.sourceforge.net/documentation/qt_qml_api/
    osmscout::BasemapDatabase* basemapdatabase; //Не понял точно из описания, либо дб, которая позволяет соединить все дб, либо дб для загрузки всей информации о карте
    osmscout::MapDownloader* mapDownloader; //Мэнэджер всех загруженных в проект датабаз, также является частью функционала Qt QML API, как и render
    osmscout::MapData* mapdata; //Данные о карте, связывается с БД
    osmscout::Tile* tile; //Тайл карты?
    osmscout::Projection* projection; //По всей видимости это класс работающий с геокоординатами и пикселями
    osmscout::MapParameter* mapParameter;//Рисование на карте

    osmscout::MapServiceRef mapServiceRef;
    //Верхняя и нижняя запись это одно и тоже
    std::shared_ptr<osmscout::MapService> mapService = std::make_shared<osmscout::MapService>();

    // Настройка путей к данным карты
    database->Open("C:\\Users\\glebu\\Documents\\tiles\\osm-2020-02-10-v3.11_russia_moscow.mbtiles"); //Надо понять как из database засунуть данные в mapdata
    painter->DrawMap(projection, mapParameter, mapdata, qpainter); //Жалуется на то, что projection, mapparameter и mapdata не const. Надо понять как связать projection и mapparameter, чтобы их можно было использовать в отрисовке


    database->Close();
    auto window = std::make_unique<Window>(this);
    setCentralWidget(window.release()); // takes ownership
}

MainWindow::~MainWindow()
{
    delete ui;
}

