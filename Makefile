StarBlazer:
	@mkdir -p bin
	g++ *.h *.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o bin/StarBlazer
