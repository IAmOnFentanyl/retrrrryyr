#include "TopBar.h"

namespace aether {

TopBar::TopBar()
{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(recordButton);
    addAndMakeVisible(loopButton);
    addAndMakeVisible(metronomeButton);
    addAndMakeVisible(bpmLabel);

    playButton.onClick = [this] { if (onPlay) onPlay(); };
    stopButton.onClick = [this] { if (onStop) onStop(); };
    recordButton.onClick = [this] { if (onRecord) onRecord(); };
    loopButton.onStateChange = [this] { if (onLoop) onLoop(loopButton.getToggleState()); };
    metronomeButton.onStateChange = [this] { if (onMetronome) onMetronome(metronomeButton.getToggleState()); };

    bpmLabel.setEditable(true);
    bpmLabel.setJustificationType(juce::Justification::centred);
}

void TopBar::paint(juce::Graphics& g)
{
    g.fillAll(AetherLookAndFeel::midnightNebula.brighter(0.05f));
    g.setColour(AetherLookAndFeel::cyanPlasma.withAlpha(0.3f));
    g.drawRect(getLocalBounds().removeFromBottom(1), 1);
}

void TopBar::resized()
{
    auto area = getLocalBounds().reduced(10);
    playButton.setBounds(area.removeFromLeft(60));
    area.removeFromLeft(8);
    stopButton.setBounds(area.removeFromLeft(60));
    area.removeFromLeft(8);
    recordButton.setBounds(area.removeFromLeft(60));
    area.removeFromLeft(20);
    loopButton.setBounds(area.removeFromLeft(80));
    area.removeFromLeft(8);
    metronomeButton.setBounds(area.removeFromLeft(100));

    bpmLabel.setBounds(area.removeFromRight(80));
}

} // namespace aether
