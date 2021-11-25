## Integrantes:

* Tomás Morales, rol : 201973611-6, par : 200
* Gabriela Acuña, rol : 201973504-7, par : 200

## Para compilar

Utilizar `make` para compilar y ejecutar todo nuestro codigo. `make clean` para eliminar las files .class creadas en la compilación del codigo.


## Tener en cuenta

- En morseThread, se agregan los atributos abc y my_dict, para guardar las letras y sus traducciones en un HashTable para más facil acceso. 

- Para medir los tiempos de ejecución, a cada clase *Thread, se le implementaron los atributos inicio y fin, inicio se asigna cuando se llama al constructor con el tiempo de inicio, y fin se asigna cuando termina la ejecución de la hebra correspondiente. Para calcular los tiempos, se llama al método printTime. El tiempo es calculado en **MiliSegundos** (con `System.currentTimeMillis()`). 