// DocumentView implementation

#include "DocumentView.h"

using namespace Upp;

DocumentView::DocumentView() {
    NoWantFocus();
}

void DocumentView::SetPath(const String& path) {
    path_ = path;
    Refresh();
}

void DocumentView::SetUntitled() {
    path_.Clear();
    Refresh();
}

void DocumentView::Paint(Draw& w) {
    Size sz = GetSize();
    Color bg = SColorFace();
    w.DrawRect(sz, bg);

    String line1 = "Document View";
    String line2 = path_.IsEmpty() ? String("Untitled") : String("File: ") + path_;
    Font fnt = StdFont().Bold();

    Size l1 = GetTextSize(line1, fnt);
    Size l2 = GetTextSize(line2, StdFont());

    int y = sz.cy/2 - (l1.cy + l2.cy + 8)/2;
    int x1 = (sz.cx - l1.cx)/2;
    int x2 = (sz.cx - l2.cx)/2;

    w.DrawText(x1, y, line1, fnt, SColorText());
    w.DrawText(x2, y + l1.cy + 8, line2, StdFont(), SColorText());
}

