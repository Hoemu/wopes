#ifndef ACORE_GLOBAL_H
#define ACORE_GLOBAL_H

#define A_DECL_EXPORT __declspec(dllexport)
#define A_DECL_IMPORT __declspec(dllimport)

#if defined(ACORE_LIBRARY)
#define ACORE_EXPORT A_DECL_EXPORT
#else
#define ACORE_EXPORT
#endif

#define ACORE_IMPORT A_DECL_IMPORT

#endif // ACORE_GLOBAL_H
