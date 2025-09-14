// MainWindow — maps from TGWindow (Java) to U++ TopWindow
#pragma once

#include <CtrlLib/CtrlLib.h>

class MainWindow : public Upp::TopWindow {
public:
    MainWindow();
    void SetStatus(const Upp::String& text);

    bool Key(dword key, int count) override;

private:
    void MainMenu(Upp::Bar& bar);
    void FileMenu(Upp::Bar& bar);
    void OnOpen();
    void OnExit();

private:
    Upp::MenuBar menubar_;
    Upp::StatusBar status_;
};
