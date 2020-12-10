LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

TARGET = main.out

HDRS = \
       project/include

SRCS = \
       project/src/main.cpp \
       project/src/Engine.cpp \
       project/src/Ship.cpp \
       project/src/World.cpp \
       project/src/Player.cpp \
       project/src/Server.cpp \
       project/src/Network.cpp \
       project/src/Massive.cpp


.PHONY: all clean

all: $(SRCS)
	g++ -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS) $(LIBS)

clean:
	rm -rf $(TARGET)
