all:
	g++ soci-radius.cpp -o soci-radius -lsoci_core -ldl -I /usr/local/include/soci -Wall -ansi
