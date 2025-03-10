#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QCloseEvent>

#include "gamemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ButtonPressed();
    void BuyItem(const QString & itemName, int n);
    void BuyUpgrade(const QString & upgradeName, int n);
    void BuyTab();
    void TabChanged(const int);//Tab index

private slots:
    void on_pushButton_6_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_clicked();

    void on_lineEdit_editingFinished();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();
    void Update();


    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionCreate_triggered();

private:
    Ui::MainWindow *ui;
    GameManager *pGameManager_;
    QTimer * ptimer;

    int scoreTest;
    int quantityItem1;
    int levelUpgrade1;
    int quantityItem2;
    int levelUpgrade2;
    void printScore();
    int getPriceBuy(const QString & itemName,int quantity);
    int getPriceUpdate(const QString & itemName,int quantity);
    void printItem();
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
