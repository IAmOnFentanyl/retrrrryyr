#pragma once
#include <JuceHeader.h>

namespace aether {

enum class ClipType { Audio, MIDI, Pattern };

class Clip
{
public:
    Clip(const juce::String& name, ClipType type, double startPos, double length);
    virtual ~Clip();

    const juce::String& getName() const { return clipName; }
    ClipType getType() const { return clipType; }

    double getStartPosition() const { return startPosition; }
    void setStartPosition(double pos) { startPosition = pos; }

    double getLength() const { return clipLength; }
    void setLength(double length) { clipLength = length; }

    juce::MidiMessageSequence& getMidiSequence() { return midiSequence; }

private:
    juce::String clipName;
    ClipType clipType;
    double startPosition;
    double clipLength;
    juce::MidiMessageSequence midiSequence;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Clip)
};

} // namespace aether
