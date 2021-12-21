import threading
import time
import random as rand
import queue

max_fila =[10,8,15,15]
capacidad = [10,2,5,1]
tiem = [5,3,7,2]
fila = [0,0,0,0]

fila_mr = queue.Queue(1)
ajugar_mr = queue.Queue(10)

fila_ct = queue.Queue(6)
ajugar_ct = queue.Queue(2)

fila_bp = queue.Queue(10)
ajugar_bp = queue.Queue(5)

fila_tb = queue.Queue(4)
ajugar_tb = queue.Queue(1)


lock = threading.Lock()


registro_zc = []    # [(nombre, inicio, juego, fin), ...]
registro_mr = []    # [(nombre, inicio, fin), ...]
registro_ct = []    # [(nombre, inicio, fin), ...]
registro_bp = []    # [(nombre, inicio, fin), ...]
registro_tb = []    # [(nombre, inicio, fin), ...]
registro_sa = []    # [(nombre, fin), ...]


class persona(threading.Thread):
    def __init__(self):
        super().__init__()
        self.cv_fila = threading.Condition()
        self.cv_juego = threading.Condition()
        self.juego = rand.randint(0, 3)
        
        self.i = time.time()
        self.t_juego = 0
        

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
        
        if self.ajugar.full():
            self.fila.put(self)
            self.f = time.time()
            print(self.getName(), 'en cola para', self.nombre, flush=True)
        else:
            self.ajugar.put(self)
            self.f = time.time()
            print(self.getName(), 'en cola para', self.nombre, flush=True)
        
        lock.acquire()
        registro_zc.append((self.getName(), self.i, self.nombre ,self.f))
        lock.release()

        

        lock.acquire()
        if self.ajugar.full():
            # print('1. ajugar:',list(ajugar.queue), flush=True)
            # print('1. cola:',list(cola.queue), flush=True)
            for _ in range(capacidad[self.juego]):
                jugando = self.ajugar.get()
                self.t_juego = time.time()
                print(jugando.getName(), 'jugando', self.nombre, flush=True)
                # jugando.join()
            time.sleep(tiem[jugando.juego]) # tiempo de juego
            
            while not self.ajugar.full() and not self.fila.empty():
                temp1 = self.fila.get()            
                self.ajugar.put(temp1)
            # print('2. ajugar:',list(ajugar.queue), flush=True)
            # print('2. cola:',list(cola.queue), flush=True)
        line = (self.getName(), self.f, self.t_juego)
        if self.juego == 0:
            registro_mr.append(line)
        elif self.juego == 1:
            registro_ct.append(line)
        elif self.juego == 2:
            registro_bp.append(line)
        elif self.juego == 3:
            registro_tb.append(line)
        registro_sa.append((self.getName(), time.time()))
        lock.release()
            
        

        #Espera inicial
        
        # print('Esperando a jugar:', self.getName(), flush=True)
        # self.cv_juego.acquire()
        # self.cv_juego.wait()
        # self.cv_juego.release()
        # time.sleep(1)
        # print('Termino thread:', self.getName(), flush=True)
        # fin
        
para_join = []

for i in range(20):
    p = persona()
    p.start()
    para_join.append(p)

for p in para_join:
    p.join()

### Archivos:

print(registro_zc)
print(registro_mr)
print(registro_ct)
print(registro_bp)
print(registro_tb)
print(registro_sa)
