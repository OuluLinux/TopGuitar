// MainWindow implementation

#include "MainWindow.h"
#include "core/Document.h"

using namespace Upp;

MainWindow::MainWindow() {
    Title("TopGuitar");
    Sizeable().Zoomable();
    MinSize(Size(600, 400));

    AddFrame(menubar_);
    menubar_.Set(THISBACK(MainMenu));

    AddFrame(status_);
    status_ = "Ready";
}

void MainWindow::MainMenu(Bar& bar) {
    bar.Sub("&File", THISBACK(FileMenu));
}

void MainWindow::FileMenu(Bar& bar) {
    bar.Add("&Open...\tCtrl+O", THISBACK(OnOpen));
    bar.Separator();
    bar.Add("E&xit", THISBACK(OnExit));
}

void MainWindow::OnOpen() {
    FileSel fs;
    fs.Type("Guitar Files", "*.gp;*.gpx;*.tg;*.tgf;*.ptb;*.tef;*.xml");
    if (fs.ExecuteOpen("Open File")) {
        String fn = ~fs;
        if (!fn.IsEmpty())
            DocumentManager::Get().OpenFile(fn);
        SetStatus(fn);
    }
}

void MainWindow::OnExit() {
    Close();
}

void MainWindow::SetStatus(const Upp::String& text) {
    status_ = text;
}

bool MainWindow::Key(dword key, int count) {
    if (key == K_CTRL_O) { OnOpen(); return true; }
    return TopWindow::Key(key, count);
}
