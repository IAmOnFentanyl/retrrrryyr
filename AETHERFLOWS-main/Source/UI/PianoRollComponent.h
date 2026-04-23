#pragma once
#include <JuceHeader.h>
#include "AetherLookAndFeel.h"
#include "../Core/Clip.h"

namespace aether {

class PianoRollComponent : public juce::Component
{
public:
    PianoRollComponent();
    void paint(juce::Graphics& g) override;
    void mouseDown(const juce::MouseEvent& e) override;
    void mouseUp(const juce::MouseEvent& e) override;
    void mouseDoubleClick(const juce::MouseEvent& e) override;

    void setTargetClip(Clip* clip) { targetClip = clip; repaint(); }

    std::function<void(int, float)> onNoteOn;
    std::function<void(int)> onNoteOff;

private:
    Clip* targetClip = nullptr;
    int lastNotePlayed = -1;
    int getMidiNoteFromY(float y);
    double getTimeFromX(float x);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PianoRollComponent)
};

} // namespace aether
