// LogWindow — simple viewer for log file
#pragma once

#include <CtrlLib/CtrlLib.h>

class LogWindow : public Upp::TopWindow {
public:
    LogWindow();
    void LoadLog();

private:
    void OnRefresh();
    void OnClear();
    void LogBar(Upp::ToolBar& bar);

private:
    Upp::DocEdit edit_;
    Upp::ToolBar bar_;
};

