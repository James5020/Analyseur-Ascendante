# Variables
CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = analyseur

# Liste des fichiers objets (.o) que l'on veut générer
OBJS = main.o automate.o lexer.o symbole.o etat.o

# Règle par défaut (ce qui s'exécute quand on tape juste "make")
all: $(TARGET)

# 1. ÉDITION DE LIENS : On assemble tous les .o pour créer l'exécutable final
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# 2. COMPILATION SÉPARÉE : Règle générique pour transformer un .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle pour tout nettoyer (les .o et l'exécutable)
clean:
	del /Q *.o $(TARGET).exe