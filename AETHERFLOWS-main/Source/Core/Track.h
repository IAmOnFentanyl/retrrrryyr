#pragma once
#include <memory>
#include <JuceHeader.h>
#include "../Audio/AetherProcessor.h"

namespace aether {

enum class TrackType { Audio, MIDI, Instrument, Bus, Aux };

class Track
{
public:
    Track(const juce::String& name, TrackType type);
    virtual ~Track();

    const juce::String& getName() const { return trackName; }
    TrackType getType() const { return trackType; }

    void setMuted(bool mute) { isMuted = mute; }
    bool getMuted() const { return isMuted; }

    void setSoloed(bool solo) { isSoloed = solo; }
    bool getSoloed() const { return isSoloed; }

    float getVolume() const { return volume; }
    void setVolume(float newVolume) { volume = newVolume; }

    // Each track has its own processor graph node in the main engine
    juce::AudioProcessorGraph::Node::Ptr node;

private:
    juce::String trackName;
    TrackType trackType;
    bool isMuted = false;
    bool isSoloed = false;
    float volume = 1.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Track)
};

} // namespace aether
