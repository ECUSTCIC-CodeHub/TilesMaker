#pragma once

#if defined BUILDING_DLL
#if defined _MSC_VER
    #define TILESMAKER_API __declspec(dllexport)
#elif defined __GNUC__
    #define TILESMAKER_API __attribute__((visibility("default")))
#elif defined __clang__
    #define TILESMAKER_API __attribute__((visibility("default")))
#endif
#endif

