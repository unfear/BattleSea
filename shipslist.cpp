#include <QtGui>

#include "shipslist.h"
#include <QTextStream>

QTextStream ccout(stdout);

ShipsList::ShipsList(int shipSize, QWidget *parent) :
    mShipSize(shipSize), QListWidget(parent)
{
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(40, 40));
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

void ShipsList::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece")) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else
        event->ignore();
}

void ShipsList::startDrag(Qt::DropActions /*supportedActions*/)
{
    ccout << "startDrag" << endl;
    QListWidgetItem *item = currentItem();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPixmap pixmap = qvariant_cast<QPixmap>(item->data(Qt::UserRole));
    QPoint location = item->data(Qt::UserRole+1).toPoint();

    dataStream << pixmap << location;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("image/x-puzzle-piece", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
    drag->setPixmap(pixmap);

    if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
        delete takeItem(row(item));
}
