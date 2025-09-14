// MainWindow implementation

#include "MainWindow.h"
#include "core/Document.h"
#include "core/Config.h"
#include "core/Recent.h"
#include "core/Log.h"
#include <climits>

using namespace Upp;

MainWindow::MainWindow() {
    Title("TopGuitar");
    Sizeable().Zoomable();
    MinSize(Size(600, 400));
    Icon(CtrlImg::new_doc());

    AddFrame(menubar_);
    menubar_.Set(THISBACK(MainMenu));

    AddFrame(toolbar_);
    toolbar_.Set(THISBACK(ToolBarMain));

    AddFrame(status_);
    status_ = "Ready";

    WhenClose = THISBACK(OnExit);
    LoadGeometry();

    Add(docview_.SizePos());
}

void MainWindow::MainMenu(Bar& bar) {
    bar.Sub("&File", THISBACK(FileMenu));
    bar.Sub("&Help", THISBACK(HelpMenu));
}

void MainWindow::FileMenu(Bar& bar) {
    bar.Add("&New\tCtrl+N", THISBACK(OnNew));
    bar.Sub("New From &Template", [=](Bar& b){
        b.Add("Standard 6-string", THISBACK1(OnNewFromTemplate, Upp::String("Standard 6-string")));
        b.Add("7-string guitar", THISBACK1(OnNewFromTemplate, Upp::String("7-string guitar")));
        b.Add("Bass 4-string", THISBACK1(OnNewFromTemplate, Upp::String("Bass 4-string")));
        b.Add("Ukulele", THISBACK1(OnNewFromTemplate, Upp::String("Ukulele")));
    });
    bar.Add("&Open...\tCtrl+O", THISBACK(OnOpen));
    bar.Add("S&ave As...\tCtrl+S", THISBACK(OnSaveAs));
    bar.Sub("&Recent Files", [=](Bar& b){
        Upp::Vector<Upp::String> recent = RecentFiles::Get();
        if(recent.IsEmpty()) {
            b.Add("(Empty)").Disable();
        } else {
            for(const Upp::String& p : recent) {
                b.Add(p, THISBACK1(OnOpenRecent, p));
            }
            b.Separator();
            b.Add("Clear Recent", THISBACK(OnClearRecent));
        }
    });
    bar.Separator();
    bar.Add("E&xit", THISBACK(OnExit));
}

void MainWindow::HelpMenu(Bar& bar) {
    bar.Add("&View Logs", THISBACK(OnViewLogs));
    bar.Add("&About TopGuitar", THISBACK(OnAbout));
}

void MainWindow::OnOpen() {
    FileSel fs;
    fs.Type("Guitar Files", "*.gp;*.gpx;*.tg;*.tgf;*.ptb;*.tef;*.xml");
    if (fs.ExecuteOpen("Open File")) {
        String fn = ~fs;
        OpenPath(fn);
    }
}

void MainWindow::OnExit() {
    SaveGeometry();
    ConfigService::Get().Save();
    Logger::Get().Append("Exit");
    Close();
}

void MainWindow::SetStatus(const Upp::String& text) {
    status_ = text;
}

bool MainWindow::Key(dword key, int count) {
    if (key == K_CTRL_O) { OnOpen(); return true; }
    if (key == K_CTRL_S) { OnSaveAs(); return true; }
    if (key == K_CTRL_N) { OnNew(); return true; }
    return TopWindow::Key(key, count);
}

void MainWindow::LoadGeometry() {
    ConfigService& cfg = ConfigService::Get();
    int x = cfg.GetInt("window.x", INT_MIN);
    int y = cfg.GetInt("window.y", INT_MIN);
    int w = cfg.GetInt("window.w", 800);
    int h = cfg.GetInt("window.h", 600);
    bool maxed = cfg.GetBool("window.max", false);
    if (x != INT_MIN && y != INT_MIN) {
        SetRect(x, y, w, h);
    } else {
        SetRect(0, 0, w, h);
        CenterScreen();
    }
    if (maxed)
        Maximize();
}

void MainWindow::SaveGeometry() {
    ConfigService& cfg = ConfigService::Get();
    cfg.SetBool("window.max", IsMaximized());
    if (!IsMaximized()) {
        Rect r = GetRect();
        cfg.SetInt("window.x", r.left);
        cfg.SetInt("window.y", r.top);
        cfg.SetInt("window.w", r.Width());
        cfg.SetInt("window.h", r.Height());
    }
}

void MainWindow::OnOpenRecent(const Upp::String& path) {
    OpenPath(path);
}

void MainWindow::OnClearRecent() {
    RecentFiles::Clear();
    ConfigService::Get().Save();
    ShowTransient("Recent list cleared");
    Logger::Get().Append("Recent list cleared");
}

void MainWindow::OpenPath(const Upp::String& path) {
    if(path.IsEmpty()) return;
    if(!FileExists(path)) {
        Exclamation(Format("File not found:\n%s", path));
        return;
    }
    DocumentManager::Get().OpenFile(path);
    SetStatus(path);
    docview_.SetPath(path);
    ConfigService::Get().Set("last_file", path);
    RecentFiles::Add(path);
    ConfigService::Get().Save();
    ShowTransient(Format("Opened: %s", path));
    Logger::Get().Append(Format("Opened: %s", path));
}

void MainWindow::OnAbout() {
    String msg;
    msg << "TopGuitar (U++ skeleton)\n\n"
        << "A C++/U++ fork-in-progress inspired by TuxGuitar.\n"
        << "This build is a prototype focusing on the main program.\n\n"
        << "Sources used as reference remain under desktop/ and common/.\n"
        << "See LICENSE for terms.";
    PromptOK(msg);
}

void MainWindow::RefreshViewFromDocument() {
    String path = DocumentManager::Get().CurrentPath();
    if(path.IsEmpty())
        docview_.SetUntitled();
    else
        docview_.SetPath(path);
}

void MainWindow::ToolBarMain(ToolBar& bar) {
    bar.Add("New", CtrlImg::new_doc(), THISBACK(OnNew));
    bar.Add("Open", CtrlImg::open(), THISBACK(OnOpen));
    bar.Separator();
    bar.Add("About", CtrlImg::help(), THISBACK(OnAbout));
}

void MainWindow::OnNew() {
    DocumentManager::Get().NewDocument();
    SetStatus("Untitled");
    docview_.SetUntitled();
    ShowTransient("New document created");
    Logger::Get().Append("New document");
}

void MainWindow::OnNewFromTemplate(const Upp::String& name) {
    DocumentManager::Get().NewDocument();
    docview_.SetUntitled();
    UpdateStatusToCurrentFile();
    ShowTransient(Format("New from template: %s", name));
    Logger::Get().Append(Format("New from template: %s", name));
}

void MainWindow::OnSaveAs() {
    FileSel fs;
    fs.Type("Guitar Files", "*.gp;*.gpx;*.tg;*.tgf;*.ptb;*.tef;*.xml");
    if (fs.ExecuteSaveAs("Save As")) {
        String fn = ~fs;
        SaveAsPath(fn);
    }
}

void MainWindow::SaveAsPath(const Upp::String& path) {
    if(path.IsEmpty()) return;
    DocumentManager::Get().SetCurrentPath(path);
    SetStatus(path);
    docview_.SetPath(path);
    ConfigService::Get().Set("last_file", path);
    RecentFiles::Add(path);
    ConfigService::Get().Save();
    ShowTransient(Format("Saved as: %s", path));
    Logger::Get().Append(Format("Saved as: %s", path));
}

void MainWindow::UpdateStatusToCurrentFile() {
    String path = DocumentManager::Get().CurrentPath();
    if(path.IsEmpty())
        SetStatus("Untitled");
    else
        SetStatus(path);
}

void MainWindow::ShowTransient(const Upp::String& text, int ms) {
    SetStatus(text);
    KillTimeCallback(1);
    SetTimeCallback(ms, THISBACK(UpdateStatusToCurrentFile), 1);
}

void MainWindow::OnViewLogs() {
    if(!logwin_)
        logwin_.Create();
    logwin_->LoadLog();
    logwin_->Open(this);
}
