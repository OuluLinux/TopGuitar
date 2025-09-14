TopGuitar — Agent Guide (U++/C++ Port)

Scope

- This file applies to the entire repository.
- We are forking TuxGuitar (Java) into C++ using the U++ framework.
- Keep original Java sources as reference. New implementation goes under `uppsrc/`.

High-Level Goals

- Prioritize the desktop main program behavior from `desktop/TuxGuitar`.
- Skip all plugins initially. Provide stubs for optional services (MIDI, UI extras, converters).
- Establish a clean, minimal, buildable U++ application skeleton before porting features.

Repository Layout (Target)

- `uppsrc/TopGuitar/` — primary U++ package
  - `Main.cpp` — `GUI_APP_MAIN`, single-instance guard, bootstrap
  - `TopGuitarApp.h/.cpp` — application singleton (maps from Java `TuxGuitar`)
  - `MainWindow.h/.cpp` — main window (maps from `TGWindow`)
  - `core/` — config, actions, document, player interfaces (stubs at first)
  - `TopGuitar.upp` — U++ package file
- Java reference modules remain in-place under `desktop/` and `common/`.

Coding Conventions (U++)

- Language: C++17 (or newer if available in U++ toolchain).
- Names
  - Classes/structs/functions: PascalCase (e.g., `TopGuitarApp`, `InitMainContext`).
  - Methods/data members: camelCase for locals/params; trailing underscore for private members (e.g., `context_`).
  - Constants/macros: ALL_CAPS with underscores.
- Framework: prefer U++ types and facilities
  - Strings/containers: `Upp::String`, `Upp::Vector`, `Upp::Array`, `Upp::One`, `Upp::Ptr`.
  - Concurrency: `Upp::Thread`, `Upp::Mutex`, `Upp::Gate`.
  - Events/callbacks: `Upp::Callback`, `Upp::Event`.
  - UI: `Upp::TopWindow`, `Upp::Ctrl`, `Upp::MenuBar`, etc.
- Error handling: avoid exceptions for control flow; prefer status returns and assertions (`ASSERT`).
- File organization: `.h` headers + `.cpp` sources; header guards or `#pragma once` (be consistent per package).
- Avoid heavy STL use unless required for 3rd-party interop; wrap if used.

Porting Strategy (Mapping from Java)

- `app.tuxguitar.app.TGMainSingleton` → `SingleInstance` (lock file + bring-to-front/IPC later)
- `app.tuxguitar.app.TuxGuitar` → `TopGuitarApp` (init context, UI, player, config)
- `app.tuxguitar.app.view.main.TGWindow` → `MainWindow` (`TopWindow`) 
- Action bus (`TGAction*`) → lightweight command/dispatcher using `Callback` and IDs/enums
- Config (`TGConfig*`) → simple config service (JSON or `.cfg`) in app data dir
- I18N (`messages.properties`) → U++ `.t` translation files (future task)
- Splash (`TGSplash`) → optional; defer
- MIDI/Player (`MidiPlayer`, `MidiSequencerProviderImpl`) → `IMidiPlayer` interface + stub impl

In/Out of Scope (Initial Pass)

- In: app bootstrap, single-instance, main window, config stub, action dispatcher stub, empty document flow.
- Out: all plugins (e.g., `TuxGuitar-*-ui`, `TuxGuitar-fluidsynth`, `TuxGuitar-synth-*`, `gervill`), conversion/exporters, advanced editors.

Licensing

- Preserve original copyright/license notices when porting code.
- The repository root contains LGPL-2.1; some modules may differ. Respect each module’s license terms when deriving code.
- Do not remove or alter license headers in referenced sources.

Process Guidelines

- Keep changes minimal and focused on the current task.
- Mirror Java structure only where it clarifies mapping; otherwise adopt idiomatic U++ design.
- Prefer small, verifiable steps (compiling skeleton → wire services → add features).
- Do not modify Java source in `desktop/` or `common/` except for documentation or reference markers.
- Document decisions and pending items in `CURRENT_TASK.md`.

Build & Tooling

- Use U++ TheIDE packages (`.upp`). CI/alt-build can be revisited later (e.g., CMake + U++).
- Target platforms: Windows, Linux, macOS. Use only cross-platform U++ APIs.

Quality Bar (for each step)

- Compiles in TheIDE and opens a main window.
- Single-instance guard works on Windows and Linux (macOS later). 
- No plugin dependencies introduced.

Future Integration (Notes)

- Sound: favor Fluidsynth (C API) integration for better output when audio is in scope; `gervill` is a Java reference.
- UI: consider feature parity incrementally (tablature, matrix/piano views) once skeleton is stable.

