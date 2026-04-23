#pragma once
#include <JuceHeader.h>

namespace aether {

class AetherLookAndFeel : public juce::LookAndFeel_V4
{
public:
    AetherLookAndFeel();

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                          juce::Slider& slider) override;

    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPos, float minSliderPos, float maxSliderPos,
                          const juce::Slider::SliderStyle style, juce::Slider& slider) override;

    static const juce::Colour midnightNebula;
    static const juce::Colour electricAmethyst;
    static const juce::Colour cyanPlasma;
    static const juce::Colour magentaPulse;
};

} // namespace aether
