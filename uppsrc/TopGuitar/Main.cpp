// TopGuitar — U++ skeleton main

#include <CtrlLib/CtrlLib.h>
#include "TopGuitarApp.h"
#include "MainWindow.h"

using namespace Upp;

namespace {

#ifdef PLATFORM_WIN32
#include <windows.h>
class SingleInstanceGuard {
public:
    SingleInstanceGuard() : h_(NULL) {}
    ~SingleInstanceGuard() { if (h_) CloseHandle(h_); }
    bool Acquire(const WString& name) {
        h_ = CreateMutexW(NULL, FALSE, name.ToWString());
        if (!h_)
            return true; // fail open
        if (GetLastError() == ERROR_ALREADY_EXISTS)
            return false;
        return true;
    }
private:
    HANDLE h_;
};
#else
#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>
class SingleInstanceGuard {
public:
    SingleInstanceGuard() : fd_(-1) {}
    ~SingleInstanceGuard() {
        if (fd_ >= 0) {
            flock(fd_, LOCK_UN);
            close(fd_);
        }
    }
    bool Acquire(const String& lockfile) {
        fd_ = open(lockfile.Begin(), O_RDWR | O_CREAT, 0666);
        if (fd_ < 0)
            return true; // fail open
        if (flock(fd_, LOCK_EX | LOCK_NB) != 0)
            return false;
        return true;
    }
private:
    int fd_;
};
#endif

}

GUI_APP_MAIN
{
    // Single instance guard
#ifdef PLATFORM_WIN32
    SingleInstanceGuard app_lock;
    if (!app_lock.Acquire(L"Global\\TopGuitar_SingleInstance")) {
        PromptOK("TopGuitar is already running.");
        return;
    }
#else
    SingleInstanceGuard app_lock;
    String lockfile = "/tmp/topguitar.lock";
    if (!app_lock.Acquire(lockfile)) {
        PromptOK("TopGuitar is already running.");
        return;
    }
#endif

    // Bootstrap lifecycle
    Upp::String open_path;
    const Upp::Vector<Upp::String>& args = CommandLine();
    for (int i = 0; i < args.GetCount(); ++i) {
        const Upp::String& a = args[i];
        if (a == "--open" && i + 1 < args.GetCount()) {
            open_path = args[++i];
        } else if (!a.IsEmpty() && a[0] != '-') {
            if (open_path.IsEmpty()) open_path = a;
        }
    }
    TopGuitarApp& app = TopGuitarApp::Get();
    app.InitMainContext();
    app.InitUIContext();

    MainWindow win;
    app.StartUIContext(win, open_path);
    win.Run();
}
