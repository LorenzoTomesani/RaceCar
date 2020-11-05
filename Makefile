CXX = g++

INCLUDE_DIR = ./header
OBJDIR = obj
SRCDIR = src
SHDIR = bin
# seleziono tutti i file .c -> trasformo .o
SRCLIST = $(wildcard $(SRCDIR)/*.cpp)
OBJLIST =$(addprefix $(OBJDIR)/, $(patsubst %.cpp, %.o,$(notdir $(SRCLIST))))

# parametri aggiuntivi: warning + directory degli header
CXXFLAGS = -c -I$(INCLUDE_DIR) -Wall

# Linker options : ncurses
LDFLAGS =-lncurses

$(SHDIR)/RaceCar.sh :  $(OBJLIST)
	$(CXX) -o $@ $^  $(LDFLAGS)

# pulisco file non necessari dopo aver compilato
clean:
	-rm -f $(OBJDIR)/*.o $(SHDIR)/RaceCar.sh

# compilo i file .cpp in .o  -> -c -flagvarie  nomeFile.cpp
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS)  $< -o $@
