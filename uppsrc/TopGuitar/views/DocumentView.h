// DocumentView — placeholder central view
#pragma once

#include <CtrlLib/CtrlLib.h>

class DocumentView : public Upp::Ctrl {
public:
    DocumentView();
    void SetPath(const Upp::String& path);
    void SetUntitled();

    void Paint(Upp::Draw& w) override;

private:
    Upp::String path_;
};

