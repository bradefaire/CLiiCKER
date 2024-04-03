#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scoreTest = 0;
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
    if(pGameManager_->BuyTab(windowName))
    {
        QWidget *newWidget = new QWidget();

        QWidget *originalWidget = ui->tabWidget->widget(0);
        newWidget->setLayout(originalWidget->layout());
        ui->tabWidget->addTab(newWidget,windowName);
        QPushButton *originalButton = originalWidget->findChild<QPushButton*>("pushButton"); // Remplacez "nom_du_bouton" par l'ID de votre bouton
        if (originalButton) {
            QPushButton *newButton = new QPushButton(originalButton->text(), newWidget);
            newButton->setGeometry(originalButton->geometry());

            connect(originalButton, &QPushButton::clicked, this, &MainWindow::ButtonPressed);

            connect(newButton, &QPushButton::clicked, this, &MainWindow::ButtonPressed);
        }
        else{
            qDebug()<<"no button";
        }

        int newIndex = ui->tabWidget->indexOf(newWidget);

        TabChanged(newIndex);
    }
    else qDebug()<<"ce nom de tab existe déjà";
}

void MainWindow::ButtonPressed(){
    scoreTest++;
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


void MainWindow::on_lineEdit_editingFinished()
{
    QString tabName = ui->lineEdit->text();

    int tabIndex = -1;
    for (int i = 0; i < ui->tabWidget->count(); ++i) {
        if (ui->tabWidget->tabText(i) == tabName) {
            tabIndex = i;
            break;
        }
    }

    if (tabIndex != -1) {
        ui->tabWidget->setCurrentIndex(tabIndex);
    } else {
        qDebug() << "La tab correspondante n'a pas été trouvée.";
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    //button item2
    QString name = ui->item2->title();
    BuyItem(name);
}

void MainWindow::on_pushButton_5_clicked()
{
    //button item2
    QString name = ui->item1->title();
    BuyItem(name);
}


void MainWindow::on_pushButton_4_clicked()
{
    //iupgrade item 1
     QString name = ui->item1->title();
    BuyUpgrade(name);
}

