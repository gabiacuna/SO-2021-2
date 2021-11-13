## Integrantes:

* Tomás Morales, rol : 201973611-6, par : 200
* Gabriela Acuña, rol : 201973504-7, par : 200

## Para compilar

Utilizar `make` para compilar y ejecutar todo nuestro codigo. `make valg` para ejecutar nuestro programa con Valgrind y `make clean` para eliminar las files extras creadas en la compilación del codigo.

## Jugabilidad

Para jugar Monopoly, solo es necesario apretar enter o cualquier tecla cuando se pida por pantalla. 

Para poder ver bien la interfaz, se debe poner el terminal en pantalla completa (o tamalo 195 x 55, filas x columnas, mínimo).

Una vez gane un jugador, se mostrará un mensaje por pantalla durante 10 segundos y luego se cerrará el programa. 

Sabemos que existe un pequeño leak de memoria, de 5 bloques, que todavia son alcanzables, debido a la libreria que utilizamos para mostrar el juego, ncurses. Enviamos mail previamente a los ayudantes para notificiar y consultar sobre esto. 