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

void MainWindow::BuyItem(const QString & itemName){
    pGameManager_->BuyItem(itemName);
}

void MainWindow::BuyUpgrade(const QString & upgradeName){
    pGameManager_->BuyUpgrade(upgradeName);
}

void MainWindow::BuyTab(){
    pGameManager_->BuyTab(QString("New Tab"));
}

void MainWindow::ButtonPressed(){
    return;
}

void MainWindow::TabChanged(const int tabIndex){
    return;
}
