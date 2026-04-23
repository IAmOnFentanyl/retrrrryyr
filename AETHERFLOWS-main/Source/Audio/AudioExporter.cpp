#include <memory>
#include "AudioExporter.h"

namespace aether {

bool AudioExporter::exportProject(const juce::File& file, AudioEngine& engine, double duration)
{
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

    auto wavFormat = formatManager.findFormatForFileExtension("wav");
    if (!wavFormat) return false;

    file.deleteFile();
    if (auto outStream = std::unique_ptr<juce::FileOutputStream>(file.createOutputStream()))
    {
        auto sampleRate = 44100.0;
        if (auto writer = std::unique_ptr<juce::AudioFormatWriter>(wavFormat->createWriterFor(outStream.get(), sampleRate, 2, 24, {}, 0)))
        {
            outStream.release();

            int samplesPerBlock = 512;
            juce::AudioBuffer<float> buffer(2, samplesPerBlock);

            engine.prepareToPlay(samplesPerBlock, sampleRate);
            engine.play();

            auto totalSamples = (juce::int64)(duration * sampleRate);
            juce::int64 samplesWritten = 0;

            while (samplesWritten < totalSamples)
            {
                auto samplesToProcess = (int)juce::jmin((juce::int64)samplesPerBlock, totalSamples - samplesWritten);

                juce::AudioSourceChannelInfo info(&buffer, 0, samplesToProcess);
                engine.getNextAudioBlock(info);

                writer->writeFromAudioSampleBuffer(buffer, 0, samplesToProcess);
                samplesWritten += samplesToProcess;
            }

            engine.stop();
            engine.releaseResources();
            return true;
        }
    }
    return false;
}

} // namespace aether
