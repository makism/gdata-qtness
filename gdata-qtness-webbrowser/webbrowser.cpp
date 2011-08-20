#include "webbrowser.h"
#include "ui_mainwindow.h"


WebBrowser::WebBrowser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QObject::connect(ui->webView, SIGNAL(loadProgress(int)),
                     ui->progressBar, SLOT(setValue(int)));

    QObject::connect(ui->webView, SIGNAL(loadStarted()),
                     this, SLOT(showProgressBar()));

    QObject::connect(ui->webView, SIGNAL(loadFinished(bool)),
                     this, SLOT(hideProgressBar(bool)));
}

WebBrowser::~WebBrowser()
{
    delete ui;
}

void WebBrowser::showProgressBar()
{
    ui->progressBar->setVisible(true);
}

void WebBrowser::hideProgressBar(bool val)
{
    Q_UNUSED(val);

    ui->progressBar->setVisible(false);
}

void WebBrowser::setUrl(const QString &_url)
{
    ui->webView->load(QUrl(_url));
    this->show();
}
