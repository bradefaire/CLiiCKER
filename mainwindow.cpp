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

    quantityItem1 = 0;
    levelUpgrade1 = 0;
    quantityItem2 = 0;
    levelUpgrade2 = 0;

    printScore();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::BuyItem(const QString & itemName,int n){
    printScore();
    int price;

    if (n==1) price = pGameManager_->pplayer_->getCurrentWindow()->getItem(itemName)->Price(quantityItem1++);
    else price = pGameManager_->pplayer_->getCurrentWindow()->getItem(itemName)->Price(quantityItem2++);

    ui->number_10->setText(QString("%1").arg(price));
    pGameManager_->BuyItem(itemName);
}

void MainWindow::BuyUpgrade(const QString & itemName, int n){
    int level;

    if (n==1) level = pGameManager_->pplayer_->getCurrentWindow()->getUpgrade(itemName)->Price(levelUpgrade1++);
    else level = pGameManager_->pplayer_->getCurrentWindow()->getUpgrade(itemName)->Price(levelUpgrade2++);

    ui->number_10->setText(QString("%1").arg(level));
    pGameManager_->BuyUpgrade(itemName);
}

void MainWindow::BuyTab(){
    bool ok;
    QString windowName = QInputDialog::getText(this, "Nom de la fenêtre", "Entrez un nom pour la nouvelle fenêtre:", QLineEdit::Normal, "", &ok);
    if(pGameManager_->BuyTab(windowName)) //à modifier en try and catch
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

void MainWindow::printScore(){
    QString message = QString("score = %1").arg(pGameManager_->getScore());
    ui->statusbar->showMessage(message);
}
void MainWindow::ButtonPressed(){
    pGameManager_->ButtonPressed();
    printScore();
    return;
}

void MainWindow::TabChanged(const int tabIndex){
    ui->tabWidget->setCurrentIndex(tabIndex);
    return;
}

void MainWindow::on_pushButton_6_clicked()
{
    BuyTab();
    printScore();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    TabChanged(ui->tabWidget->currentIndex());
}

void MainWindow::on_pushButton_clicked()
{
    ButtonPressed();
    printScore();
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
    //button item 2
    QString name = ui->item2->title();
    BuyItem(name,2);
    printScore();
}

void MainWindow::on_pushButton_5_clicked()
{
    //button item 1
    QString name = ui->item1->title();
    BuyItem(name,1);
}

void MainWindow::on_pushButton_4_clicked()
{
    //upgrade item 1
    QString name = ui->item1->title();
    qDebug()<<name;
    BuyUpgrade(name,1);
    printScore();
}


void MainWindow::on_pushButton_3_clicked()
{
    //upgrade item2
    QString name = ui->item2->title();
    BuyUpgrade(name,2);
    printScore();
}

