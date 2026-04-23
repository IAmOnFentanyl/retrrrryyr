#include "TimelineComponent.h"

namespace aether {

TimelineComponent::TimelineComponent()
{
    demoClips.push_back(std::make_unique<Clip>("Neon Bass", ClipType::Audio, 0.0, 8.0));
    demoClips.push_back(std::make_unique<Clip>("Plasma Lead", ClipType::MIDI, 8.0, 8.0));
    demoClips.push_back(std::make_unique<Clip>("Aether Pad", ClipType::Audio, 4.0, 12.0));
    demoClips.push_back(std::make_unique<Clip>("Cosmic Perc", ClipType::MIDI, 16.0, 4.0));

    for (auto& clip : demoClips)
    {
        auto comp = std::make_unique<ClipComponent>(*clip);
        addAndMakeVisible(*comp);
        clipComponents.push_back(std::move(comp));
    }
}

void TimelineComponent::paint(juce::Graphics& g)
{
    g.fillAll(AetherLookAndFeel::midnightNebula);

    // Aesthetic Grid
    g.setColour(juce::Colours::white.withAlpha(0.03f));
    int pixelsPerBeat = 100;
    for (int x = 0; x < getWidth(); x += pixelsPerBeat)
    {
        g.drawVerticalLine(x, 0, (float)getHeight());
        if (x % (pixelsPerBeat * 4) == 0) // Bar lines
        {
             g.setColour(juce::Colours::white.withAlpha(0.08f));
             g.drawVerticalLine(x, 0, (float)getHeight());
             g.setColour(juce::Colours::white.withAlpha(0.03f));
        }
    }
}

void TimelineComponent::resized()
{
    int pixelsPerBeat = 100;
    int trackHeight = 60;

    for (int i = 0; i < clipComponents.size(); ++i)
    {
        auto& clip = demoClips[i];
        auto& comp = clipComponents[i];

        comp->setBounds((int)(clip->getStartPosition() * pixelsPerBeat),
                        i * trackHeight + 10,
                        (int)(clip->getLength() * pixelsPerBeat),
                        trackHeight - 15);
    }
}

} // namespace aether
