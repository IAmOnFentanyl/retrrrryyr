#include <memory>
#include <vector>
#pragma once
#include <vector>
#include <memory>
#include <JuceHeader.h>
#include "AetherLookAndFeel.h"

namespace aether {

class MixerPanel : public juce::Component
{
public:
    MixerPanel();
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    std::vector<std::unique_ptr<juce::Slider>> faders;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MixerPanel)
};

} // namespace aether
