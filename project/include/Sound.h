#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include "Holder.h"

#include <list>

namespace sounds {

class SoundPlayer : private sf::NonCopyable {
 public:
    SoundPlayer();
    void play(Id effect);
    void play(Id effect, sf::Vector2f position);
    
    void remove_stopped_sounds();
    void set_listener_position(sf::Vector2f position);
    sf::Vector2f get_listener_position() const;

 private:
 sounds::Holder _sound_buffer;
 std::list<sf::Sound> _sounds;
};

}  // namespace sounds