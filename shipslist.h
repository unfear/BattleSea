#ifndef SHIPSLIST_H
#define SHIPSLIST_H

#include <QListWidget>

class ShipsList  : public QListWidget
{
    Q_OBJECT

public:
    ShipsList(int shipSize, QWidget *parent = 0);
    void addShip(QPixmap pixmap, QPoint location);

private:
    int mShipSize;
};

#endif // SHIPSLIST_H
