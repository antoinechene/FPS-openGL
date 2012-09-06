NAME	=	libnetworkhandler.a

SRC	=	Network.cpp\
		Parser.cpp\
		Client.cpp\
		DataNetwork.cpp\
		DataGame.cpp\
		DataPlayer.cpp\
		../Tools/Buffer.cpp

OBJ	=	$(SRC:.cpp=.o)
CXX	=	g++
CXXFLAGS+=	-Werror -Wall -W -D__SDL
LDFLAGS =

##########################################

$(NAME): $(OBJ)
	ar -r $(NAME) $(OBJ)
	ranlib $(NAME)

##########################################

telnet: CXXFLAGS += -D_TELNET
telnet: rebuild

telnet_server: CXXFLAGS += -D_TELNET -D_SERVER
telnet_server: debug

telnet_client: CXXFLAGS += -D_TELNET -D_CLIENT 
telnet_client: debug


server: CXXFLAGS += -D_SERVER 
server: debug

client: CXXFLAGS += -D_CLIENT 
client: debug

clean:
	rm -rf $(OBJ) $(TESTOBJ)

##########################################

distclean: clean
	rm -rf $(NAME) $(TESTNAME)

##########################################

rebuild: distclean $(NAME)

##########################################

debug: CXXFLAGS += -g3 -D__DEBUG
debug: rebuild

##########################################

only: clean
only: rebuild

##########################################

test:
	g++ -g3 Parser.cpp Network.cpp main_client.cpp -lpthread ../Common/libcommon.a -o client -D__DEBUG
	g++ -g3 Parser.cpp Network.cpp main_server.cpp -lpthread ../Common/libcommon.a -o server -D__DEBUG
