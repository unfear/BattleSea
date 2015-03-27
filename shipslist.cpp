#include <QtGui>

#include "shipslist.h"
#include "utility.h"

ShipsList::ShipsList(int shipSize, QWidget *parent) :
    mShipSize(shipSize), QListWidget(parent),
    mOneDeckShipsCount(4),
    mTwoDeckShipsCount(3),
    mThreeDeckShipsCount(2),
    mFourDeckShipsCount(1)
{
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
//    setLayoutMode(QListView::SinglePass);
    setIconSize(QSize(160, 40));
//    setSpacing(10);
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

    int curRow = row(shipItem);
    switch(curRow)
    {
        case 0:
            shipItem->setText(QString::number(mOneDeckShipsCount));
            break;
        case 1:
            shipItem->setText(QString::number(mTwoDeckShipsCount));
            break;
        case 2:
            shipItem->setText(QString::number(mThreeDeckShipsCount));
            break;
        case 3:
            shipItem->setText(QString::number(mFourDeckShipsCount));
            break;
    default:
        shipItem->setText(QString::number(curRow));
        break;
    }
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
    cout << "startDrag" << endl;
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
    {
        int curRow = row(item);
        switch(curRow)
        {
            case 0:
                if(--mOneDeckShipsCount == 0)
                    delete takeItem(row(item));
                else
                    selectedItems().takeFirst()->setText(QString::number(mOneDeckShipsCount));
                break;
            case 1:
                if(--mTwoDeckShipsCount == 0)
                    delete takeItem(row(item));
                else
                    selectedItems().takeFirst()->setText(QString::number(mTwoDeckShipsCount));
                break;
            case 2:
                if(--mThreeDeckShipsCount == 0)
                    delete takeItem(row(item));
                else
                    selectedItems().takeFirst()->setText(QString::number(mThreeDeckShipsCount));
                break;
            case 3:
                if(--mFourDeckShipsCount == 0)
                    delete takeItem(row(item));
                else
                    selectedItems().takeFirst()->setText(QString::number(mFourDeckShipsCount));
                break;
        }
//        if(--mOneDeckShipsCount == 0)
//            delete takeItem(row(item));
//        else
//            selectedItems().takeFirst()->setText(QString::number(mOneDeckShipsCount));
    }
}
