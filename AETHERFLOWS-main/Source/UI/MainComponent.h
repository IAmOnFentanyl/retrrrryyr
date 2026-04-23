#pragma once
#include <JuceHeader.h>
#include "AetherLookAndFeel.h"
#include "TopBar.h"
#include "MixerPanel.h"
#include "TimelineComponent.h"
#include "PianoRollComponent.h"
#include "../Audio/AudioEngine.h"
#include <vector>
#include <memory>

class MainComponent : public juce::AudioAppComponent
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    aether::AetherLookAndFeel lookAndFeel;
    aether::TopBar topBar;
    aether::MixerPanel mixerPanel;
    aether::TimelineComponent timeline;
    aether::PianoRollComponent pianoRoll;
    aether::AudioEngine audioEngine;

    std::vector<std::unique_ptr<aether::Clip>> activeMidiClips;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
