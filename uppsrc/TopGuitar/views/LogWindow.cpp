// LogWindow implementation

#include "LogWindow.h"
#include "../core/Log.h"

using namespace Upp;

LogWindow::LogWindow() {
    Title("TopGuitar Logs");
    Sizeable().Zoomable();
    MinSize(Size(500, 300));

    AddFrame(bar_);
    bar_.Set(THISBACK(LogBar));

    edit_.SetReadOnly();
    edit_.SetFont(MonoFont());
    Add(edit_.SizePos());

    LoadLog();
}

void LogWindow::LoadLog() {
    edit_.SetData(Logger::Get().ReadAll());
    edit_.ScrollEnd();
}

void LogWindow::OnRefresh() {
    LoadLog();
}

void LogWindow::OnClear() {
    Logger::Get().Clear();
    LoadLog();
}

void LogWindow::LogBar(ToolBar& bar) {
    bar.Add("Refresh", CtrlImg::refresh(), THISBACK(OnRefresh));
    bar.Add("Clear", CtrlImg::remove(), THISBACK(OnClear));
    bar.Separator();
    bar.Add("Close", CtrlImg::close(), THISBACK(Close));
}

