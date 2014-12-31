#ifndef SEAWIDGET_H
#define SEAWIDGET_H

#include <QList>
#include <QPoint>
#include <QPixmap>
#include <QWidget>

class SeaWidget : public QWidget
{
    Q_OBJECT
public:
    SeaWidget(QWidget *parent = 0);
    SeaWidget(int shipSize, QWidget *parent = 0);
    int getShipSize() const;
    void clear();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
//    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
//    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    const QRect targetSquare(const QPoint &position) const;

    int mShipSize;
    QList<QPixmap> piecePixmaps;
    QList<QRect> pieceRects;
    QList<QPoint> pieceLocations;
    QRect highlightedRect;
    bool bDrawShip;

signals:
    
public slots:
    
};

#endif // SEAWIDGET_H
