// Config service (stub)

#include "Config.h"

using namespace Upp;

ConfigService& ConfigService::Get() {
    static ConfigService inst;
    return inst;
}

void ConfigService::Set(const String& key, const String& value) {
    int i = kv_.Find(key);
    if (i >= 0) kv_.Set(i, value);
    else kv_.Add(key, value);
}

String ConfigService::Get(const String& key, const String& def) const {
    int i = kv_.Find(key);
    return (i >= 0 ? kv_.Get(i) : def);
}

void ConfigService::SetBool(const String& key, bool value) {
    Set(key, value ? "1" : "0");
}

bool ConfigService::GetBool(const String& key, bool def) const {
    int i = kv_.Find(key);
    if (i < 0) return def;
    const String& v = kv_.Get(i);
    return v == "1" || ToLower(v) == "true";
}

void ConfigService::Load() {
    // TODO: implement persistence (e.g., JSON or .cfg in appdata)
}

void ConfigService::Save() const {
    // TODO: implement persistence
}

