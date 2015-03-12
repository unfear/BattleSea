#ifndef SHIPSLIST_H
#define SHIPSLIST_H

#include <QListWidget>

class ShipsList  : public QListWidget
{
    Q_OBJECT

public:
    ShipsList(int shipSize, QWidget *parent = 0);
    void addShip(QPixmap pixmap, QPoint location);
    void dragMoveEvent(QDragMoveEvent *event);
    void startDrag(Qt::DropActions supportedActions);

private:
    int mShipSize;
    int mOneDeckShipsCount;
    int mTwoDeckShipsCount;
    int mThreeDeckShipsCount;
    int mFourDeckShipsCount;
};

#endif // SHIPSLIST_H
