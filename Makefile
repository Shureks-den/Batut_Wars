LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -pthread -lsfml-audio

TARGET = main.out

HDRS = \
       project/include \
       project/include/GUI \
       project/include/Network \
       project/include/GUI

SRCS = \
       project/src/main.cpp \
       project/src/Engine.cpp \
       project/src/Ship.cpp \
       project/src/Animation.cpp \
       project/src/World.cpp \
       project/src/Game.cpp \
       project/src/Render.cpp \
       project/src/Player.cpp \
       project/src/Layer.cpp \
       project/src/Holder.cpp \
       project/src/Utility.cpp \
       project/src/States/TitleState.cpp \
       project/src/States/StateStack.cpp \
       project/src/States/State.cpp \
       project/src/States/SettingState.cpp \
       project/src/States/PauseState.cpp \
       project/src/States/MenuState.cpp \
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
       project/src/AnimationCreator.cpp \
       project/src/GUI/Textbox.cpp \
       project/src/States/OnlineMenuState.cpp \
       project/src/Bullet.cpp \
       project/src/Music.cpp

.PHONY: all clean

all: $(SRCS)
	g++ -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS) $(LIBS)

clean:
	rm -rf $(TARGET)
