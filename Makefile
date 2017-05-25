all:
	g++ -std=c++11 main.cpp -o main
	g++ -std=c++11 temperature.cpp -o temperature
	g++ -std=c++11 altitude.cpp -o altitude
	g++ -std=c++11 vento.cpp -o vento
	g++ -std=c++11 passageiros.cpp -o passageiros
	g++ -std=c++11 velAviao.cpp -o velAviao
	g++ -std=c++11 distancia.cpp -o distancia
run:
	./temperature& ./altitude& ./vento& ./passageiros& ./velAviao& ./distancia& ./main