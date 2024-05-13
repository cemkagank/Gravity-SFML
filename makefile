default:
	mkdir -p build
	g++ -o ./build/gravity ./src/main.cpp -lsfml-graphics -lsfml-window -lsfml-system -O3
	g++ -o ./build/gravityv2 ./src/main2.cpp -lsfml-graphics -lsfml-window -lsfml-system -O3
run:
	./build/gravity
2:
	./build/gravityv2
