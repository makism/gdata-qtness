#include "test_clientlogin.h"

Test_ClientLogin::Test_ClientLogin(QObject *parent)
	: QObject (parent)
{
	cl = new ClientLogin("username", "password", dl);
	
	connect(cl, SIGNAL(authenticationSuccess()),
			this, SLOT(authSuccess()));
	connect(cl, SIGNAL(authenticationError(QString)),
			this, SLOT(authError(QString)));
	
	cl->authenticate();
}

Test_ClientLogin::~Test_ClientLogin(void)
{
	cl->deleteLater();
	cl = 0;
}

void Test_ClientLogin::authError(QString strError)
{
	qDebug() << strError;
}

void Test_ClientLogin::authSuccess(void)
{
	//qDebug() << cl->getAuthCookie();
	
	dl.setAuthToken(cl->getAuthCookie());
	dl.listDocuments();
}
