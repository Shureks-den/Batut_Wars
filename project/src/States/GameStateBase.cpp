#include "States/GameStateBase.h"

#include <memory>

#include "Ally.h"

GameStateBase::GameStateBase(StateStack& stack, Context context)
          : State(stack, context),
          _render(*context.window),
          _player(*context.player),
          _mission_status(*context.mission_status),
          _game_over(sf::Time::Zero),
          _frames(0) {
    _statistic_text.setFont(*context.fonts->get(fonts::Id::FPS));
    _statistic_text.setPosition(5.f, 5.f);
    _statistic_text.setCharacterSize(10);
}

void GameStateBase::draw() {
  _render.draw();

  sf::Vector2f fps = _render.get_view().getCenter();
  fps.x -= _render.get_view().getSize().x / 2 - 5;
  fps.y -= _render.get_view().getSize().y / 2 - 5;
  _statistic_text.setPosition(fps);
  getContext().window->draw(_statistic_text);
}

void GameStateBase::update_statistic(sf::Time time) {
  _update_time += time;
  _frames += 1;

  if (_update_time >= sf::seconds(1.0f)) {
    _statistic_text.setString(
        "FPS = " + std::to_string(_frames) + "\n" +
        "mSPU = " + std::to_string(_update_time.asMicroseconds() / _frames));

    _update_time -= sf::seconds(1.0f);
    _frames = 0;
  }
}
