import threading
import time
import logging
import random as rand
import queue

#max_fila = {'mr':10, 'ct':8, 'bp':15, 'tb':15}
#capacidad = {'mr':10, 'ct':2, 'bp':5, 'tb':1}
#fila = {'mr':[], 'ct':[], 'bp':[], 'tb':[]}

max_fila =[10,8,15,15]
capacidad = [10,2,5,1]
fila = [0,0,0,0]

q = queue.Queue(0)
cola_mr = queue.Queue(10)

cv_fila = threading.Condition()
cv_juego = threading.Condition()

class persona(threading.Thread):
    def __init__(self):
        super().__init__()
        self.cv_fila = threading.Condition()
        self.cv_juego = threading.Condition()
        
    def run(self):
        time.sleep(0.1)
        print(threading.current_thread().getName(), 'creada')

        # cv_fila.acquire()
        # n_juego = 0 #rand.randint(0,3)
        # # Vemos que juega / Se crea variable condicional para el juego
        
        # while len(fila[n_juego]) >= max_fila[n_juego]:
        #     cv_fila.wait()
        # fila[n_juego] += 1
        # q.put(threading.currentThread())
        # cv_fila.release()
        # cv_juego.acquire()

        # while fila[n_juego] >= capacidad[0]: # Aca juuegan los primeros capacidad personas
        #     cv_juego.notify_all()
        # while fila[n_juego] < capacidad[0]:
        #     cv_juego.wait()

        # for _ in range(capacidad[n_juego]):
        #     q.get()
        #     time.sleep(0.2) # Sleep por tiempo juego/capacidad
        #     q.task_done()

# zc = []
for i in range(10):
    p = persona()
    p.start()
    q.put(p)
time.sleep(1)
print(q.empty())
# while (not q.empty() and threading.current_thread().getName() != "MainThread"):
while (True):
    print(1)
    persona = q.get()

    persona.cv_fila.acquire()
    n_juego = 0 #rand.randint(0,3)
    # Vemos que juega / Se crea variable condicional para el juego
    cola_mr.put(persona)
    fila[n_juego] += 1
    print(threading.current_thread().getName(), 'en fila')

    # while fila[n_juego] > capacidad[n_juego]:
    #     persona.cv_fila.wait()
    
    persona.cv_fila.release()
    
    persona.cv_juego.acquire()
    
    while fila[n_juego] < capacidad[n_juego]: # Aca juegan los primeros capacidad personas
        persona.cv_juego.wait()
        time.sleep(0.2) # Jugando
        cola_mr.task_done()
        fila[n_juego] -= 1
        print(threading.current_thread().getName(), 'jugo')
        jugador.cv_juego.release()

    while fila[n_juego] == capacidad[n_juego]: # Aca se completa el grupo
        # cv_juego.notify_all()
        for _ in range(capacidad[n_juego] - 1):
            jugador = cola_mr.get()
            jugador.cv_juego.notify()
        
        # Para el ultimo jugador
        jugador = cola_mr.get()
        time.sleep(0.2) # Jugando
        cola_mr.task_done()
        fila[n_juego] -= 1
        print(threading.current_thread().getName(), 'jugo')
        jugador.cv_juego.release()


    




        
        
        

