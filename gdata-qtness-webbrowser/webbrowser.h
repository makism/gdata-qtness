#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QMainWindow>
#include <QUrl>

#include "gdata-qtness-webbrowser_global.h"


namespace Ui {
    class MainWindow;
}

GDATAQTNESSGOAUTHWWWBROWSERSHARED_EXPORT class WebBrowser : public QMainWindow
{
    Q_OBJECT

public:
    explicit WebBrowser(QWidget *parent = 0);
    ~WebBrowser();

public slots:
    void showProgressBar();
    void hideProgressBar(bool val);
    void setUrl(const QString &_url);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
