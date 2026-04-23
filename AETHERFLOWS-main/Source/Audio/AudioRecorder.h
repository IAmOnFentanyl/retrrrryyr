#pragma once
#include <JuceHeader.h>

namespace aether {

class AudioRecorder
{
public:
    AudioRecorder();
    ~AudioRecorder();

    void startRecording(const juce::File& file);
    void stopRecording();
    bool isRecording() const { return activeWriter.load() != nullptr; }

    void processBlock(const juce::AudioBuffer<float>& buffer);

private:
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatWriter> writer;
    std::unique_ptr<juce::AudioFormatWriter::ThreadedWriter> threadedWriter;
    juce::TimeSliceThread backgroundThread { "Audio Recorder Thread" };

    std::atomic<juce::AudioFormatWriter::ThreadedWriter*> activeWriter { nullptr };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioRecorder)
};

} // namespace aether
