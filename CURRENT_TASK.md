TopGuitar — Current Task (Main Program Port)

Objective

- Start the C++ (U++) fork by porting the core desktop application (no plugins yet). Keep Java sources as reference. New code lives under `uppsrc/`.

Scope (This Iteration)

- Focus: `desktop/TuxGuitar` main program behavior, wire up a minimal UI in U++.
- Reference-only: `common/*`, `desktop/TuxGuitar-ui-*`, `desktop/gervill`, `desktop/TuxGuitar-fluidsynth`.
- Exclude: All plugin implementations for now (keep APIs abstracted/stubbed).

Key References (Java)

- Entry/launch: `desktop/TuxGuitar/src/app/tuxguitar/app/TGMainSingleton.java`
- Core app: `desktop/TuxGuitar/src/app/tuxguitar/app/TuxGuitar.java`
- UI toolkit API surface: `desktop/TuxGuitar-ui-toolkit/src/app/tuxguitar/ui/*`
- MIDI player surface: `common/TuxGuitar-midi`, `desktop/TuxGuitar-synth*`
- Sound engines: `desktop/gervill`, `desktop/TuxGuitar-fluidsynth`

Deliverables (U++)

- `uppsrc/TopGuitar/TopGuitar.upp` — U++ package definition
- `uppsrc/TopGuitar/Main.cpp` — `GUI_APP_MAIN`, single-instance + app bootstrap
- `uppsrc/TopGuitar/TopGuitarApp.h/.cpp` — app singleton (maps from Java `TuxGuitar`)
- `uppsrc/TopGuitar/MainWindow.h/.cpp` — minimal main window (maps from `TGWindow`)
- `uppsrc/TopGuitar/core/*` — placeholders for config, actions, document, player abstractions
- Build: runnable skeleton in TheIDE (Windows/Linux/macOS)

Design Notes (Mapping)

- Single-instance: emulate `TGMainSingleton` with a lock file + bringing existing instance to front (later: IPC). Temp folder name: `TopGuitar-<user>`.
- Startup order: splash (optional), create UI, init player (stub), restore config (stub), open default song (stub).
- UI: Use U++ `TopWindow` for main frame; no toolkit abstraction layer; direct U++ controls.
- Actions/events: replace Java action bus with U++ `Callback`/light dispatcher.
- MIDI/audio: define `IMidiPlayer` interface with a stub implementation. Fluidsynth integration later.
- I18N: plan to use U++ translation `.t` files; Java message bundles remain a reference.

Risks / Watchouts

- License alignment: root is LGPL-2.1; some modules may differ. Preserve original notices in derived code as required.
- Large surface area: keep scope tight; stub non-core.
- UI and threading semantics differ between SWT/JavaFX and U++; validate event/thread model early.

Checklist

- [x] Inventory core modules and entry points
- [x] Establish port focus and exclusions
- [x] Scaffold U++ package and minimal window
- [x] Implement single-instance lock (Windows/Linux/macOS) — lock file held open (bring-to-front pending)
- [x] Add `TopGuitarApp` bootstrap mirroring Java lifecycle
- [x] Add config stub and simple persistence
- [x] Add action dispatcher stub
- [x] Add player interface stub (no sound yet)
- [x] Open default empty document workflow
- [ ] Build and run in TheIDE

Added in this pass

- Menu: File (New/Open/Save/Exit), Help (About)
- Status bar with simple messages
- Command-line `--open <file>` and File/Open dialog

Next Up (Proposed)

- Implement Save (stub UI -> actual persistence when model lands)
- Add recent files list to File menu using config
- Remember/restoring window geometry in config
- Wire a simple central view area (placeholder widget for score)

Next Up (Proposed)

- Verify build in TheIDE and run the hello-window.
- Implement default empty document creation and UI plumbing.
- Add basic command-line `--open <file>` workflow to open path in UI.

