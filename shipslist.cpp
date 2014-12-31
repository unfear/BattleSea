#include "shipslist.h"

ShipsList::ShipsList(int shipSize, QWidget *parent) :
    mShipSize(shipSize), QListWidget(parent)
{
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(40, 160));
    setSpacing(10);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
}

void ShipsList::addShip(QPixmap pixmap, QPoint location)
{
    QListWidgetItem *shipItem = new QListWidgetItem(this);
    shipItem->setIcon(QIcon(pixmap));
    shipItem->setData(Qt::UserRole, QVariant(pixmap));
    shipItem->setData(Qt::UserRole+1, location);
    shipItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable
                        | Qt::ItemIsDragEnabled);
}
