// MainWindow implementation

#include "MainWindow.h"

using namespace Upp;

MainWindow::MainWindow() {
    Title("TopGuitar");
    Sizeable().Zoomable();
    MinSize(Size(600, 400));
}

