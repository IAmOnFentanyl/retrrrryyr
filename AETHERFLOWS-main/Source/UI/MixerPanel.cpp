#include "MixerPanel.h"

namespace aether {

MixerPanel::MixerPanel()
{
    // Add dummy faders for now
    for (int i = 0; i < 4; ++i)
    {
        auto fader = std::make_unique<juce::Slider>(juce::Slider::LinearVertical, juce::Slider::NoTextBox);
        addAndMakeVisible(*fader);
        faders.push_back(std::move(fader));
    }
}

void MixerPanel::paint(juce::Graphics& g)
{
    g.fillAll(AetherLookAndFeel::midnightNebula.brighter(0.02f));
}

void MixerPanel::resized()
{
    auto area = getLocalBounds().reduced(20);
    int faderWidth = 60;

    for (auto& fader : faders)
    {
        fader->setBounds(area.removeFromLeft(faderWidth).reduced(10));
        area.removeFromLeft(10);
    }
}

} // namespace aether
