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
        mIsShipHere.append(false);

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
        painter.drawRect(pieceRects[i]);    //  for black borders
        painter.drawPixmap(pieceRects[i], piecePixmaps[i]);
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
        cout << "mimeData hasFormat image/x-puzzle-piece" << endl;

        QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QRect square = targetSquare(event->pos());
        QPixmap pixmap;
        QPoint location;
        dataStream >> pixmap >> location;
        int foundCell = findPiece(square);
        cout << "Dropped cell is : " << foundCell << endl;

        piecePixmaps.replace(foundCell,pixmap);
        pieceRects.replace(foundCell,square);
        mIsShipHere.replace(foundCell, true);

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
    {
        if(mIsShipHere[clickedCell] == true)
            return true;
    }

    return false;
}

void SeaWidget::mousePressEvent(QMouseEvent *event)
{
    // ERROR: 9 position, next 11. where is 10th ???
    QRect square = targetSquare(event->pos());
    int found = findPiece(square);
    cout << "Clicked to " << found << " position!" << endl;
    if(checkClash(found))
    {
        //TODO: add hit ships icon to piecePixmaps[found]
        cout << "BANG!" << endl;
        QPixmap hitCross(":/images/images/hitCross.png");
//        piecePixmaps.replace(found,hitCross);
//        pieceRects.replace(found,square);

        QPainter pixPaint(&piecePixmaps[found]);
        QBrush brush2( Qt::blue);
        pixPaint.setBrush(brush2);
        pixPaint.drawImage(QPoint(10,10),hitCross.toImage());
        pieceRects.replace(found,square);
    }
    else
    {
        //TODO: add miss point icon to piecePixmaps[found]
        cout << "MISS!" << endl;
        QPixmap missDot(":/images/images/missDot.png");
        piecePixmaps.replace(found,missDot);
        pieceRects.replace(found,square);
    }
    update(square);
}
