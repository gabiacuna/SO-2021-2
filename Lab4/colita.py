import queue
import threading

q = queue.Queue(maxsize=5)
cv = threading.Condition()

def foo():
    print(threading.currentThread().getName(), 'se esta ejec 1')
    cv.acquire()
    cv.wait()
    cv.release()
    print(threading.currentThread().getName(), 'se esta ejec 2')

cont = 0
for i in range(7):
    if cont >= 2:
        t = q.get()
        cv.acquire()
        cv.notify()
        cv.release()
    else:
        t = threading.Thread(target=foo)
        t.start()
        cont += 1
        q.put(t)
        print(list(q.queue))
