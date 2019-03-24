#include "mainwindow.h"

#include <QFileDialog>
#include <QPushButton>
#include "document.h"
#include "view.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.centralWidget->setStyleSheet("background-color:gray");

	createDockWidget();

	createStatusBar();

	pDoc = new Document(this);
	pView = new View(ui.centralWidget);
	pView->resize(ui.centralWidget->size());
	pView->show();
}

MainWindow::~MainWindow()
{
	if (pDoc)
	{
		delete pDoc;
	}
	if (pView)
	{
		delete pView;
	}
}

void MainWindow::createStatusBar()
{
	pixelCordLabel = new QLabel(this);
	pixelCordLabel->setAlignment(Qt::AlignRight);

	pixelInfoLabel = new QLabel(this);
	pixelInfoLabel->setAlignment(Qt::AlignRight);

	statusBar()->addPermanentWidget(pixelCordLabel, 1);
	statusBar()->addPermanentWidget(pixelInfoLabel, 1);
}

void MainWindow::showPixelValue(QPoint pos, QRgb rgb)
{
	QString str = QString(tr("x=%1, y=%2")).arg(pos.x()).arg(pos.y());
	pixelCordLabel->setText(str);

	str = QString(tr("Red%3, Green%4, Blue%5")).arg(qRed(rgb)).arg(qGreen(rgb)).arg(qBlue(rgb));
	pixelInfoLabel->setText(str);
}

void MainWindow::clearPixelValue()
{
	pixelCordLabel->setText(NULL);
	pixelInfoLabel->setText(NULL);
}

void MainWindow::on_actionOpen_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, QStringLiteral("Open Image"),
		"/", QStringLiteral("Image file (*.dr *.jpg *.png *.bmp *.tif *.gif)"));
	if (!fileName.isEmpty())
	{
		pDoc->openFile(fileName);
	}
}

void MainWindow::on_actionSaveAs_triggered()
{
	if (pDoc->getImage() == NULL)
		return;

	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image As"),
		"/", tr("JPG image (*.jpg);;PNG image (*.png);;BMP image (*.bmp);;TIFF image (*.tif)"));
	if (!fileName.isEmpty())
	{
		pDoc->saveAs(fileName);
	}
}

void MainWindow::on_actionClose_triggered()
{
	pDoc->closeFile();
}

void MainWindow::on_actionQuit_triggered()
{
	close();
}

void MainWindow::resizeEvent(QResizeEvent*)
{
	pView->resize(ui.centralWidget->size());
}
