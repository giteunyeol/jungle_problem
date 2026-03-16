from collections import deque

n = int(input())
queue = deque()

for i in range(1, n + 1):
    queue.append(i)

while(True):
    #한장 남았을때 탈출
    if len(queue) == 1:
        print(queue[0])
        exit(0)
    queue.popleft()
    queue.append(queue[0])
    queue.popleft()