// Simple file logger
#pragma once

#include <Core/Core.h>

class Logger {
public:
    static Logger& Get();

    void Append(const Upp::String& line);
    Upp::String ReadAll() const;
    void Clear();
    Upp::String Path() const;

private:
    Logger() = default;
    Upp::String Timestamp() const;
};

