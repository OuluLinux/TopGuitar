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

void DocumentManager::OpenFile(const Upp::String& path) {
    current_path_ = path;
    unwanted_ = false;
    // TODO: parse supported formats and load content.
}

void DocumentManager::NewDocument() {
    current_path_.Clear();
    unwanted_ = false;
    // TODO: initialize a blank document/song structure
}

void DocumentManager::SetCurrentPath(const Upp::String& path) {
    current_path_ = path;
}
