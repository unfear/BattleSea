#ifndef SEAWIDGET_H
#define SEAWIDGET_H

#include <QList>
#include <QPoint>
#include <QPixmap>
#include <QWidget>
#include "listener.h"

class SeaWidget : public QWidget
{
    Q_OBJECT
public:
    SeaWidget(QWidget *parent = 0);

    /// set role for the field. Because we have two the same fields.
    /// Left one is our's but the right one is enemy's field.
    enum BattleFieldRole {
        OWN = 0,
        ENEMY = 1
    };

    SeaWidget(int shipSize, BattleFieldRole role, QWidget *parent = 0);

    /// returns ship size
    int getShipSize() const;

    /// clear sea dashboard
    void clear();

    /// set listener to notify when data should be send.
    void setListener(Listener * listener);

    /// check whether enemy BANG or MISS by ship
    void enemyFireProcess(int cell);

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
    /// Add piece of ship to cell.
    void addShipsPiece(int cell, QRect square, QPixmap piece);
    /// Check whether we can add ship or not to cell
    bool isEnoughPlaceForShip(int deck, int cell) const;

    int mBoardSize{0};
    QList<QPixmap> piecePixmaps;
    QList<QRect> pieceRects;
    QRect highlightedRect;
    QList<bool> mIsShipHere;
    BattleFieldRole mBattlefieldRole;
    Listener * mListener;   // Shouldn't be deleted

signals:
    
public slots:
    
};

#endif // SEAWIDGET_H
