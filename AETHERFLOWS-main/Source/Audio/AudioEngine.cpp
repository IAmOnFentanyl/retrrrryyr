#include "AudioEngine.h"

namespace aether {

AudioEngine::AudioEngine()
{
    formatManager.registerBasicFormats();
    transportSource.addChangeListener(this);
    transportSource.setSource(&mixerSource);
}

AudioEngine::~AudioEngine()
{
    transportSource.setSource(nullptr);
    transportSource.removeChangeListener(this);
}

void AudioEngine::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    currentSampleRate = sampleRate;
    synthProcessor.prepareToPlay(sampleRate, samplesPerBlockExpected);
    masterEQ.prepareToPlay(sampleRate, samplesPerBlockExpected);
    masterComp.prepareToPlay(sampleRate, samplesPerBlockExpected);
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void AudioEngine::releaseResources()
{
    synthProcessor.releaseResources();
    masterEQ.releaseResources();
    masterComp.releaseResources();
    mixerSource.releaseResources();
    transportSource.releaseResources();
}

void AudioEngine::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (transportSource.isPlaying())
    {
        transportSource.getNextAudioBlock(bufferToFill);
    }
    else
    {
        bufferToFill.clearActiveBufferRegion();
    }

    // Process MIDI
    juce::MidiBuffer blockMidi;
    {
        const juce::ScopedLock sl(midiLock);
        blockMidi.addEvents(liveMidi, 0, bufferToFill.numSamples, 0);
        liveMidi.clear();
    }

    if (transportSource.isPlaying())
    {
        double startTime = playHead / currentSampleRate;
        double endTime = (playHead + bufferToFill.numSamples) / currentSampleRate;

        for (auto* clip : midiClips)
        {
            auto& seq = clip->getMidiSequence();
            for (int i = 0; i < seq.getNumEvents(); ++i)
            {
                auto* event = seq.getEventPointer(i);
                auto ts = event->message.getTimeStamp();
                if (ts >= startTime && ts < endTime)
                {
                    int offset = (int)((ts - startTime) * currentSampleRate);
                    blockMidi.addEvent(event->message, juce::jlimit(0, bufferToFill.numSamples - 1, offset));
                }
            }
        }
        playHead += bufferToFill.numSamples;
    }

    // Synthesize MIDI into a temp buffer and mix in
    juce::AudioBuffer<float> synthBuffer(bufferToFill.buffer->getNumChannels(), bufferToFill.numSamples);
    synthBuffer.clear();
    synthProcessor.processBlock(synthBuffer, blockMidi);

    for (int ch = 0; ch < bufferToFill.buffer->getNumChannels(); ++ch)
        bufferToFill.buffer->addFrom(ch, bufferToFill.startSample, synthBuffer, ch, 0, bufferToFill.numSamples);

    // Master FX
    juce::MidiBuffer emptyMidi;
    masterEQ.processBlock(*bufferToFill.buffer, emptyMidi);
    masterComp.processBlock(*bufferToFill.buffer, emptyMidi);

    if (recorder.isRecording())
        recorder.processBlock(*bufferToFill.buffer);
}

void AudioEngine::play() { playHead = 0; transportSource.start(); }
void AudioEngine::stop() { transportSource.stop(); }

void AudioEngine::addClipSource(const juce::File& file)
{
    auto source = std::make_unique<AudioClipSource>(file, formatManager);
    mixerSource.addInputSource(source.get(), false);
    clipSources.push_back(std::move(source));
}

void AudioEngine::changeListenerCallback(juce::ChangeBroadcaster*) {}

} // namespace aether
