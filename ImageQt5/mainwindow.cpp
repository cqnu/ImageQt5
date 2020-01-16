#include "mainwindow.h"

#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>

#include "Document.h"
#include "View.h"
#include "GlobalFunc.h"
#include "Widget/WidgetManager.h"
#include "Widget/CommonWidget.h"
#include "Widget/CurvesWidget.h"
#include "Widget/LevelsWidget.h"
#include "Dialog/RawParameter.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.centralWidget->setStyleSheet("background-color:gray");

	createImageWidget();

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
	WidgetManager::getInstance()->cleanUp();
}

void MainWindow::createImageWidget()
{
	CommonWidget* common = new CommonWidget();
	createDockWidget(common);

	CurvesWidget* curves = new CurvesWidget();
	createDockWidget(curves);

	LevelsWidget* levels = new LevelsWidget();
	createDockWidget(levels);
}

void MainWindow::createDockWidget(BaseWidget* widget)
{
	QDockWidget* dockWidget = new QDockWidget(this);
	dockWidget->setWindowTitle(widget->getName());
	dockWidget->setWidget(widget);
	addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, dockWidget);

	WidgetManager::getInstance()->addWidget(widget);
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
	pixelCordLabel->setText(nullptr);
	pixelInfoLabel->setText(nullptr);
}

void MainWindow::on_actionOpenImage_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"),
		"/", QStringLiteral("Image file (*.dr *.jpg *.png *.bmp *.tif *.gif)"));
	if (!fileName.isEmpty())
	{
		pDoc->openFile(fileName);
		if (getGlobalImage())
		{
			WidgetManager::getInstance()->init();
		}
	}
}

void MainWindow::on_actionOpenRaw_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Raw"),
		"/", QStringLiteral("Raw file (*.raw)"));
	if (!fileName.isEmpty())
	{
		RawParameter raw(this, fileName);
		int res = raw.exec();
		if (res == QDialog::Accepted)
		{
			std::shared_ptr<BaseImage> image = raw.getImage();
			pDoc->copyImage(image);
			WidgetManager::getInstance()->init();
		}
	}
}

void MainWindow::on_actionSaveAs_triggered()
{
	if (pDoc->getImage() == nullptr)
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

	WidgetManager::getInstance()->reset();
}

void MainWindow::on_actionQuit_triggered()
{
	close();
}

void MainWindow::on_actionAbout_triggered()
{

}

void MainWindow::resizeEvent(QResizeEvent*)
{
	pView->resize(ui.centralWidget->size());
}
