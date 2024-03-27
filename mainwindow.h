#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void BuyItem(const QString & itemName);
    void BuyUpgrade(const QString & upgradeName);
    void BuyTab();
    void TabChanged(const int);//Tab index

private:
    Ui::MainWindow *ui;
    GameManager *pGameManager_;
};
#endif // MAINWINDOW_H
