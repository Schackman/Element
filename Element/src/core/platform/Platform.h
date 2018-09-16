#pragma once

#ifdef _WIN32
	#define ELM_PLATFORM_WINDOWS 1
	#define ELM_API __declspec(dllexport)
#else
	#define ELM_API
#endif


