all:
	g++ -std=c++11 -c functions.cpp -o functions
	g++ -std=c++11 gerenciador.cpp -o gerenciador
	g++ -std=c++11 temperature.cpp -o temperature
	g++ -std=c++11 altitude.cpp -o altitude
	g++ -std=c++11 dirVento.cpp -o dirVento
	g++ -std=c++11 passageiros.cpp -o passageiros
	g++ -std=c++11 velAviao.cpp -o velAviao
	g++ -std=c++11 distancia.cpp -o distancia

run:
	./gerenciador

clean:
	rm -f functions gerenciador temperature altitude dirVento passageiros velAviao distancia

kill:
	ps axf | grep temperature | grep -v grep | awk '{print "kill " $1}' | sh
	ps axf | grep altitude | grep -v grep | awk '{print "kill " $1}' | sh
	ps axf | grep dirVento | grep -v grep | awk '{print "kill " $1}' | sh
	ps axf | grep passageiros | grep -v grep | awk '{print "kill " $1}' | sh
	ps axf | grep velAviao | grep -v grep | awk '{print "kill " $1}' | sh
	ps axf | grep distancia | grep -v grep | awk '{print "kill " $1}' | sh

