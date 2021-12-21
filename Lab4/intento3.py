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

lock = threading.Lock()

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

        while (not q.empty()):
            
            lock.acquire()
            persona = q.get()
            lock.release()
            
            persona.cv_fila.acquire()
            n_juego = 0 #rand.randint(0,3)
            # Vemos que juega / Se crea variable condicional para el juego
            cola_mr.put(persona)
            # print('Entro: ', list(cola_mr.queue), '\nCont:', fila[n_juego])
            fila[n_juego] += 1
            print(threading.current_thread().getName(), 'en fila')

            while fila[n_juego] > capacidad[n_juego]:
                time.sleep
            
            persona.cv_fila.release()
            
            persona.cv_juego.acquire()

            # print('\tfila[n_juego] =' , fila[n_juego], '\n\t fila =', list(cola_mr.queue))
            
            while fila[n_juego] < capacidad[n_juego]:   # Aca juegan los primeros capacidad personas
                persona.cv_juego.acquire()
                persona.cv_juego.wait()
                persona.cv_juego.release()
                time.sleep(0.2)     # Jugando
                cola_mr.task_done()
                fila[n_juego] -= 1
                print(threading.current_thread().getName(), 'jugo')
                persona.cv_juego.release()  
                quit()

            while fila[n_juego] == capacidad[n_juego]: # Aca se completa el grupo
                # cv_juego.notify_all()
                # cola_juego = queue.Queue(capacidad[n_juego])
                for _ in range(capacidad[n_juego] - 1):
                    jugador = cola_mr.get()
                    # print('Salida :\n',list(cola_mr.queue), '\nCont:', fila[n_juego])
                    print(jugador.getName())
                    jugador.cv_juego.acquire()
                    jugador.cv_juego.notify() 
                    jugador.cv_juego.release()
                    jugador.join()
                # Para el ultimo jugador
                jugador = cola_mr.get()
                # print('Salida :\n',list(cola_mr.queue), '\nCont:', fila[n_juego])
                time.sleep(0.2) # Jugando
                cola_mr.task_done()
                fila[n_juego] -= 1
                jugador.join()
                print(threading.current_thread().getName(), 'jugo')
                jugador.cv_juego.release()


                quit()


# zc = []
for i in range(20):
    p = persona()
    p.start()
    q.put(p)
time.sleep(1)
print(q.empty())
