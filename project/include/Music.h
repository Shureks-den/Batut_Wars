#pragma once

#include <SFML/Audio.hpp>
#include <map>
#include <string>

namespace Music {
enum ID {
  MenuTheme,
  MissionTheme,
};
}

class MusicPlayer : private sf::NonCopyable {
 public:
  MusicPlayer();
  void play(Music::ID theme);
  void stop();
  void setPaused(bool paused);
  void setVolume(float volume);

 private:
  sf::Music _music;
  std::map<Music::ID, std::string> _filenames;
  float _volume;
};