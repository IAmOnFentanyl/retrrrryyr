#pragma once
#include <JuceHeader.h>

namespace aether {

class AudioClipSource : public juce::AudioSource
{
public:
    AudioClipSource(const juce::File& file, juce::AudioFormatManager& formatManager);
    ~AudioClipSource() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

    void setNextReadPosition(juce::int64 newPosition);
    juce::int64 getNextReadPosition() const;
    juce::int64 getTotalLength() const;

private:
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioClipSource)
};

} // namespace aether
