// Recent files management

#include "Recent.h"
#include "Config.h"

using namespace Upp;

namespace RecentFiles {

static String KeyAt(int i) { return Format("recent%d", i); }

Vector<String> Get(int max_items) {
    Vector<String> out;
    ConfigService& cfg = ConfigService::Get();
    for(int i = 0; i < max_items; ++i) {
        String v = cfg.Get(KeyAt(i));
        if(v.IsEmpty())
            continue;
        out.Add(v);
    }
    return out;
}

void Add(const String& path, int max_items) {
    if(path.IsEmpty() || !FileExists(path))
        return;
    ConfigService& cfg = ConfigService::Get();
    Vector<String> v = Get(max_items);
    // Remove duplicates
    for(int i = 0; i < v.GetCount(); ++i) {
        if(v[i] == path) { v.Remove(i); break; }
    }
    v.Insert(0, path);
    while(v.GetCount() > max_items)
        v.Remove(v.GetCount() - 1);
    for(int i = 0; i < max_items; ++i) {
        cfg.Set(KeyAt(i), i < v.GetCount() ? v[i] : String());
    }
}

void Clear() {
    ConfigService& cfg = ConfigService::Get();
    for(int i = 0; i < 10; ++i)
        cfg.Set(KeyAt(i), String());
}

}

