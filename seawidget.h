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
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
//    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    const QRect targetSquare(const QPoint &position) const;
    int findPiece(const QRect &pieceRect) const;
    bool checkClash(int clickedCell) const;

    int mBoardSize{0};
    QList<QPixmap> piecePixmaps;
    QList<QRect> pieceRects;
    QRect highlightedRect;
    QList<bool> mIsShipHere;

signals:
    
public slots:
    
};

#endif // SEAWIDGET_H
