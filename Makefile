LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -pthread -lsfml-audio

TARGET = main.out

HDRS = \
       project/include \
       project/include/GUI \
       project/include/Network \
       project/include/States \
       project/include/Animation

SRCS = \
       project/src/main.cpp \
       project/src/Engine.cpp \
       project/src/Ship.cpp \
       project/src/Ally.cpp \
       project/src/Animation/Animation.cpp \
       project/src/World.cpp \
       project/src/Game.cpp \
       project/src/Render.cpp \
       project/src/Player.cpp \
       project/src/Animation/Layer.cpp \
       project/src/Holder.cpp \
       project/src/Utility.cpp \
       project/src/States/TitleState.cpp \
       project/src/States/StateStack.cpp \
       project/src/States/State.cpp \
       project/src/States/SettingState.cpp \
       project/src/States/PauseState.cpp \
       project/src/States/MenuState.cpp \
       project/src/States/WaitingState.cpp \
       project/src/States/ServerWaitingState.cpp \
       project/src/GUI/Label.cpp \
       project/src/States/GameState.cpp \
       project/src/Container.cpp \
       project/src/GUI/Component.cpp \
       project/src/GUI/Button.cpp \
       project/src/Network/Client.cpp \
       project/src/Network/Server.cpp \
       project/src/States/OnlineState.cpp \
       project/src/States/GameStateBase.cpp \
       project/src/Network/Network.cpp \
       project/src/Massive.cpp \
       project/src/IcePlanet.cpp \
       project/src/Animation/AnimationCreator.cpp \
       project/src/GUI/Textbox.cpp \
       project/src/States/OnlineMenuState.cpp \
       project/src/Bullet.cpp \
       project/src/Comet.cpp \
       project/src/Music.cpp \
       project/src/Animation/A-Ship.cpp \
       project/src/Animation/A-Space.cpp \
       project/src/Animation/A-Blackhole.cpp \
       project/src/Animation/A-Bullet.cpp \
       project/src/Animation/A-Portal.cpp \
       project/src/Animation/A-Comet.cpp \
       project/src/Animation/A-IcePlanet.cpp \
       project/src/Animation/A-Explosion.cpp \
       project/src/Animation/A-Maul.cpp \
       project/src/Enemy.cpp \
       project/src/Planet.cpp \
       project/src/States/GameOverState.cpp \
       project/src/Sound.cpp \
       project/src/Vietnam.cpp

.PHONY: all clean

all: $(SRCS)
	$(CXX) -std=c++17 -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS) $(LIBS)

clean:
	rm -rf $(TARGET)
