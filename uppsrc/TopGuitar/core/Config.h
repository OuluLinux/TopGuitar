// Config service (stub)
#pragma once

#include <Core/Core.h>

class ConfigService {
public:
    static ConfigService& Get();

    void Set(const Upp::String& key, const Upp::String& value);
    Upp::String Get(const Upp::String& key, const Upp::String& def = Upp::String()) const;

    void SetBool(const Upp::String& key, bool value);
    bool GetBool(const Upp::String& key, bool def = false) const;
    void SetInt(const Upp::String& key, int value);
    int GetInt(const Upp::String& key, int def = 0) const;

    void Load(); // TODO: persist
    void Save() const; // TODO: persist

private:
    ConfigService() = default;

    Upp::VectorMap<Upp::String, Upp::String> kv_;
};
