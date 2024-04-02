#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int score = 0;
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
    bool ok;
    QString windowName = QInputDialog::getText(this, "Nom de la fenêtre", "Entrez un nom pour la nouvelle fenêtre:", QLineEdit::Normal, "", &ok);
    pGameManager_->BuyTab(windowName);
    QWidget *newWidget = new QWidget();

    QWidget *originalWidget = ui->tabWidget->widget(0);
    newWidget->setLayout(originalWidget->layout());
    ui->tabWidget->addTab(newWidget,windowName);
    QPushButton *originalButton = originalWidget->findChild<QPushButton*>("pushButton"); // Remplacez "nom_du_bouton" par l'ID de votre bouton
    if (originalButton) {
        QPushButton *newButton = new QPushButton(originalButton->text(), newWidget);
        newButton->setGeometry(originalButton->geometry());
        QObject::connect(originalButton, &QPushButton::clicked, newButton, &QPushButton::clicked);
    }
    else{
        qDebug()<<"no button";
    }


    int newIndex = ui->tabWidget->indexOf(newWidget);

    TabChanged(newIndex);
}

void MainWindow::ButtonPressed(){
    pGameManager_->ButtonPressed();
    QString message = QString("score = %1").arg(scoreTest);
    ui->statusbar->showMessage(message);
    return;
}

void MainWindow::TabChanged(const int tabIndex){
    ui->tabWidget->setCurrentIndex(tabIndex);
    return;
}

void MainWindow::on_pushButton_6_clicked()
{
    BuyTab();
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    TabChanged(ui->tabWidget->currentIndex());
}


void MainWindow::on_pushButton_clicked()
{
    ButtonPressed();
}

