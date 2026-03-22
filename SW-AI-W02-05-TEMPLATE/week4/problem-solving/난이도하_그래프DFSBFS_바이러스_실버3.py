from collections import deque
computer_count = int(input())
edge = int(input())

graph = [[] for i in range(computer_count + 1)] #그래프 초기화
visited = [0] * (computer_count + 1)

for i in range(edge):
    a, b = map(int, input().split())
    
    graph[a].append(b) #양방향 연결
    graph[b].append(a) 

queue = deque()
queue.append(1)
visited[1] = 1

while queue:
    front = queue.popleft()
    for nx in graph[front]:
        if visited[nx] == 0:
            queue.append(nx)
            visited[nx] = 1

print(sum(visited) - 1)       

