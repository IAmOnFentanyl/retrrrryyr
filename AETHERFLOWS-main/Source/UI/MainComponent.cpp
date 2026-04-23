#include "MainComponent.h"

MainComponent::MainComponent()
{
    setLookAndFeel(&lookAndFeel);

    addAndMakeVisible(topBar);
    addAndMakeVisible(timeline);
    addAndMakeVisible(mixerPanel);
    addAndMakeVisible(pianoRoll);

    auto dummyClip = std::make_unique<aether::Clip>("Synth Clip", aether::ClipType::MIDI, 0.0, 30.0);
    pianoRoll.setTargetClip(dummyClip.get());
    audioEngine.addMidiClip(dummyClip.get());
    activeMidiClips.push_back(std::move(dummyClip));

    topBar.onPlay = [this] { audioEngine.play(); };
    topBar.onStop = [this] {
        audioEngine.stop();
        if (audioEngine.isRecording())
            audioEngine.stopRecording();
    };

    topBar.onRecord = [this] {
        if (!audioEngine.isRecording())
        {
            auto file = juce::File::getSpecialLocation(juce::File::userDocumentsDirectory)
                            .getChildFile("Aetherflow_Recording.wav");
            audioEngine.startRecording(file);
            audioEngine.play();
        }
        else
            audioEngine.stopRecording();
    };

    pianoRoll.onNoteOn = [this](int note, float vel) {
        audioEngine.addMidiEvent(juce::MidiMessage::noteOn(1, note, vel));
    };

    pianoRoll.onNoteOff = [this](int note) {
        audioEngine.addMidiEvent(juce::MidiMessage::noteOff(1, note));
    };

    setAudioChannels(2, 2);
    setSize(1200, 800);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
    setLookAndFeel(nullptr);
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    audioEngine.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    audioEngine.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    audioEngine.releaseResources();
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(aether::AetherLookAndFeel::midnightNebula);
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    topBar.setBounds(area.removeFromTop(60));
    mixerPanel.setBounds(area.removeFromBottom(200));
    pianoRoll.setBounds(area.removeFromRight(300));
    timeline.setBounds(area);
}
