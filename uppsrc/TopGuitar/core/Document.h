// Document manager (stub)
#pragma once

#include <Core/Core.h>

class DocumentManager {
public:
    static DocumentManager& Get();
    void OpenDefault();
    void OpenFile(const Upp::String& path);
    bool HasUnwanted() const { return unwanted_; }
    const Upp::String& CurrentPath() const { return current_path_; }
private:
    DocumentManager() = default;
    bool unwanted_{true};
    Upp::String current_path_;
};
