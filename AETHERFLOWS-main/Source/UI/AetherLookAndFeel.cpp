#include "AetherLookAndFeel.h"

namespace aether {

const juce::Colour AetherLookAndFeel::midnightNebula = juce::Colour::fromString("FF0B0B0D");
const juce::Colour AetherLookAndFeel::electricAmethyst = juce::Colour::fromString("FF9D50BB");
const juce::Colour AetherLookAndFeel::cyanPlasma = juce::Colour::fromString("FF00F2FE");
const juce::Colour AetherLookAndFeel::magentaPulse = juce::Colour::fromString("FFFF00FF");

AetherLookAndFeel::AetherLookAndFeel()
{
    setColour(juce::ResizableWindow::backgroundColourId, midnightNebula);
    setColour(juce::Label::textColourId, juce::Colours::lightgrey);
    setColour(juce::TextButton::buttonColourId, midnightNebula.brighter(0.1f));
    setColour(juce::TextButton::textColourOffId, juce::Colours::lightgrey);
    setColour(juce::ScrollBar::thumbColourId, electricAmethyst.withAlpha(0.3f));
}

void AetherLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                                        float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                                        juce::Slider& slider)
{
    auto fill = cyanPlasma;
    auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat().reduced(10);
    auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = 3.0f;
    auto arcRadius = radius - lineW * 0.5f;

    juce::Path backgroundArc;
    backgroundArc.addCentredArc(bounds.getCentreX(), bounds.getCentreY(), arcRadius, arcRadius, 0.0f, rotaryStartAngle, rotaryEndAngle, true);
    g.setColour(midnightNebula.brighter(0.2f));
    g.strokePath(backgroundArc, juce::PathStrokeType(lineW));

    if (slider.isEnabled())
    {
        juce::Path valueArc;
        valueArc.addCentredArc(bounds.getCentreX(), bounds.getCentreY(), arcRadius, arcRadius, 0.0f, rotaryStartAngle, toAngle, true);

        // Neon Glow
        for (int i = 1; i <= 3; ++i)
        {
            g.setColour(fill.withAlpha(0.1f * (4 - i)));
            g.strokePath(valueArc, juce::PathStrokeType(lineW + (float)i * 2.0f));
        }

        g.setColour(fill);
        g.strokePath(valueArc, juce::PathStrokeType(lineW));
    }
}

void AetherLookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
                                        float sliderPos, float minSliderPos, float maxSliderPos,
                                        const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    auto trackWidth = 4.0f;
    auto isVertical = slider.isVertical();

    juce::Rectangle<float> track;
    if (isVertical)
        track = juce::Rectangle<float>((float)x + (float)width * 0.5f - trackWidth * 0.5f, (float)y, trackWidth, (float)height);
    else
        track = juce::Rectangle<float>((float)x, (float)y + (float)height * 0.5f - trackWidth * 0.5f, (float)width, trackWidth);

    g.setColour(midnightNebula.brighter(0.2f));
    g.fillRoundedRectangle(track, trackWidth * 0.5f);

    auto fill = electricAmethyst;
    juce::Rectangle<float> thumb;
    float thumbSize = 16.0f;

    if (isVertical)
        thumb = juce::Rectangle<float>((float)x + (float)width * 0.5f - thumbSize * 0.5f, sliderPos - thumbSize * 0.5f, thumbSize, thumbSize);
    else
        thumb = juce::Rectangle<float>(sliderPos - thumbSize * 0.5f, (float)y + (float)height * 0.5f - thumbSize * 0.5f, thumbSize, thumbSize);

    // Multilayered Glow
    for (int i = 1; i <= 3; ++i)
    {
        g.setColour(fill.withAlpha(0.15f * (4 - i)));
        g.fillEllipse(thumb.expanded((float)i * 2.0f));
    }

    g.setColour(fill);
    g.fillEllipse(thumb);
}

} // namespace aether
