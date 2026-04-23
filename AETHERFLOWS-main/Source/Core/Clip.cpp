#include "Clip.h"

namespace aether {

Clip::Clip(const juce::String& name, ClipType type, double startPos, double length)
    : clipName(name), clipType(type), startPosition(startPos), clipLength(length)
{
}

Clip::~Clip() {}

} // namespace aether
