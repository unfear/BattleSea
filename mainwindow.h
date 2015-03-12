#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "seawidget.h"
#include "shipslist.h"
#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    /// add menu to window
    void setupMenus();
    /// add ships list, battlefields to window
    void setupWidgets();

    /// 1-2-3-4 Deck ships icons
    /// TODO: move to ShipsList class
    QPixmap     mOneDeckShipImage;
    QPixmap     mTwoDwckShipImage;
    QPixmap     mThreeDeckShipImage;
    QPixmap     mFourDeckShipImage;

    /// widget contain ships icons
    ShipsList *shipsList;
    /// user battlefield
    SeaWidget *seaWidget;
    /// enemy battlefield
    SeaWidget *seaWidgetEnemy;
    /// define ships count. usually is 4
    const int mShipsNumber;

public slots:
    /// load image from resources
    QPixmap openImage(const QString &path = QString());
    /// add ships to ShipsList
    void setupShips();
};

#endif // MAINWINDOW_H
