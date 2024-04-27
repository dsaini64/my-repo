output: social_network.o user.o network.o post.o
	g++ -std=c++11 social_network.o user.o network.o -o output
social_network.o: social_network.cpp
	g++ -Wall -g -std=c++11 -c social_network.cpp -o social_network.o
user.o: user.cpp
	g++ -Wall -g -std=c++11 -c user.cpp -o user.o
network.o: network.cpp
	g++ -Wall -g -std=c++11 -c network.cpp -o network.o
post.o: post.cpp
	g++ -Wall -g -std=c++11 -c post.cpp -o post.o
clean:
	rm *.o output
