Para utilizar el código se debe de entrar a la carpeta code, una vez dentro se debe de realizar el make
el cual compila todo el código, una vez compilado se debe de ejecutar de la siguiente forma
./tarea03 para trabajar con los parametros por defecto que estan definidos dentro del código.
Tambien se puede ejecutar con paramtros por consola los cuales son: 

--ncol ... --nfil ... --nt ... --plive ... --seq --show 
Donde:
	ncol es el número de columnas para el tablero
	nfil es el número de filas para el tablero
	nt es la cantidad de threas a trabajar, si esta opción no es ingresada, por defecto el código trabajara con la cantidad máxima de threads disponibles
	plive es la probabilidad de que las celulas aparescan
	seq es la opción para que el código se ejecute de manera secuencial, esta opción no es recomendable de utilizar en conjunto con la opción nt
	show es la opción para mostrar el tabler generado

Ejemplos de forma de uso:

./tarea03 --ncol 500 --nfil 500 --nt 8 --plive 0.8 --show

./tarea03 --ncol 500 --nfil 500 --seq

