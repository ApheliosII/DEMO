import random
import time

def T_worker(name):
    i = 0
    while (i := i + 1):
        print(f'[{name}] i = {i}')
        time.sleep(1)
        yield()

threads = [T_worker(i) for i in range(1000000)]
while True:
    random.choice(threads).send(None)
