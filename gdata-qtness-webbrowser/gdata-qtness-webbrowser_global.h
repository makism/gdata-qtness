#ifndef GDATAQTNESSWWWBROWSER_GLOBAL_H
#define GDATAQTNESSWWWBROWSER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GDATAQTNESSGOAUTHWWWBROWSER_LIBRARY)
#  define GDATAQTNESSGOAUTHWWWBROWSERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define GDATAQTNESSGOAUTHWWWBROWSERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GDATAQTNESSWWWBROWSER_GLOBAL_H