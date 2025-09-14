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

void ConfigService::SetInt(const String& key, int value) {
    Set(key, AsString(value));
}

int ConfigService::GetInt(const String& key, int def) const {
    int i = kv_.Find(key);
    if (i < 0) return def;
    return Nvl(StrInt(kv_.Get(i)), def);
}

void ConfigService::Load() {
    kv_.Clear();
    String path = ConfigFile("TopGuitar.cfg");
    if(!FileExists(path)) return;
    FileIn in(path);
    if(!in) return;
    while(!in.IsEof()) {
        String line = TrimBoth(in.GetLine());
        if(line.IsEmpty() || line[0] == '#') continue;
        int p = line.Find('=');
        if(p <= 0) continue;
        String key = TrimBoth(line.Left(p));
        String val = TrimBoth(line.Mid(p+1));
        Set(key, val);
    }
}

void ConfigService::Save() const {
    String path = ConfigFile("TopGuitar.cfg");
    RealizePath(path);
    FileOut out(path);
    if(!out) return;
    for(int i = 0; i < kv_.GetCount(); ++i) {
        out << kv_.GetKey(i) << "=" << kv_.Get(i) << "\n";
    }
}
