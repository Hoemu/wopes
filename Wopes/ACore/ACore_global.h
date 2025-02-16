#ifndef ACORE_GLOBAL_H
#define ACORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ACORE_LIBRARY)
#define ACORE_EXPORT Q_DECL_EXPORT
#else
#define ACORE_EXPORT
#endif

#define ACORE_IMPORT Q_DECL_IMPORT

#endif // ACORE_GLOBAL_H
