CC = g++
INCLUDES = /usr/include
LIBS = /usr/lib
FLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

StarBlazer:
	@mkdir -p obj/
	@mkdir -p bin/
	${CC} -c -I${INCLUDES} -L${LIBS} src/Engine/*.cpp ${FLAGS}
	${CC} -c -I${INCLUDES} -L${LIBS} src/Entities/*.cpp ${FLAGS}
	${CC} -c -I${INCLUDES} -L${LIBS} src/Levels/*.cpp ${FLAGS}
	${CC} -c -I${INCLUDES} -L${LIBS} includes.cpp ${FLAGS}
	${CC} -c -I${INCLUDES} -L${LIBS} main.cpp ${FLAGS}
	@mv *.o obj/
	${CC} -g -I${INCLUDES} -L${LIBS} obj/Engine.o obj/CollisionDetection.o obj/Demo.o obj/GarbageCollector.o obj/Gfx.o obj/HUD.o obj/Intro.o obj/Menu.o obj/Mission.o obj/NameEntry.o obj/PreMission.o obj/Renderer.o obj/Timer.o obj/Bullet.o obj/Entities.o obj/Explosion.o obj/Meteor.o obj/Player.o obj/Regular.o obj/Level1.o obj/LevelTemplate.o obj/includes.o obj/main.o ${FLAGS} -o bin/StarBlazer

nocomp:
	${CC} -g -I${INCLUDES} -L${LIBS} obj/Engine.o obj/CollisionDetection.o obj/Demo.o obj/GarbageCollector.o obj/Gfx.o obj/HUD.o obj/Intro.o obj/Menu.o obj/Mission.o obj/NameEntry.o obj/PreMission.o obj/Renderer.o obj/Timer.o obj/Bullet.o obj/Entities.o obj/Explosion.o obj/Meteor.o obj/Player.o obj/Regular.o obj/Level1.o obj/LevelTemplate.o obj/includes.o obj/main.o ${FLAGS} -o bin/StarBlazer

only:
	@mkdir -p obj/
	@mkdir -p bin/
	${CC} -c -I${INCLUDES} -L${LIBS} src/Engine/*.cpp ${FLAGS}
	${CC} -c -I${INCLUDES} -L${LIBS} src/Entities/*.cpp ${FLAGS}
	${CC} -c -I${INCLUDES} -L${LIBS} src/Levels/*.cpp ${FLAGS}
	${CC} -c -I${INCLUDES} -L${LIBS} includes.cpp ${FLAGS}
	${CC} -c -I${INCLUDES} -L${LIBS} main.cpp ${FLAGS}
	@mv *.o obj/

clean:
	@rm obj/*.o
	@rm -f bin/StarBlazer
