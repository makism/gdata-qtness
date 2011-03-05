#include <QtCore/QCoreApplication>

#include "test_clientlogin.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	Test_ClientLogin test_cl;

    return a.exec();
}
