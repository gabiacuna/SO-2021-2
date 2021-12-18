import threading

sema = threading.Semaphore()
def count():
    sema.acquire()
    print("Start", threading.current_thread().getName())
    for i in range(1, 4):
        print(i)
    sema.release()

t = []

for _ in range(5):
    thread = threading.Thread(target=count)
    thread.start()
    t.append(thread)

for i in t:
    i.join()