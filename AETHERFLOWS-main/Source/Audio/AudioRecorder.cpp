#include "AudioRecorder.h"

namespace aether {

AudioRecorder::AudioRecorder()
{
    formatManager.registerBasicFormats();
    backgroundThread.startThread();
}

AudioRecorder::~AudioRecorder()
{
    stopRecording();
    backgroundThread.stopThread(1000);
}

void AudioRecorder::startRecording(const juce::File& file)
{
    stopRecording();

    if (auto wavFormat = formatManager.findFormatForFileExtension("wav"))
    {
        file.deleteFile();
        if (auto outStream = std::unique_ptr<juce::FileOutputStream>(file.createOutputStream()))
        {
            writer.reset(wavFormat->createWriterFor(outStream.get(), 44100.0, 2, 24, {}, 0));
            if (writer != nullptr)
            {
                outStream.release(); // Writer now owns the stream
                threadedWriter.reset(new juce::AudioFormatWriter::ThreadedWriter(writer.get(), backgroundThread, 32768));
                activeWriter.store(threadedWriter.get());
            }
        }
    }
}

void AudioRecorder::stopRecording()
{
    activeWriter.store(nullptr);
    threadedWriter.reset();
    writer.reset();
}

void AudioRecorder::processBlock(const juce::AudioBuffer<float>& buffer)
{
    if (auto* tw = activeWriter.load())
    {
        tw->write(buffer.getArrayOfReadPointers(), buffer.getNumSamples());
    }
}

} // namespace aether
