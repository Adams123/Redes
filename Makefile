all:
	g++ -std=c++11 -c functions.cpp -o functions
	g++ -std=c++11 main.cpp -o main
	g++ -std=c++11 gerenciador.cpp -o gerenciador
	g++ -std=c++11 temperature.cpp -o temperature
	g++ -std=c++11 altitude.cpp -o altitude
	g++ -std=c++11 dirVento.cpp -o dirVento
	g++ -std=c++11 passageiros.cpp -o passageiros
	g++ -std=c++11 velAviao.cpp -o velAviao
	g++ -std=c++11 distancia.cpp -o distancia

run:
	./temperature& ./altitude& ./dirVento& ./passageiros& ./velAviao& ./distancia& ./main

clean:
	rm -f temperature altitude dirVento main gerenciador functions velAviao passageiros distancia