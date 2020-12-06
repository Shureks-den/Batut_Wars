LIBS = -lsfml-graphics -lsfml-window -lsfml-system

TARGET = main.out

HDRS = \
       project/include

SRCS = \
       project/src/main.cpp \
       project/src/engine.cpp \
       project/src/ship.cpp \
       project/src/animation.cpp \
       project/src/world.cpp \
       project/src/game.cpp \
       project/src/render.cpp \
       project/src/player.cpp \
       project/src/layer.cpp \
       project/src/holder.cpp \
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
       project/src/Button.cpp


.PHONY: all clean

all: $(SRCS)
	g++ -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS) $(LIBS)

clean:
	rm -rf $(TARGET)
