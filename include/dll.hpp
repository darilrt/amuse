#pragma once

#if defined(_MSC_VER)
#ifdef AMUSE_BUILD
#define AMUSE_API __declspec(dllexport)
#else
#define AMUSE_API __declspec(dllimport)
#endif // AMUSE_BUILD
#elif defined(__GNUC__)
//  GCC
#ifdef AMUSE_BUILD
#define AMUSE_API __attribute__((visibility("default")))
#else
#define AMUSE_API
#endif // AMUSE_BUILD
#else
#define AMUSE_API
#define AMUSE_API
#endif
