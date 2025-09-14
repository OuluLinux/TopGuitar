// Action dispatcher (very light stub)

#include "ActionDispatcher.h"

using namespace Upp;

ActionDispatcher& ActionDispatcher::Get() {
    static ActionDispatcher inst;
    return inst;
}

void ActionDispatcher::Subscribe(const String& id, const Handler& cb) {
    int i = ids_.Find(id);
    if (i < 0) {
        i = ids_.Add(id);
        cbs_.Add();
    }
    cbs_[i].Add(cb);
}

void ActionDispatcher::Unsubscribe(const String& id, const Handler& cb) {
    int i = ids_.Find(id);
    if (i < 0) return;
    auto& v = cbs_[i];
    for (int k = 0; k < v.GetCount(); ++k) {
        if (v[k] == cb) { v.Remove(k); break; }
    }
}

void ActionDispatcher::Emit(const String& id) {
    int i = ids_.Find(id);
    if (i < 0) return;
    const auto& v = cbs_[i];
    for (const auto& h : v) h(id);
}

