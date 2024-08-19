br:
	g++ -o sorting.exe src/*.cpp     && sorting.exe
br1:
	g++ -o sorting.exe src/*.cpp -O1 && sorting.exe
br2:
	g++ -o sorting.exe src/*.cpp -O2 && sorting.exe
br3:
	g++ -o sorting.exe src/*.cpp -O3 && sorting.exe
