#include "mainwindow.h"
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QTextStream>
#include <qapplication.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , textEdit(new QTextEdit(this))
{
    setCentralWidget(textEdit);
    resize(800, 600);
    setupMenu();
}

MainWindow::~MainWindow() {}

void MainWindow::setupMenu()
{
    QMenu *fileMenu = menuBar()->addMenu("File");

    QAction *open = new QAction("Open", this);
    connect(open, &QAction::triggered, this, &MainWindow::openFile);
    fileMenu->addAction(open);

    QAction *save = new QAction("Save", this);
    connect(save, &QAction::triggered, this, &MainWindow::saveFile);
    fileMenu->addAction(save);

    QAction *exit = new QAction("Exit", this);
    connect(exit, &QAction::triggered, this, &MainWindow::exitApp);
    fileMenu->addAction(exit);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {
            textEdit->setPlainText(QTextStream(&file).readAll());
        }
    }
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream(&file) << textEdit->toPlainText();
        }
    }
}

void MainWindow::exitApp()
{
    QApplication::quit();
}
