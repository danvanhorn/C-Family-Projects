CC = g++
exe = assn4

$(exe): game.o player.o room.o event.o bat.o wumpus.o gold.o pit.o driver.o errorcheck.o
	$(CC) game.o player.o room.o event.o bat.o wumpus.o gold.o pit.o driver.o errorcheck.o -g -o $(exe)

game.o: game.cpp
	$(CC) -c game.cpp

player.o: player.cpp
	$(CC) -c player.cpp

room.o: room.cpp
	$(CC) -c room.cpp 

event.o: event.cpp
	$(CC) -c event.cpp 

bat.o: bat.cpp
	$(CC) -c bat.cpp 

wumpus.o: wumpus.cpp
	$(CC) -c wumpus.cpp 

gold.o: gold.cpp
	$(CC) -c gold.cpp 

pit.o: pit.cpp
	$(CC) -c pit.cpp 

driver.o: driver.cpp
	$(CC) -c driver.cpp

errorcheck.o: errorcheck.cpp
	$(CC) -c errorcheck.cpp

clean:
	rm -f *.o a.out $(exe) 

debug:
	$(CC) game.cpp player.cpp room.cpp event.cpp bat.cpp wumpus.cpp gold.cpp pit.cpp driver.cpp errorcheck.cpp -D DEBUG -g -o  $(exe)
