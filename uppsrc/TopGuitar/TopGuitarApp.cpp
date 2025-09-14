// TopGuitarApp — skeleton lifecycle implementation

#include "TopGuitarApp.h"
#include "MainWindow.h"
#include "core/Config.h"
#include "core/Document.h"
#include "core/Player.h"

using namespace Upp;

TopGuitarApp& TopGuitarApp::Get() {
    static TopGuitarApp inst;
    return inst;
}

void TopGuitarApp::InitMainContext() {
    // Load configuration (stub)
    ConfigService::Get().Load();
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

    // Open file if provided, else default document
    if(!IsNull(open_path) && !open_path.IsEmpty())
        DocumentManager::Get().OpenFile(open_path);
    else
        DocumentManager::Get().OpenDefault();

    // Update status bar
    const Upp::String& path = DocumentManager::Get().CurrentPath();
    if(path.IsEmpty())
        window.SetStatus("Untitled");
    else
        window.SetStatus(path);

    initialized_ = true;
}
