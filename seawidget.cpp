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
    mShipSize(shipSize), QWidget(parent)
{
    bDrawShip = false;
    setAcceptDrops(true);
    setMinimumSize(mShipSize, mShipSize);
    setMaximumSize(mShipSize, mShipSize);

    // Try to implement battle grid
    int x0, y0, x1, y1;
    x0 = y0 = 0;
    x1 = y1 = 40;
    int step = 40;

    Qt::GlobalColor color = Qt::green;
    for (int i = 0; i <= 100; ++i)
    {
        QRect square(x0, y0, x1, y1);
        QPixmap pixmap(40, 40);
        pixmap.fill(color);

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
        switch(color)
        {
            case Qt::green:
                color = Qt::red;
                break;
            case Qt::red:
                color = Qt::blue;
                break;
            case Qt::blue:
                color = Qt::green;
                break;
        }
    }
}

int SeaWidget::getShipSize() const
{
    return mShipSize;
}

void SeaWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(event->rect(), Qt::white);

    highlightedRect = QRect(0, 0, mShipSize, mShipSize);

    if (highlightedRect.isValid()) {
        painter.setBrush(QColor("#ffcccc"));
        painter.setPen(Qt::SolidLine);
        painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
    }

    cout << pieceRects.size() << endl;

    for (int i = 0; i < pieceRects.size(); ++i) {
        if(bDrawShip == false)
            painter.drawRect(pieceRects[i]);
        else
        {
            cout << "pieceRects index: " << i << endl;
            painter.setBrush(QColor("#ffcccc"));
            painter.setPen(Qt::SolidLine);
            painter.drawPixmap(pieceRects[i], piecePixmaps[i]);
        }
    }
    painter.end();
}

void SeaWidget::clear()
{
    pieceLocations.clear();
    piecePixmaps.clear();
    pieceRects.clear();
    highlightedRect = QRect();
//    inPlace = 0;
    update();
}

void SeaWidget::dragEnterEvent(QDragEnterEvent *event)
{
//    if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
        event->accept();
//    else
//        event->ignore();
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
        QRect square = targetSquare(event->pos());
        bDrawShip = true;

        QPixmap pixmap(40, 40);
        pixmap.load(":/images/images/ship4v_1.png");
        piecePixmaps.replace(0, pixmap);

        QPixmap pixmap2(40, 40);
        pixmap2.load(":/images/images/ship4v_2.png");
        piecePixmaps.replace(11, pixmap2);

        QPixmap pixmap3(40, 40);
        pixmap3.load(":/images/images/ship4v_3.png");
        piecePixmaps.replace(21, pixmap3);

        QPixmap pixmap4(40, 40);
        pixmap4.load(":/images/images/ship4v_4.png");
        piecePixmaps.replace(31, pixmap4);

        highlightedRect = QRect();
        update(QRect(0, 0, 40, 40));
        update(QRect(0, 40, 40, 80));
        update(QRect(0, 80, 40, 120));
        update(QRect(0, 120, 40, 160));

        event->setDropAction(Qt::MoveAction);
        event->accept();
}
