#pragma once

#if defined(__APPLE__) || defined(__MACH__)
	#include "pch_m.h"
#elif defined(__linux__) || defined(__linux) || defined(linux)
	#include "pch_l.h"
#else
	#error "What the OS?"
#endif
