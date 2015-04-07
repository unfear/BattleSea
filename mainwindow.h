#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "seawidget.h"
#include "shipslist.h"
#include <memory>
#include <QPushButton>
#include <QLabel>
#include "utility.h"
#include "listener.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(APP_ROLE role, QWidget * parent = 0);

    ~MainWindow();
    
    /// set listener for data send notification
    void setListener(Listener * listener);

    /// check fired cell in seawidget
    void catchFireAndCheck(FireEvent eventData);

private:
    Ui::MainWindow * ui;

    /// add menu to window
    void setupMenus();

    /// add ships list, battlefields to window
    void setupWidgets();

    /// add Ready button
    void setupReadyButton();

    /// add role label
    void setupRoleLabel();

    /// 1-2-3-4 Deck ships icons
    /// TODO: move to ShipsList class
    QPixmap     mOneDeckShipImage;
    QPixmap     mTwoDwckShipImage;
    QPixmap     mThreeDeckShipImage;
    QPixmap     mFourDeckShipImage;

    /// widget contain ships icons
    ShipsList * shipsList;
    /// user battlefield
    SeaWidget * seaWidget;
    /// enemy battlefield
    SeaWidget * seaWidgetEnemy;
    /// define ships count. usually is 4
    const int mShipsNumber;
    /// Ready button
    QPushButton * mReadyBtn;
    /// client or server role label
    QLabel * mRoleLabel;
    /// client or server role
    APP_ROLE mRole;

public slots:
    /// load image from resources
    QPixmap openImage(const QString &path = QString());
    /// add ships to ShipsList
    void setupShips();

private slots:
    void handleButton();
signals:
    void readyToPlay();
};

#endif // MAINWINDOW_H
