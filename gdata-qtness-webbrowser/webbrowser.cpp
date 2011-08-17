#include "webbrowser.h"
#include "ui_mainwindow.h"

#include <QFile>


WebBrowser::WebBrowser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

WebBrowser::~WebBrowser()
{
    delete ui;
}

void WebBrowser::setHtml(const QString &_html)
{
    ui->webView->setHtml(_html);
    this->show();
}
