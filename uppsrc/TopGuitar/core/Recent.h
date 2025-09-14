// Recent files management
#pragma once

#include <Core/Core.h>

namespace RecentFiles {

Upp::Vector<Upp::String> Get(int max_items = 5);
void Add(const Upp::String& path, int max_items = 5);
void Clear();

}

