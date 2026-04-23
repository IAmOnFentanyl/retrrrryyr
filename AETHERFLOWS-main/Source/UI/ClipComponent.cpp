#include "ClipComponent.h"

namespace aether {

ClipComponent::ClipComponent(Clip& c) : clip(c)
{
}

void ClipComponent::paint(juce::Graphics& g)
{
    auto color = (clip.getType() == ClipType::MIDI) ? AetherLookAndFeel::cyanPlasma : AetherLookAndFeel::electricAmethyst;

    // Background with subtle radial gradient
    juce::ColourGradient grad(color.withAlpha(0.15f), getLocalBounds().getCentre().toFloat(),
                               color.withAlpha(0.05f), {}, true);
    g.setGradientFill(grad);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 4.0f);

    // Neon Main Border
    g.setColour(color);
    g.drawRoundedRectangle(getLocalBounds().toFloat(), 4.0f, 2.0f);

    // Outer Glow
    g.setColour(color.withAlpha(0.3f));
    g.drawRoundedRectangle(getLocalBounds().toFloat().expanded(1.0f), 4.0f, 1.0f);

    // Visual placeholder for content
    g.setColour(color.withAlpha(0.4f));
    if (clip.getType() == ClipType::MIDI)
    {
        for (int i = 0; i < 5; ++i)
             g.fillRect(10.0f + i * 20.0f, 15.0f + (i % 3) * 5.0f, 15.0f, 4.0f);
    }
    else
    {
        juce::Path wave;
        wave.startNewSubPath(5, getHeight() / 2);
        for (int x = 5; x < getWidth() - 5; x += 5)
             wave.lineTo(x, (getHeight() / 2) + std::sin(x * 0.1f) * 10.0f);
        g.strokePath(wave, juce::PathStrokeType(1.5f));
    }

    g.setFont(juce::Font(12.0f, juce::Font::bold));
    g.setColour(juce::Colours::white.withAlpha(0.9f));
    g.drawText(clip.getName(), getLocalBounds().reduced(8, 4), juce::Justification::topLeft);
}

} // namespace aether
