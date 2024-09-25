#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "window.hpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto window = std::make_unique<Window>(this);
    setCentralWidget(window.release()); // takes ownership
}

MainWindow::~MainWindow()
{
    delete ui;
}

