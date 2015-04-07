#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets>
#include <stdlib.h>

MainWindow::MainWindow(APP_ROLE role, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mShipsNumber(4),
    mRole(role)
{
    ui->setupUi(this);
    setupMenus();
    setupWidgets();
    setupReadyButton();
    setupRoleLabel();

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setWindowTitle(tr("SeaBattle"));
}

MainWindow::~MainWindow()
{
    delete shipsList;
    delete seaWidgetEnemy;
    delete seaWidget;
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

    seaWidget = new SeaWidget(400, SeaWidget::BattleFieldRole::OWN, this);
    seaWidgetEnemy = new SeaWidget(400, SeaWidget::BattleFieldRole::ENEMY, this);
    shipsList = new ShipsList(seaWidget->getShipSize(), this);
    shipsList->setMinimumWidth(seaWidget->getShipSize()*4); // 10 is a list gap


//    connect(seaWidget, SIGNAL(puzzleCompleted()),
//            this, SLOT(setCompleted()), Qt::QueuedConnection);

    frameLayout->addWidget(shipsList);
    frameLayout->addWidget(seaWidget);
    frameLayout->addWidget(seaWidgetEnemy);
    setCentralWidget(frame);
}

void MainWindow::setupReadyButton()
{
    QIcon icon(":/images/images/notready.png");
    mReadyBtn = new QPushButton(icon, "Ready?", this);
    mReadyBtn->setGeometry(QRect(QPoint(ui->menuBar->sizeHint().rwidth(), 0), QSize(60, 20)));
    // Connect button signal to appropriate slot
    connect(mReadyBtn, SIGNAL(released()),this, SLOT(handleButton()));

}

void MainWindow::handleButton()
{
    QIcon icon(":/images/images/ready.png");
    mReadyBtn->setIcon(icon);
    // emit signal
    emit readyToPlay();
}

void MainWindow::setupRoleLabel()
{
    if(mRole == UNKNOWN)
        mRoleLabel = new QLabel("You are Unknown", this);
    else if(mRole == CLIENT)
        mRoleLabel = new QLabel("You are Client", this);
    else if(mRole == SERVER)
        mRoleLabel = new QLabel("You are Server", this);

    QPoint startPoint(ui->menuBar->sizeHint().rwidth()+mReadyBtn->size().rwidth()+10, 0);
    mRoleLabel->setGeometry(QRect(startPoint, QSize(100, 20)));
}

QPixmap MainWindow::openImage(const QString &path)
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
            return QPixmap();
        }
        return newImage;
    }

    return QPixmap();
}

void MainWindow::setupShips()
{
    QList<QString> images{":/images/images/ship1h.png", ":/images/images/ship2h.png",
                          ":/images/images/ship3h.png", ":/images/images/ship4h.png"};
    for(auto &x : images)
        shipsList->addShip(openImage(x), QPoint());

//    mOneDeckShipImage = openImage(":/images/images/ship1h.png");
//    mTwoDwckShipImage = openImage(":/images/images/ship1h.png");;
//    mThreeDeckShipImage = openImage(":/images/images/ship1h.png");;
//    mFourDeckShipImage = openImage(":/images/images/ship1h.png");;

//    for(int i = 0; i < mShipsNumber; i++)
//        shipsList->addShip(mOneDeckShipImage, QPoint());
}

void MainWindow::setListener(Listener * listener)
{
    seaWidgetEnemy->setListener(listener);
}

void MainWindow::catchFireAndCheck(FireEvent eventData)
{
    seaWidget->enemyFireProcess(eventData.x);
}
