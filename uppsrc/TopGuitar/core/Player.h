// MIDI player interface (stub)
#pragma once

#include <Core/Core.h>

class IMidiPlayer {
public:
    virtual ~IMidiPlayer() {}
    virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;
    virtual bool IsRunning() const = 0;
    virtual void PlayTestTone() = 0; // placeholder
};

// Simple stub implementation
class MidiPlayerStub : public IMidiPlayer {
public:
    bool Initialize() override { running_ = true; return true; }
    void Shutdown() override { running_ = false; }
    bool IsRunning() const override { return running_; }
    void PlayTestTone() override { /* no-op */ }
private:
    bool running_{false};
};

