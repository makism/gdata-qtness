#include <QtCore/QCoreApplication>

#include "fetchoauthrequesttoken.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FetchOAuthRequestToken f;

    return a.exec();
}
