LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

TARGET = main.out

HDRS = \
       project/include

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
       project/src/TitleState.cpp \
       project/src/StateStack.cpp \
       project/src/State.cpp \
       project/src/SettingState.cpp \
       project/src/PauseState.cpp \
       project/src/MenuState.cpp \
       project/src/Label.cpp \
       project/src/GameState.cpp \
       project/src/Container.cpp \
       project/src/Component.cpp \
       project/src/Button.cpp \
       project/src/Server.cpp \
       project/src/Client.cpp \
       project/src/GameStateBase.cpp \
       project/src/OnlineState.cpp \
       project/src/Network.cpp


.PHONY: all clean

all: $(SRCS)
	g++ -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS) $(LIBS)

clean:
	rm -rf $(TARGET)
