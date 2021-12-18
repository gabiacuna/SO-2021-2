import threading

max_fila = {'mr':10, 'ct':8, 'bp':15, 'tb':15}
capacidad = {'mr':10, 'ct':2, 'bp':5, 'tb':1}
fila = {'mr':[], 'ct':[], 'bp':[], 'tb':[]}

lock = threading.Lock()
entrar = threading.Condition()
salir = threading.Condition()

def montania_rusa_fila():
    lock.acquire()
    t = threading.current_thread()
    print(t.getName(), 'fila')
    
    while not (len(fila['mr']) < max_fila['mr']):
        salir.wait()
    
    fila['mr'].append(t)

    if len(fila['mr']) == max_fila['mr']:
        entrar.notify_all()
        
    lock.release()

def montania_rusa_juego():
    lock.acquire()
    t = threading.current_thread()
    print(t.getName(), 'juego')
    while len(fila['mr']) < capacidad['mr']:
        entrar.wait()
    i = fila['mr'].index(t)
    del fila['mr'][i]
    if len(fila['mr']) == 0:
        salir.notify_all
    lock.release()

def montania_rusa():
    montania_rusa_fila()
    montania_rusa_juego()

inicio = 5
zona_comun = []

for i in range(inicio):
    t = threading.Thread(target=montania_rusa)
    
    t.start()
    zona_comun.append(t)

for thread in zona_comun:
    print(thread.getName())
    thread.join()