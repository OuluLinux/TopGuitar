// MainWindow — maps from TGWindow (Java) to U++ TopWindow
#pragma once

#include <CtrlLib/CtrlLib.h>
#include "views/DocumentView.h"
#include "views/LogWindow.h"
using namespace Upp;

class MainWindow : public Upp::TopWindow {
public:
    MainWindow();
    void SetStatus(const Upp::String& text);

    bool Key(dword key, int count) override;

private:
    void MainMenu(Upp::Bar& bar);
    void FileMenu(Upp::Bar& bar);
    void HelpMenu(Upp::Bar& bar);
    void ToolBarMain(Upp::ToolBar& bar);
    void OnOpen();
    void OnSaveAs();
    void OnNew();
    void OnNewFromTemplate(const Upp::String& name);
    void OnExit();
    void OnOpenRecent(const Upp::String& path);
    void OnClearRecent();
    void OpenPath(const Upp::String& path);
    void SaveAsPath(const Upp::String& path);
    void OnAbout();
    void OnViewLogs();
    void LoadGeometry();
    void SaveGeometry();
public:
    void RefreshViewFromDocument();
    void UpdateStatusToCurrentFile();
    void ShowTransient(const Upp::String& text, int ms = 2500);

private:
    Upp::MenuBar menubar_;
    Upp::StatusBar status_;
    Upp::ToolBar toolbar_;
    DocumentView docview_;
    Upp::Timer transient_timer_;
    Upp::One<LogWindow> logwin_;
};
