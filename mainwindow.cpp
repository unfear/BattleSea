#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets>
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
    delete seaWidget;
    delete shipsList;
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
    connect(restartAction, SIGNAL(triggered()), this, SLOT(setupShips()));
}

void MainWindow::setupWidgets()
{
    QFrame *frame = new QFrame(this);
    QHBoxLayout *frameLayout = new QHBoxLayout(frame);

    seaWidget = new SeaWidget(400, this);
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
    }
}

void MainWindow::setupShips()
{
    for(int i = 0; i < shipsNumber; i++)
        shipsList->addShip(mShip1hImage, QPoint());
}
