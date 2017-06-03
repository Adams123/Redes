Instruções de compilação:

Utilizando o Makefile, apenas um make all irá compilar todos os arquivos na ordem correta. Caso ocorra algum problema com o Makefile, os comandos
	g++ -std=c++11 -c functions.cpp -o functions
	g++ -std=c++11 gerenciador.cpp -o gerenciador
	g++ -std=c++11 temperature.cpp -o temperature
	g++ -std=c++11 altitude.cpp -o altitude
	g++ -std=c++11 dirVento.cpp -o dirVento
	g++ -std=c++11 passageiros.cpp -o passageiros
	g++ -std=c++11 velAviao.cpp -o velAviao
	g++ -std=c++11 distancia.cpp -o distancia
irão compilar todo o necessário. Para iniciar, utilize make run OU ./gerenciador. Também está disponível um make clean para limpar todos os arquivos gerados.