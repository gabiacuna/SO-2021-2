# Links Útiles

# https://www.geeksforgeeks.org/synchronization-by-using-semaphore-in-python/
# https://docs.python.org/3/library/asyncio-sync.html
# https://rico-schmidt.name/pymotw-3/threading/

# Ejemplo:
# https://www.bogotobogo.com/python/Multithread/python_multithreading_Synchronization_Semaphore_Objects_Thread_Pool.php

import threading
from random import randint
import time

max_fila = {'mr':10, 'ct':8, 'bp':15, 'tb':15}
capacidad = {'mr':10, 'ct':2, 'bp':5, 'tb':1}
fila = {'mr':[], 'ct':[], 'bp':[], 'tb':[]}

#threading.Condition()

lock = threading.Lock()
mr_fila = threading.Condition()
mr_juego = threading.Condition()

'''
Montaña Rusa
• Capacidad de la fila: 10 personas 
• Duración del juego: 5 segundos
• Capacidad del juego: 10 personas
'''

def montania_rusa_juego():
    t = threading.current_thread()
    print(t.getName(), "mr_juego")
    
    mr_juego.acquire()

    i = zona_comun.index(t)
    del zona_comun[i]

    if len(zona_comun) == 0:
        print(t.getName(), " no puede jugar :c")
        mr_fila.acquire()
        mr_fila.notify()
        mr_fila.release()
        mr_juego.release()
        return

    #while len(fila['mr']) < capacidad['mr']:
    print('esperando a jugar')
    mr_juego.wait()

    # time.sleep(5) #Jugar!
    print(t.getName(), "jugando.....")
    #for i in range(capacidad['mr']):
     #  fila['mr'][i].join()
    #for _ in range(capacidad['mr']):
    #    del fila['mr'][0]
    i = fila['mr'].index(t)
    del fila['mr'][i]

    
    print('llega aca')
    mr_fila.acquire()
    mr_fila.notify()
    mr_fila.release()
    mr_juego.release()

def montania_rusa_fila():
    t = threading.current_thread()

    print(t.getName() , 'mr fila')

    mr_fila.acquire()
    while len(fila['mr']) >= max_fila['mr']:
        mr_fila.wait()
    
    fila['mr'].append(t)

    montania_rusa_juego()

    if len(fila['mr']) == capacidad['mr']:
        print('notify juego')
        time.sleep(1)
        mr_juego.acquire()
        mr_juego.notify_all()
        mr_juego.release()

    mr_fila.release()
        # Entran a la fila
        # si hay cap, que jueguen

# def montania_rusa():
#     duracion = 5 #segundos
#     montania_rusa_fila()
#     montania_rusa_juego()



'''
Casa del Terror
• Capacidad de la fila: 8 personas
• Duración del juego: 3 segundos
• Capacidad del juego: 2 personas
'''
def casa_terror():
    max_fila = 0
    duracion = 3 #segundos
    capacidad = 2

    print('Casa Terror')
    time.sleep(0.5)
    t = threading.current_thread()
    print('\t' ,t.getName(),'\n')

'''
Barco Pirata
• Capacidad de la fila: 15 personas
• Duración del juego: 7 segundos
• Capacidad del juego: 5 personas
'''
def barco_pirata():
    max_fila = 15
    duracion = 7 #segundos
    capacidad = 5
    print('BP')
    time.sleep(0.5)
    t = threading.current_thread()
    print('\t' ,t.getName(),'\n')

'''
Tiro al Blanco
• Capacidad de la fila: 5 personas
• Duración del juego: 2 segundos
• Capacidad del juego: 1 persona
'''
def tiro_al_blanco():
    max_fila = 5
    duracion = 2 #segundos
    capacidad = 1
    print('TB')
    time.sleep(0.5)
    t = threading.current_thread()
    print('\t' ,t.getName(),'\n')

'''
No tiene límite de personas
Personas serán representadas por hebras
Cada vez que una persona llegue al parque, irá a una atracción aleatoria, y luego se irá del parque.
El acceso desde la fila al juego no puede ser interrumpido, y debe ser por orden de llegada.
'''

# def zona_comun():

inicio = 11
zona_comun = []

for i in range(inicio):
    # destino = randint(0,3)
    destino = 0
    if destino == 0:
        t = threading.Thread(target=montania_rusa_fila)
    if destino == 1:
        t = threading.Thread(target=casa_terror)
    if destino == 2:
        t = threading.Thread(target=barco_pirata)
    if destino == 3:
        t = threading.Thread(target=tiro_al_blanco)
    
    zona_comun.append(t)
    t.start()

for thread in zona_comun:
    print(thread.getName())
    thread.join()

print(fila)