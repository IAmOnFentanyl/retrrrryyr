#include "PianoRollComponent.h"

namespace aether {

PianoRollComponent::PianoRollComponent() {}

void PianoRollComponent::paint(juce::Graphics& g)
{
    g.fillAll(AetherLookAndFeel::midnightNebula);

    float keyHeight = (float)getHeight() / 128.0f;
    for (int i = 0; i < 128; ++i)
    {
        bool isBlack = juce::MidiMessage::isMidiNoteBlack(i);
        g.setColour(isBlack ? juce::Colours::black.withAlpha(0.2f) : juce::Colours::white.withAlpha(0.05f));
        g.fillRect(0.0f, (float)getHeight() - (i + 1) * keyHeight, (float)getWidth(), keyHeight);

        if (i % 12 == 0) // Octave lines
        {
             g.setColour(juce::Colours::white.withAlpha(0.15f));
             g.drawHorizontalLine((int)(getHeight() - i * keyHeight), 0.0f, (float)getWidth());
        }
    }

    if (targetClip)
    {
        g.setColour(AetherLookAndFeel::cyanPlasma);
        float pixelsPerSecond = 100.0f;
        for (auto event : targetClip->getMidiSequence())
        {
            if (event->message.isNoteOn())
            {
                auto startTime = event->message.getTimeStamp();
                auto note = event->message.getMidiNoteNumber();
                auto endTime = targetClip->getMidiSequence().getEndTimeOfNote(event->message.getChannel(), note, event);

                juce::Rectangle<float> noteRect((float)startTime * pixelsPerSecond,
                                                (float)getHeight() - (note + 1) * keyHeight,
                                                (float)(endTime - startTime) * pixelsPerSecond,
                                                keyHeight);

                g.setColour(AetherLookAndFeel::cyanPlasma.withAlpha(0.8f));
                g.fillRoundedRectangle(noteRect, 2.0f);
                g.setColour(juce::Colours::white.withAlpha(0.4f));
                g.drawRoundedRectangle(noteRect, 2.0f, 1.0f);
            }
        }
    }
}

void PianoRollComponent::mouseDown(const juce::MouseEvent& e)
{
    int note = getMidiNoteFromY(e.position.y);
    lastNotePlayed = note;
    if (onNoteOn) onNoteOn(note, 0.8f);
}

void PianoRollComponent::mouseUp(const juce::MouseEvent& e)
{
    if (lastNotePlayed != -1)
    {
        if (onNoteOff) onNoteOff(lastNotePlayed);
        lastNotePlayed = -1;
    }
}

void PianoRollComponent::mouseDoubleClick(const juce::MouseEvent& e)
{
    if (targetClip)
    {
        int note = getMidiNoteFromY(e.position.y);
        double time = getTimeFromX(e.position.x);

        targetClip->getMidiSequence().addEvent(juce::MidiMessage::noteOn(1, note, 0.8f), time);
        targetClip->getMidiSequence().addEvent(juce::MidiMessage::noteOff(1, note), time + 0.5);
        targetClip->getMidiSequence().updateMatchedPairs();
        repaint();
    }
}

int PianoRollComponent::getMidiNoteFromY(float y)
{
    float keyHeight = (float)getHeight() / 128.0f;
    return juce::jlimit(0, 127, (int)((getHeight() - y) / keyHeight));
}

double PianoRollComponent::getTimeFromX(float x)
{
    return (double)x / 100.0;
}

} // namespace aether
