// Licensed under Creative Commons Zero v1.0 Universal

#pragma once

// clang-format off

#if defined(_WIN32) || defined(WIN32)

#include "WinLite/internal/preWinapi.h"

    // We enable STRICT mode to avoid some type conversions in the Win32 API
// https://learn.microsoft.com/en-us/windows/win32/winprog/enabling-strict
#ifndef STRICT
#define STRICT
#endif

#include "WinLite/internal/minWindows.h"
#include "WinLite/internal/postWinapi.h"

#endif // defined(_WIN32) || defined(WIN32)