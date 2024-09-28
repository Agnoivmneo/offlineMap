// Copyright (C) 2023 MapLibre contributors

// SPDX-License-Identifier: MIT

#include "window.hpp"

#include "mainwindow.h"

#include <QApplication>
#include <QKeyEvent>
#include <QMessageBox>
#include <QVBoxLayout>

Window::Window(MainWindow *mainWindow)
    : QWidget(mainWindow),
      m_mainWindowRef(mainWindow) {
    QMapLibre::Styles styles;
    //styles.append(QMapLibre::Style(":/russia_geojson_wgs84.geojson", "Demo Tiles"));
    //styles.append(QMapLibre::Style("D:/PROJECT/projects_Qt/testforqmaplibre/build-testforqmaplibre-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/style.json", "Demo Tiles"));

    QMapLibre::Settings settings;
    //settings.setStyles(styles);
    //settings.setDefaultZoom(5);
    //settings.setDefaultCoordinate(QMapLibre::Coordinate(43, 21));

    m_glWidget = std::make_unique<QMapLibre::GLWidget>(settings);

    m_layout = std::make_unique<QVBoxLayout>(this);
    m_layout->addWidget(m_glWidget.get());
    m_buttonDock = std::make_unique<QPushButton>(tr("Undock"), this);
    connect(m_buttonDock.get(), &QPushButton::clicked, this, &Window::dockUndock);
    m_layout->addWidget(m_buttonDock.get());

    setLayout(m_layout.get());

    this->show();

    setWindowTitle(tr("Hello QMapLibre"));
}

void Window::keyPressEvent(QKeyEvent *e) {
    QMapLibre::Map *map = m_glWidget->map();

    QFile styleFile(":/style.json");
    if (!styleFile.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open style file"));
        return;
    }

    QByteArray styleData = styleFile.readAll();
    styleFile.close();

    map->setStyleJson(styleData);
    map->setCoordinate(QMapLibre::Coordinate(43, 21));
    map->setZoom(10);
    //map->setStyleUrl("https://demotiles.maplibre.org/style.json");
    map->createRenderer();
    map->startStaticRender();
    if (e->key() == Qt::Key_Escape) {
        close();
    } else {
        QWidget::keyPressEvent(e);
    }
}

void Window::dockUndock() {
    if (parent() != nullptr) {
        setParent(nullptr);
        setAttribute(Qt::WA_DeleteOnClose);
        //move(QGuiApplication::primaryScreen()->size().width() / 2 - width() / 2,
        //     QGuiApplication::primaryScreen()->size().height() / 2 - height() / 2);
        m_buttonDock->setText(tr("Dock"));
        show();
    } else {
        if (m_mainWindowRef->centralWidget() == nullptr) {
            if (m_mainWindowRef->isVisible()) {
                setAttribute(Qt::WA_DeleteOnClose, false);
                m_buttonDock->setText(tr("Undock"));
                m_mainWindowRef->setCentralWidget(this);
            } else {
                QMessageBox::information(nullptr, tr("Cannot dock"), tr("Main window already closed"));
            }
        } else {
            QMessageBox::information(nullptr, tr("Cannot dock"), tr("Main window already occupied"));
        }
    }
}
