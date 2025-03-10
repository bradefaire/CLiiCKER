#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>

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

    printItem();

    ui->label_3->setText(QString("%1").arg(pGameManager_->pplayer_->getWindowPrice(pGameManager_->pplayer_->getNbWindow())));

    ptimer = new QTimer(this);

    const int interval = 1;
    ptimer->setInterval(interval);
    connect(ptimer,SIGNAL(timeout()),this,SLOT(Update()));
    ptimer->start();

    QMessageBox msgBox;
    msgBox.setText("Loading Game");
    msgBox.setInformativeText("Do you want to load an existing game ?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int ans = msgBox.exec();
    if (ans == QMessageBox::Yes){
        on_actionOpen_triggered();
    }
    else{
        on_actionCreate_triggered();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    delete ptimer;
}

void MainWindow::printItem()
{
    QString itemName1 = ui->item1->title();
    Item * pitem1 = pGameManager_->pplayer_->getCurrentWindow()->getItem(itemName1);
    int quantity1 = pGameManager_->pplayer_->getCurrentWindow()->getItemQuantity(pitem1);
    int level1 = pGameManager_->pplayer_->getCurrentWindow()->getUpgradeLevel(pitem1->getUpgrade());
    qDebug() << level1 << "level1";
    qDebug() << quantity1 << "quantity1";

    ui->number_10->setText(QString("%1").arg(getPriceBuy(ui->item1->title(),quantity1)));//item
    ui->number_7->setText(QString("%1").arg(quantity1));
    ui->number_8->setText(QString("%1").arg(getPriceUpdate(ui->item1->title(),level1)));//upgrade
    ui->number_9->setText(QString("%1").arg(level1));

    QString itemName2 = ui->item2->title();
    Item * pitem2 = pGameManager_->pplayer_->getCurrentWindow()->getItem(itemName2);
    int quantity2 = pGameManager_->pplayer_->getCurrentWindow()->getItemQuantity(pitem2);
    int level2 = pGameManager_->pplayer_->getCurrentWindow()->getUpgradeLevel(pitem2->getUpgrade());

    ui->number->setText(QString("%1").arg(getPriceBuy(ui->item2->title(),quantity2)));//item
    ui->number_5->setText(QString("%1").arg(quantity2));
    ui->number_2->setText(QString("%1").arg(getPriceUpdate(ui->item2->title(),level2)));//upgrade
    ui->number_6->setText(QString("%1").arg(level2));
}

int MainWindow::getPriceBuy(const QString & itemName,int quantity)
{
    return pGameManager_->pplayer_->getCurrentWindow()->getItem(itemName)->Price(quantity);
}

int MainWindow::getPriceUpdate(const QString & itemName,int quantity)
{
    return pGameManager_->pplayer_->getCurrentWindow()->getUpgrade(itemName)->Price(quantity);
}

void MainWindow::BuyItem(const QString & itemName,int n){
    printScore();
    if (!pGameManager_->BuyItem(itemName)) return;
    int price;

    if (n==1){
        Item * pitem1 = pGameManager_->pplayer_->getCurrentWindow()->getItem(itemName);
        int quantity1 = pGameManager_->pplayer_->getCurrentWindow()->getItemQuantity(pitem1);

        price = getPriceBuy(itemName,quantity1);
        ui->number_10->setText(QString("%1").arg(price));
        ui->number_7->setText(QString("%1").arg(quantity1));
    }
    else if (n==2){
        Item * pitem2 = pGameManager_->pplayer_->getCurrentWindow()->getItem(itemName);
        int quantity2 = pGameManager_->pplayer_->getCurrentWindow()->getItemQuantity(pitem2);
        price = getPriceBuy(itemName,quantity2);
        ui->number->setText(QString("%1").arg(price));
        ui->number_5->setText(QString("%1").arg(quantity2));
    }
    else qDebug()<<"t'es nul/le";

}

void MainWindow::BuyUpgrade(const QString & itemName, int n){
    if (!pGameManager_->BuyUpgrade(itemName)) return;
    int levelPrice;

    if (n==1){
        Item * pitem1 = pGameManager_->pplayer_->getCurrentWindow()->getItem(itemName);
        int level1 = pGameManager_->pplayer_->getCurrentWindow()->getUpgradeLevel(pitem1->getUpgrade());
        levelPrice = getPriceUpdate(itemName,level1);
        ui->number_8->setText(QString("%1").arg(levelPrice));
        ui->number_9->setText(QString("%1").arg(level1));
    }
    else if (n==2){
        Item * pitem2 = pGameManager_->pplayer_->getCurrentWindow()->getItem(itemName);
        int level2 = pGameManager_->pplayer_->getCurrentWindow()->getUpgradeLevel(pitem2->getUpgrade());
        levelPrice = getPriceUpdate(itemName,level2);
        ui->number_2->setText(QString("%1").arg(levelPrice));
        ui->number_6->setText(QString("%1").arg(level2));
    }
    else qDebug()<<"t'es nul/le";
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
        ui->tabWidget->setCurrentIndex(newIndex);
        TabChanged(newIndex);

        int newPrice = pGameManager_->pplayer_->getWindowPrice(pGameManager_->pplayer_->getNbWindow());
        ui->label_3->setText(QString("%1").arg(newPrice));
    }
    else qDebug()<<"Achat impossible";
}

void MainWindow::printScore(){
    QString message = QString("%1").arg(pGameManager_->getScore());
    ui->label_11->setText(message);
}

void MainWindow::ButtonPressed(){
    pGameManager_->ButtonPressed();
    printScore();
    return;
}

void MainWindow::TabChanged(const int tabIndex){
    qDebug() << "change tab to index"<< tabIndex;

    pGameManager_->ChangeTab(tabIndex);
    printItem();
    return;
}

void MainWindow::on_pushButton_6_clicked()
{
    BuyTab();
    printScore();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    qDebug() << "index current tab "<< index;
    TabChanged(index);
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

void MainWindow::Update(){
    pGameManager_->Update(ptimer->interval());
    printScore();
}

void MainWindow::on_actionSave_triggered()
{
    QString playerName = pGameManager_->pplayer_->getName();
    bool noName = (playerName.isNull() || playerName.isEmpty());
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save File"),
                                                    noName ? "New Game" : playerName,
                                                    tr("Text files (*.json")
                                                    );
    if (fileName != nullptr){
        if (noName){
            QFileInfo fi(fileName);
            pGameManager_->pplayer_->setName( fi.baseName() );
        }
        pGameManager_->SaveGame(fileName);
        printItem();
        printScore();
    }
}


void MainWindow::on_actionOpen_triggered()
{
    QString playerName = pGameManager_->pplayer_->getName();
    if (! (playerName.isNull())){
        QMessageBox msgBox;
        msgBox.setText("All unsaved data will be lost");
        msgBox.setInformativeText("Are you sure you want to open a new file ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        int ans = msgBox.exec();
        if (ans == QMessageBox::Cancel){
            return;
        }
    }
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "",
                                                    "Text files (*.json)");
    if (fileName != nullptr){
        pGameManager_->LoadGame(fileName);
        printScore();
        printItem();
    }

}


void MainWindow::on_actionCreate_triggered()
{
    QString playerName = pGameManager_->pplayer_->getName();
    if (! (playerName.isNull())){
        QMessageBox msgBox;
        msgBox.setText("All unsaved data will be lost");
        msgBox.setInformativeText("Are you sure you want to create a new file ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        int ans = msgBox.exec();
        if (ans == QMessageBox::Cancel){
            return;
        }
    }
    bool ok;
    QString newName = QInputDialog::getText(this, "Player Name", "Please, enter your new game name :", QLineEdit::Normal, "", &ok);
    if(ok)
    {
        if (newName.isEmpty() || newName.isNull()){
            newName = "New Game";
        }
        pGameManager_->NewGame(newName);
        printItem();
        printScore();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if (QMessageBox::Yes == QMessageBox::question(this, "All unsaved data will be lost", "Are you sure you want to Quit?", QMessageBox::Yes | QMessageBox::No))
    {
        event->accept();
    }

}
