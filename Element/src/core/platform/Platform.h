#pragma once
#ifdef ELM_EXPORT
#undef ELM_EXPORT
#endif
#if defined _WIN32 || _WIN64
	#define ELM_PLATFORM_WINDOWS
	#define ELM_EXPORT __declspec(dllexport)
	#include <windows.h>
#else
	#define ELM_EXPORT
#endif


