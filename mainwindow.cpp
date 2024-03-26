#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pGameManager_ = new GameManager();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::BuyItem(const int itemIndex){
    pGameManager_->BuyItem(itemIndex);
}

void MainWindow::BuyUpgrade(const int upgradeIndex){
    pGameManager_->BuyUpgrade(upgradeIndex);
}

void MainWindow::BuyTab(){
    pGameManager_->BuyTab();
}

void MainWindow::ButtonPressed(){
    return;
}

void MainWindow::TabChanged(const int tabIndex){
    return;
}
