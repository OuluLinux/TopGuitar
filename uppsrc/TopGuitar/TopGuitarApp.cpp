#include "TopGuitar.h"

using namespace Upp;

TopGuitarApp& TopGuitarApp::Get() {
    static TopGuitarApp inst;
    return inst;
}

void TopGuitarApp::InitMainContext() {
    // Load configuration (stub)
    ConfigService::Get().Load();
    Logger::Get().Append("InitMainContext");
}

void TopGuitarApp::InitUIContext() {
    // TODO: set up UI-specific state if needed
}

void TopGuitarApp::StartUIContext(MainWindow& window, const Upp::String& open_path) {
    // Initialize player (stub)
    static MidiPlayerStub player;
    player.Initialize();

    // Restore UI/config (stub)
    // TODO: apply window geometry, show optional panels, etc.

    // Open file if provided, else last file, else default document
    if(!IsNull(open_path) && !open_path.IsEmpty()) {
        if(FileExists(open_path)) {
            DocumentManager::Get().OpenFile(open_path);
            RecentFiles::Add(open_path);
            Logger::Get().Append(Format("Startup open: %s", open_path));
        } else {
            Exclamation(Format("File not found:\n%s", open_path));
            Logger::Get().Append(Format("Startup missing: %s", open_path));
        }
    } else {
        Upp::String last = ConfigService::Get().Get("last_file");
        if(!IsNull(last) && !last.IsEmpty() && FileExists(last))
            DocumentManager::Get().OpenFile(last), RecentFiles::Add(last), Logger::Get().Append(Format("Startup reopen last: %s", last));
        else
            DocumentManager::Get().OpenDefault(), Logger::Get().Append("Startup default document");
    }

    // Update status bar
    const Upp::String& path = DocumentManager::Get().CurrentPath();
    if(path.IsEmpty())
        window.SetStatus("Untitled");
    else
        window.SetStatus(path);

    // Persist last file if newly opened
    if(!path.IsEmpty()) {
        ConfigService::Get().Set("last_file", path);
        ConfigService::Get().Save();
    }

    // Update central view content
    window.RefreshViewFromDocument();

    initialized_ = true;
}
