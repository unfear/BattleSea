#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "seawidget.h"
#include "shipslist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    void setupMenus();
    void setupWidgets();

    QPixmap ship4vImage;
    ShipsList *shipsList;
    SeaWidget *seaWidget;

public slots:
    void openImage(const QString &path = QString());
    void setupShips();
};

#endif // MAINWINDOW_H
