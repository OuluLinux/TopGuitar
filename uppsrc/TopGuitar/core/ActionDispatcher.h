// Action dispatcher (very light stub)
#pragma once

#include <Core/Core.h>

class ActionDispatcher {
public:
    using Handler = Upp::Callback1<const Upp::String&>; // action id

    static ActionDispatcher& Get();

    void Subscribe(const Upp::String& id, const Handler& cb);
    void Unsubscribe(const Upp::String& id, const Handler& cb);
    void Emit(const Upp::String& id);

private:
    ActionDispatcher() = default;
    Upp::Index<Upp::String> ids_;
    Upp::Vector<Upp::Vector<Handler>> cbs_;
};

