#pragma once

#define ELM_API

#ifdef _WIN32
	#define ELM_PLATFORM_WINDOWS 1
	#define ELM_API __declspec(dllexport)
#endif


