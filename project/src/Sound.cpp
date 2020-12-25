#include "Sound.h"

#include <SFML/Audio/Listener.hpp>

#include <cmath>

namespace {
    const float ListenerZ = 300.f;
    const float Attenuation = 8.f;
    const float MinDistance2D = 200.f;
    const float MinDistance3D = std::sqrt(MinDistance2D * MinDistance2D + ListenerZ * ListenerZ);
}

namespace sounds {
    SoundPlayer::SoundPlayer() : _sound_buffer(), _sounds() {
        sf::Listener::setDirection(0.f, 0.f, -1.f);
    }

    void SoundPlayer::play(Id effect) {  // играй
        play(effect, get_listener_position());
    }

    void SoundPlayer::play(Id effect, sf::Vector2f position) {  // играй но тут
        _sounds.push_back(sf::Sound());
        sf::Sound& sound = _sounds.back();

        switch (effect) {
            case sounds::Id::ENEMYFIRE:
                sound.setVolume(6.0f);
                break;
            case sounds::Id::PLAYERFIRE:
                sound.setVolume(20.f);
                break;
            case sounds::Id::REFRACTION:
                sound.setVolume(100.f);
                break;
            case sounds::Id::EXPOLOSION:
                sound.setVolume(15.f);
            default:
                break;
        }

        sound.setBuffer(*_sound_buffer.get(effect));  // очень не уверен в этой строке
        sound.setPosition(position.x, - position.y, 0.f);  // а зря, работает пиздато :)  <3
        sound.setAttenuation(Attenuation);
        sound.setMinDistance(MinDistance3D);

        if (effect == Id::EXPOLOSION) {
            sound.setVolume(5.f);
        }

        sound.play();
    }

    void SoundPlayer::remove_stopped_sounds() {  // почисти за собой
        _sounds.remove_if([] (const sf::Sound &s) {
            return s.getStatus() == sf::Sound::Stopped;
        });
    }

    void SoundPlayer::set_listener_position(sf::Vector2f position) {
        sf::Listener::setPosition(position.x, -position.y, ListenerZ);
    }

    sf::Vector2f SoundPlayer::get_listener_position() const {
        sf::Vector3f position = sf::Listener::getPosition();

        return sf::Vector2f(position.x, position.y);
    }
}
