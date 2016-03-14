#ifdef EXPORTING_DLL
extern "C" __declspec(dllexport) void engineMain();
#else
extern "C" __declspec(dllimport) void engineMain();
#endif