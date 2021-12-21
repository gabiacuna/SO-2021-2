import threading
import random as rand
import time
import queue
from datetime import datetime

# Variables/Constantes Globales
max_fila =[10,8,15,15]
capacidad = [10,2,5,1]
tiem = [5,3,7,2]

# Inicialización de las colas para cada juego
fila_mr = queue.Queue(1)    # En este caso solo se usa ajugar
ajugar_mr = queue.Queue(10)

fila_ct = queue.Queue(6)    # Max_Fila - Capacidad Juego
ajugar_ct = queue.Queue(2)  # Capacidad Juego

fila_bp = queue.Queue(10)
ajugar_bp = queue.Queue(5)

fila_tb = queue.Queue(4)
ajugar_tb = queue.Queue(1)

lock = threading.Lock()

# Listas de tuplas para registrar tiempos (cada tupla es lo que será una linea del arreglo)
registro_zc = []    # [(nombre, inicio, juego, fin), ...]
registro_mr = []    # [(nombre, inicio, fin), ...]
registro_ct = []    # [(nombre, inicio, fin), ...]
registro_bp = []    # [(nombre, inicio, fin), ...]
registro_tb = []    # [(nombre, inicio, fin), ...]
registro_sa = []    # [(nombre, fin), ...]


# Clase Persona, extiende a threading.Thread, por lo que un objeto Persona es un Thread.
class persona(threading.Thread):
    def __init__(self):
        super().__init__()
        # Se define a que juego va una persona
        self.juego = rand.randint(0, 3)
        
        # Se almacena el tiempo de llegada a la zona comun
        self.i = str(datetime.now().time())
        
        # Se relaciona a la persona con su fila y nombre de juego correspondiente
        if self.juego == 0:
            self.fila = fila_mr
            self.ajugar = ajugar_mr
            self.nombre = 'Montaña Rusa'
        elif self.juego == 1:
            self.fila = fila_ct
            self.ajugar = ajugar_ct
            self.nombre = 'Casa del Terror'
        elif self.juego == 2:
            self.fila = fila_bp
            self.ajugar = ajugar_bp
            self.nombre = 'Barco Pirata'
        elif self.juego == 3:
            self.fila = fila_tb
            self.ajugar = ajugar_tb
            self.nombre = 'Tiro al Blanco'
        
    def run(self):
        # Metemos a la persona actual a fila si ajugar esta lleno, o en ajugar si hay espacio
        if self.ajugar.full():
            self.fila.put(self)
            self.f = str(datetime.now().time())
            
        else:
            self.ajugar.put(self)
            self.f = str(datetime.now().time())
        
        # En un lock, agregamos la linea correspondiente al registro zona comun.
        lock.acquire()
        registro_zc.append((self.getName(), self.i, self.nombre ,self.f))
        lock.release()

        lock.acquire()
        # Si la queue ajugar esta llena, entran a jugar sus miembros.
        if self.ajugar.full():
            for _ in range(capacidad[self.juego]):
                # Sacamos a las personas de la cola, para que jueguen.
                jugando = self.ajugar.get()
                self.t_juego = str(datetime.now().time())
                print(jugando.getName(), 'jugando', self.nombre, flush=True)
               
            time.sleep(tiem[jugando.juego]) # tiempo de juego
            
            # Pasamos personas de la fila a ajugar, mientras podamos.
            while not self.ajugar.full() and not self.fila.empty():
                temp1 = self.fila.get()            
                self.ajugar.put(temp1)
            # Agregamos una linea al txt correspondiente.
            line = (self.getName(), self.f, self.t_juego)
            if self.juego == 0:
                registro_mr.append(line)
            elif self.juego == 1:
                registro_ct.append(line)
            elif self.juego == 2:
                registro_bp.append(line)
            elif self.juego == 3:
                registro_tb.append(line)
            registro_sa.append((self.getName(), str(datetime.now().time())))
        lock.release()
            
# Lista que guarda las threads creadas para hacer join mas adelante.
para_join = []

# Generar las Hebras
for i in range(40):
    p = persona()
    p.start()
    para_join.append(p)

# Join a todas las hebras para asegurar su finalizacion
for p in para_join:
    p.join()

### Archivos:

with open('ZonaComun.txt', 'w') as file:
    for nombre, inicio, juego, fin in registro_zc:
        nombre = nombre.replace('Thread', 'Persona')
        line = nombre + ', ' + inicio + ', ' + juego + ', ' + fin + '\n'
        file.write(line)

with open('MontañaRusa.txt', 'w') as file:
    for nombre, inicio, fin in registro_mr:
        nombre = nombre.replace('Thread', 'Persona')
        line = nombre + ', ' + inicio + ', ' + fin + '\n'
        file.write(line)
    
with open('CasaTerror.txt', 'w') as file:
    for nombre, inicio, fin in registro_ct:
        nombre = nombre.replace('Thread', 'Persona')
        line = nombre + ', ' + inicio + ', ' + fin + '\n'
        file.write(line)

with open('BarcoPirata.txt', 'w') as file:
    for nombre, inicio, fin in registro_bp:
        nombre = nombre.replace('Thread', 'Persona')
        line = nombre + ', ' + inicio + ', ' + fin + '\n'
        file.write(line)

with open('TiroBlanco.txt', 'w') as file:
    for nombre, inicio, fin in registro_tb:
        nombre = nombre.replace('Thread', 'Persona')
        line = nombre + ', ' + inicio + ', ' + fin + '\n'
        file.write(line)

with open('Salida.txt', 'w') as file:
    for nombre, hora in registro_sa:
        nombre = nombre.replace('Thread', 'Persona')
        line = nombre + ', ' + hora + '\n'
        file.write(line)