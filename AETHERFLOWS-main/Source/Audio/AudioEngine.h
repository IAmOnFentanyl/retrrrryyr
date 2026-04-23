#pragma once
#include <JuceHeader.h>
#include "AudioRecorder.h"
#include "AudioClipSource.h"
#include "AetherEffects.h"
#include "AetherSynth.h"
#include "../Core/Clip.h"
#include <vector>
#include <memory>

namespace aether {

class AudioEngine : public juce::AudioSource, public juce::ChangeListener
{
public:
    AudioEngine();
    ~AudioEngine() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

    void play();
    void stop();
    bool isPlaying() const { return transportSource.isPlaying(); }

    void startRecording(const juce::File& file) { recorder.startRecording(file); }
    void stopRecording() { recorder.stopRecording(); }
    bool isRecording() const { return recorder.isRecording(); }

    void addClipSource(const juce::File& file);
    void addMidiClip(Clip* clip) { midiClips.push_back(clip); }

    void addMidiEvent(const juce::MidiMessage& msg) {
        const juce::ScopedLock sl(midiLock);
        liveMidi.addEvent(msg, 0);
    }

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

private:
    juce::AudioTransportSource transportSource;
    juce::AudioFormatManager formatManager;
    AudioRecorder recorder;

    juce::MixerAudioSource mixerSource;
    std::vector<std::unique_ptr<AudioClipSource>> clipSources;
    std::vector<Clip*> midiClips;

    AetherSynthProcessor synthProcessor;
    juce::MidiBuffer liveMidi;
    juce::CriticalSection midiLock;

    AetherEQ masterEQ;
    AetherCompressor masterComp;

    double currentSampleRate = 44100.0;
    juce::int64 playHead = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioEngine)
};

} // namespace aether
