#include "seawidget.h"
#include <QtGui>
#include <stdio.h>
#include <QTextStream>

QTextStream cout(stdout);

SeaWidget::SeaWidget(QWidget *parent) :
    QWidget(parent)
{
}

SeaWidget::SeaWidget(int shipSize, QWidget *parent) :
    mBoardSize(shipSize), QWidget(parent)
{
    bDrawShip = false;
    setAcceptDrops(true);
    setMinimumSize(mBoardSize, mBoardSize);
    setMaximumSize(mBoardSize, mBoardSize);

    // Try to implement battle grid
    int x0, y0, x1, y1;
    x0 = y0 = 0;
    x1 = y1 = 40;
    int step = 40;

    for (int i = 0; i <= 100; ++i)
    {
        QRect square(x0, y0, x1, y1);
        QPixmap pixmap(40, 40);
        pixmap.fill(Qt::GlobalColor(Qt::transparent));

        piecePixmaps.append(pixmap);
        pieceRects.append(square);

        if(i != 0 && i%10 == 0)
        {
            x0 = 0;
            x1 = 40;

            y0 += step;
            y1 += step;
        }
        else
        {
            x0 += step;
            x1 += step;
        }
    }
}

int SeaWidget::getShipSize() const
{
    return mBoardSize/10;
}

int SeaWidget::findPiece(const QRect &pieceRect) const
{
    for (int i = 0; i < pieceRects.size(); ++i) {
        QRect rect = pieceRects[i];
        if (pieceRect.top() == rect.top() && pieceRect.left() == rect.left()) {
            return i;
        }
    }
    return -1;
}

void SeaWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(event->rect(), Qt::white);

    highlightedRect = QRect(0, 0, mBoardSize, mBoardSize);

    if (highlightedRect.isValid()) {
        painter.setBrush(QColor("#ffcccc"));
        painter.setPen(Qt::SolidLine);
        painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
    }

    cout << "pieceRects:" << pieceRects.size() << endl;

    for (int i = 0; i < pieceRects.size(); ++i) {
        if(bDrawShip == false)
        {
            painter.drawRect(pieceRects[i]);
        }
        else
        {
            painter.drawRect(pieceRects[i]);    //  for black borders
            painter.drawPixmap(pieceRects[i], piecePixmaps[i]);
        }
    }
    painter.end();
}

void SeaWidget::clear()
{
    piecePixmaps.clear();
    pieceRects.clear();
    highlightedRect = QRect();
    update();
}

void SeaWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
        event->accept();
    else
        event->ignore();
}

void SeaWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    QRect updateRect = highlightedRect;
    highlightedRect = QRect();
    update(updateRect);
    event->accept();
}

const QRect SeaWidget::targetSquare(const QPoint &position) const
{
    return QRect(position.x()/getShipSize() * getShipSize(), position.y()/getShipSize() * getShipSize(), getShipSize(), getShipSize());
}

void SeaWidget::dropEvent(QDropEvent *event)
{
    cout << "DropEvent" << endl;
    if (event->mimeData()->hasFormat("image/x-puzzle-piece")) {
        bDrawShip = true;
        cout << "mimeData hasFormat image/x-puzzle-piece" << endl;

        QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QRect square = targetSquare(event->pos());
        QPixmap pixmap;
        QPoint location;
        dataStream >> pixmap >> location;
        cout << "Dropped cell is : " << findPiece(square) << endl;

        piecePixmaps.replace(findPiece(square),pixmap);
        pieceRects.replace(findPiece(square),square);

        highlightedRect = QRect();
        update(square);

        event->setDropAction(Qt::MoveAction);
        event->accept();

    } else {
        cout << "mimeData not an image/x-puzzle-piece" << endl;
        highlightedRect = QRect();
        event->ignore();
    }
}

bool SeaWidget::checkClash(int clickedCell) const
{
    QPixmap pixmap(40, 40);
    pixmap.fill(Qt::GlobalColor(Qt::transparent));
    if(piecePixmaps[clickedCell].toImage() != pixmap.toImage())
        return true;
    else
        return false;
}

void SeaWidget::mousePressEvent(QMouseEvent *event)
{
    // ERROR: 9 position, next 11. where is 10th ???
    QRect square = targetSquare(event->pos());
    int found = findPiece(square);
    cout << "Clicked to " << found << " position!" << endl;
    if(checkClash(found))
        cout << "BANG!" << endl;
    else
        cout << "MISS!" << endl;
}
