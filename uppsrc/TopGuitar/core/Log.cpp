// Simple file logger

#include "Log.h"

using namespace Upp;

Logger& Logger::Get() {
    static Logger inst;
    return inst;
}

String Logger::Path() const {
    return ConfigFile("TopGuitar.log");
}

String Logger::Timestamp() const {
    Time t = GetSysTime();
    return Format("%04d-%02d-%02d %02d:%02d:%02d", t.year, t.month, t.day, t.hour, t.minute, t.second);
}

void Logger::Append(const String& line) {
    String p = Path();
    RealizePath(p);
    FileAppend fa(p);
    if(!fa) return;
    fa << Timestamp() << " | " << line << '\n';
}

String Logger::ReadAll() const {
    String p = Path();
    if(!FileExists(p)) return String();
    return LoadFile(p);
}

void Logger::Clear() {
    String p = Path();
    if(FileExists(p)) FileDelete(p);
}

