import time
import threading
import random

def beberDelVaso(cond):
    while not cond.acquire(False):
        time.sleep(0.5)

    time.sleep(random.randint(1, 10))
    cond.release()

    nombre = threading.current_thread().name
    print(f"Thread {nombre} terminada")

def ejercicio4():
    hilos = []
    cond = threading.Condition()

    for i in range(20):
        nombre = f"t{i+1}"
        print(f"Lanzando thread {nombre}")
        t = threading.Thread(target=beberDelVaso, name=nombre, args=(cond, ))
        hilos.append(t)
        t.start()

    for i in range(len(hilos)):
        hilos[i].join()

    print('¡El programa ha finalizado!')

ejercicio4()