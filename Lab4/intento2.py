import threading
import time
import logging

max_fila = {'mr':10, 'ct':8, 'bp':15, 'tb':15}
capacidad = {'mr':10, 'ct':2, 'bp':5, 'tb':1}
fila = {'mr':[], 'ct':[], 'bp':[], 'tb':[]}

logging.basicConfig(level=logging.DEBUG,
                    format='(%(threadName)-9s) %(message)s',)

def mr_juego(cv):
    logging.debug('mr_juego thread started ...')    
    print(fila['mr'])
    with cv:
        logging.debug('mr_juego waiting ...')
        cv.wait()
        logging.debug('mr_juego consumed the resource')

def mr_fila(cv):
    logging.debug('mr_fila thread started ...')
    with cv:
        if len(fila['mr']) < max_fila['mr']:
            t = threading.current_thread()
            fila['mr'].append(t)
            logging.debug('Making resource available')
            logging.debug('Notifying to all mr_juegos')
            for _ in range(3):
                cv.notifyAll()
        else:
            cv.wait()

def main(cv):
    mr_fila(cv)
    mr_juego(cv)

condition = threading.Condition()

cs1 = threading.Thread(target=main, args=(condition,))
cs2 = threading.Thread(target=main, args=(condition,))
pd = threading.Thread(target=main, args=(condition,))

cs1.start()
zc = [cs1]
# time.sleep(2)
cs2.start()
zc.append(cs2)
# time.sleep(2)
pd.start()
zc.append(pd)