// Document manager (stub)
#pragma once

#include <Core/Core.h>

class DocumentManager {
public:
    static DocumentManager& Get();
    void OpenDefault();
    bool HasUnwanted() const { return unwanted_; }
private:
    DocumentManager() = default;
    bool unwanted_{true};
};

