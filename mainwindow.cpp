#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupMenus();
    setupWidgets();

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setWindowTitle(tr("SeaBattle"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *exitAction = fileMenu->addAction(tr("E&xit"));
    exitAction->setShortcuts(QKeySequence::Quit);

    QMenu *gameMenu = menuBar()->addMenu(tr("&Game"));

    QAction *restartAction = gameMenu->addAction(tr("&Restart"));

    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
//    connect(restartAction, SIGNAL(triggered()), this, SLOT(setupPuzzle()));
}

void MainWindow::setupWidgets()
{
    QFrame *frame = new QFrame;
    QHBoxLayout *frameLayout = new QHBoxLayout(frame);

    seaWidget = new SeaWidget(400);

    shipsList = new ShipsList(seaWidget->getShipSize(), this);


//    connect(seaWidget, SIGNAL(puzzleCompleted()),
//            this, SLOT(setCompleted()), Qt::QueuedConnection);

    frameLayout->addWidget(shipsList);
    frameLayout->addWidget(seaWidget);
    setCentralWidget(frame);
}

void MainWindow::openImage(const QString &path)
{
    QString fileName = path;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this,
            tr("Open Image"), "", "Image Files (*.png *.jpg *.bmp)");

    if (!fileName.isEmpty()) {
        QPixmap newImage;
        if (!newImage.load(fileName)) {
            QMessageBox::warning(this, tr("Open Image"),
                                  tr("The image file could not be loaded."),
                                  QMessageBox::Cancel);
            return;
        }
        mShip1hImage = newImage;
        setupShips();
    }
}

void MainWindow::setupShips()
{
//    int size = qMin(ship4vImage.width(), ship4vImage.height());
//    ship4vImage = ship4vImage.copy((ship4vImage.width() - size)/2,
//        (ship4vImage.height() - size)/2, size, size).scaled(seaWidget->width(),
//            seaWidget->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    shipsList->clear();
    int x = 0;
    int y = 0;
//    for (int y = 0; y < 5; ++y) {
//        for (int x = 0; x < 5; ++x) {
            int pieceSize = seaWidget->getShipSize();
            QPixmap pieceImage = mShip1hImage.copy(x * pieceSize, y * pieceSize, pieceSize, pieceSize);
            shipsList->addShip(pieceImage, QPoint(x, y));
//            shipsList->addShip(pieceImage, QPoint(x, y));
//        }
//    }

//    qsrand(QCursor::pos().x() ^ QCursor::pos().y());

//    for (int i = 0; i < shipsList->count(); ++i) {
//        if (int(2.0*qrand()/(RAND_MAX+1.0)) == 1) {
//            QListWidgetItem *item = shipsList->takeItem(i);
//            shipsList->insertItem(0, item);
//        }
//    }

//    seaWidget->clear();
}
