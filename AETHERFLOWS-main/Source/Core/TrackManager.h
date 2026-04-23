#pragma once
#include <vector>
#include <memory>
#include <JuceHeader.h>
#include "Track.h"
#include "../Audio/AudioEngine.h"

namespace aether {

class TrackManager
{
public:
    TrackManager(AudioEngine& engine);
    ~TrackManager();

    Track* addTrack(const juce::String& name, TrackType type);
    void removeTrack(Track* track);

    const std::vector<std::unique_ptr<Track>>& getTracks() const { return tracks; }

private:
    AudioEngine& audioEngine;
    std::vector<std::unique_ptr<Track>> tracks;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackManager)
};

} // namespace aether
