#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <Axiom/Attributes.h>
#include <Axiom/Log.h>
#include <Axiom/System.h>

#ifndef AXM_LOG_DISABLE

#    if defined(AXM_OS_WINDOWS)
#        include <io.h>
#        include <windows.h>
#    else
#        include <unistd.h>
#    endif

inline bool isTerminal(FILE* buffer) noexcept {
    if (buffer == nullptr) return false;

#    if defined(AXM_OS_WINDOWS)
    int fd = _fileno(buffer);
    if (fd < 0) return false;
    return _isatty(fd) != 0;
#    else
    int fd = fileno(buffer);
    if (fd < 0) return false;
    return isatty(fd) != 0;
#    endif
}
bool shouldUseColor(FILE* buffer) {
    if (const char* no_color = getenv("NO_COLOR"))
        if (no_color[0] != '\0') return false;

    if (!isTerminal(buffer)) return false;

#    if defined(AXM_OS_WINDOWS)
    int fd = _fileno(buffer);
    if (fd < 0) return false;

    HANDLE h = (HANDLE)_get_osfhandle(fd);
    if (h == INVALID_HANDLE_VALUE) return false;

    DWORD mode = 0;
    if (GetConsoleMode(h, &mode) != 0) {
        if ((mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) == 0)
            SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        return true;
    }
    return false;
#    else
    return true;
#    endif
}

void printPrefix(const char* prefix, const char* color, FILE* buffer, bool formatting) {
    if (prefix != nullptr) {
        if (color != nullptr && formatting) fputs(color, buffer);
        fputs("[", buffer);
        fputs(prefix, buffer);
        fputs("] ", buffer);
        if (formatting) fputs(AXM::Console::RESET, buffer);
    }
}


namespace AXM {
    Log::Log() :
        _prefix(nullptr),
        _color(nullptr),
        _buffer(stdout),
        _formatting(shouldUseColor(stdout)) {}
    Log::Log(const char* prefix, const char* color) :
        _prefix(prefix),
        _color(color),
        _buffer(stdout),
        _formatting(shouldUseColor(stdout)) {}
    Log::Log(const char* prefix, const char* color, FILE* buffer) :
        _prefix(prefix),
        _color(color),
        _buffer(buffer ? buffer : stdout),
        _formatting(shouldUseColor(buffer ? buffer : stdout)) {}

    void Log::logImpl(const char* format, va_list args, bool formatting) {
        vfprintf(_buffer, format, args);
        if (formatting) fputs(Console::RESET, _buffer);
        fputc('\n', _buffer);
        fflush(_buffer);
    }

    void Log::logInfo(const char* format, ...) {
        printPrefix(_prefix, _color, _buffer, _formatting);
        va_list args;
        va_start(args, format);
        logImpl(format, args, _formatting);
        va_end(args);
    }

    void Log::logWarning(const char* format, ...) {
        printPrefix(_prefix, _color, _buffer, _formatting);
        if (_formatting) fputs(Console::YELLOW, _buffer);
        fputs("WARNING ", _buffer);

        va_list args;
        va_start(args, format);
        logImpl(format, args, _formatting);
        va_end(args);
    }

    void Log::logError(const char* format, ...) {
        printPrefix(_prefix, _color, _buffer, _formatting);
        if (_formatting) fputs(Console::RED, _buffer);
        fputs("ERROR ", _buffer);

        va_list args;
        va_start(args, format);
        logImpl(format, args, _formatting);
        va_end(args);
    }

}

#endif
