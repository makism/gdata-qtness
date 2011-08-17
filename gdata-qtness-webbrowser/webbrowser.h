#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QMainWindow>

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
    void setHtml(const QString &_html);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
