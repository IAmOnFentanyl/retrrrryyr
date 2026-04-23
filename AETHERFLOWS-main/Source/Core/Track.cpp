#include "Track.h"

namespace aether {

Track::Track(const juce::String& name, TrackType type)
    : trackName(name), trackType(type)
{
}

Track::~Track() {}

} // namespace aether
