#include "Music.h"

#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>

MusicPlayer::MusicPlayer():_music(), _filenames(), _volume(10.f) {
    _filenames[Music::MenuTheme] = "project/media/Chill.ogg";
    _filenames[Music::MissionTheme] = "project/media/Battle.ogg";
}

void MusicPlayer::play(Music::ID theme) {
  std::string filename = _filenames[theme];
  if (!_music.openFromFile(filename)) {
    throw std::runtime_error("Music " + filename + " could not be loaded.");
  }

  _music.setVolume(_volume);
  _music.setLoop(true);
  _music.play();
}

void MusicPlayer::stop() { _music.stop(); }

void MusicPlayer::setPaused(bool paused) {
  if (paused) {
    _music.pause();
  } else {
    _music.play();
  }
}

void MusicPlayer::setVolume(float volume) { _volume = volume; }