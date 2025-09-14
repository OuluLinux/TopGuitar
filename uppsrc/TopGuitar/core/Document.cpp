// Document manager (stub)

#include "Document.h"

using namespace Upp;

DocumentManager& DocumentManager::Get() {
    static DocumentManager inst;
    return inst;
}

void DocumentManager::OpenDefault() {
    // No-op for now; would create a default empty song/document.
    unwanted_ = false;
}

