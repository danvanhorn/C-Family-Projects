CC = g++
exe = assn2

$(exe):  hand.o deck.o driver.o player.o dealer.o game.o card.o
	$(CC) driver.o hand.o deck.o player.o dealer.o game.o card.o -g -o $(exe)
hand.o: hand.cpp
	$(CC) -c hand.cpp
deck.o: deck.cpp
	$(CC) -c deck.cpp
driver.o: driver.cpp
	$(CC) -c driver.cpp
player.o: player.cpp
	$(CC) -c player.cpp
dealer.o: dealer.cpp
	$(CC) -c dealer.cpp
game.o: game.cpp
	$(CC) -c game.cpp
card.o: card.cpp
	$(CC) -c card.cpp


clean:
	rm -f a.out $(exe) *.o 
