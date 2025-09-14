// TopGuitarApp — maps from Java TuxGuitar core to U++
#pragma once

#include <CtrlLib/CtrlLib.h>

class MainWindow;

class TopGuitarApp {
public:
    static TopGuitarApp& Get();

    void InitMainContext();
    void InitUIContext();
    void StartUIContext(MainWindow& window, const Upp::String& open_path = Upp::String());

    bool IsInitialized() const { return initialized_; }

private:
    TopGuitarApp() = default;

private:
    bool initialized_{false};
};
