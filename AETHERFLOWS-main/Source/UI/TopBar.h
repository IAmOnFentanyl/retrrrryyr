#pragma once
#include <JuceHeader.h>
#include "AetherLookAndFeel.h"
#include <functional>

namespace aether {

class TopBar : public juce::Component
{
public:
    TopBar();
    void paint(juce::Graphics& g) override;
    void resized() override;

    std::function<void()> onPlay;
    std::function<void()> onStop;
    std::function<void()> onRecord;
    std::function<void(bool)> onLoop;
    std::function<void(bool)> onMetronome;

private:
    juce::TextButton playButton { "PLAY" };
    juce::TextButton stopButton { "STOP" };
    juce::TextButton recordButton { "REC" };
    juce::ToggleButton loopButton { "LOOP" };
    juce::ToggleButton metronomeButton { "METRO" };
    juce::Label bpmLabel { "BPM", "120.0" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TopBar)
};

} // namespace aether
