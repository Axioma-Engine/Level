#ifndef AXM_LEVEL_LOG_H
#define AXM_LEVEL_LOG_H
#pragma once

#include <stdarg.h>
#include <stdio.h>

#include <Axiom/Attributes.h>
#include <Axiom/Types.h>

namespace AXM {
    class Console {
      public:
        static constexpr const char* const RESET = "\033[0m";

        static constexpr const char* const BOLD      = "\033[1m";
        static constexpr const char* const DIM       = "\033[2m";
        static constexpr const char* const ITALIC    = "\033[3m";
        static constexpr const char* const UNDERLINE = "\033[4m";
        static constexpr const char* const BLINK     = "\033[5m";
        static constexpr const char* const REVERSE   = "\033[7m";
        static constexpr const char* const HIDDEN    = "\033[8m";
        static constexpr const char* const STRIKE    = "\033[9m";

        static constexpr const char* const BLACK   = "\033[30m";
        static constexpr const char* const RED     = "\033[31m";
        static constexpr const char* const GREEN   = "\033[32m";
        static constexpr const char* const YELLOW  = "\033[33m";
        static constexpr const char* const BLUE    = "\033[34m";
        static constexpr const char* const MAGENTA = "\033[35m";
        static constexpr const char* const CYAN    = "\033[36m";
        static constexpr const char* const WHITE   = "\033[37m";

        static constexpr const char* const BRIGHT_BLACK   = "\033[90m";
        static constexpr const char* const BRIGHT_RED     = "\033[91m";
        static constexpr const char* const BRIGHT_GREEN   = "\033[92m";
        static constexpr const char* const BRIGHT_YELLOW  = "\033[93m";
        static constexpr const char* const BRIGHT_BLUE    = "\033[94m";
        static constexpr const char* const BRIGHT_MAGENTA = "\033[95m";
        static constexpr const char* const BRIGHT_CYAN    = "\033[96m";
        static constexpr const char* const BRIGHT_WHITE   = "\033[97m";

        static constexpr const char* const BG_BLACK   = "\033[40m";
        static constexpr const char* const BG_RED     = "\033[41m";
        static constexpr const char* const BG_GREEN   = "\033[42m";
        static constexpr const char* const BG_YELLOW  = "\033[43m";
        static constexpr const char* const BG_BLUE    = "\033[44m";
        static constexpr const char* const BG_MAGENTA = "\033[45m";
        static constexpr const char* const BG_CYAN    = "\033[46m";
        static constexpr const char* const BG_WHITE   = "\033[47m";

        static constexpr const char* const BG_BRIGHT_BLACK   = "\033[100m";
        static constexpr const char* const BG_BRIGHT_RED     = "\033[101m";
        static constexpr const char* const BG_BRIGHT_GREEN   = "\033[102m";
        static constexpr const char* const BG_BRIGHT_YELLOW  = "\033[103m";
        static constexpr const char* const BG_BRIGHT_BLUE    = "\033[104m";
        static constexpr const char* const BG_BRIGHT_MAGENTA = "\033[105m";
        static constexpr const char* const BG_BRIGHT_CYAN    = "\033[106m";
        static constexpr const char* const BG_BRIGHT_WHITE   = "\033[107m";
    };

#ifdef AXM_LOG_DISABLE
    class Log {
      public:
        Log() {}
        Log(const char* prefix, const char* color) {}
        Log(const char* prefix, const char* color, FILE* buffer) {}

        axmFormatPrintf(2, 3) void logInfo(const char* format, ...) {}
        axmFormatPrintf(2, 3) void logWarning(const char* format, ...) {}
        axmFormatPrintf(2, 3) void logError(const char* format, ...) {}
    };
#else
    class Log {
      public:
        Log();
        Log(const char* prefix, const char* color);
        Log(const char* prefix, const char* color, FILE* buffer);

        axmFormatPrintf(2, 3) void logInfo(const char* format, ...);
        axmFormatPrintf(2, 3) void logWarning(const char* format, ...);
        axmFormatPrintf(2, 3) void logError(const char* format, ...);

      private:
        axmFormatPrintf(2, 0) void logImpl(const char* format, va_list args, bool formatting);

        const char* _prefix;
        const char* _color;
        FILE*       _buffer;
        bool        _formatting;
    };

#endif
}
#endif
