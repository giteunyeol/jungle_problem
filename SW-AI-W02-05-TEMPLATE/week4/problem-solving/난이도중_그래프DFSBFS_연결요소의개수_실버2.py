#무방향 그래프
#bfs로 순회하고 while문 만약 들어가면 카운트 하나 올려서 출력하면 될듯

import sys
from collections import deque
input = sys.stdin.readline

n, m = map(int, input().split()) # N : 노드의 갯수, M: edge의 갯수 

connections = 0 #연결요소 갯수 저장
vis = [False] * (n + 1)
graph = {}
for i in range(n + 1):
    graph[i] = []

for _ in range(m):
    a, b = map(int, input().split())
    graph[a].append(b)
    graph[b].append(a)

queue = deque()

for i in range(1, n + 1): #1 ~ n + 1까지
    if not vis[i]: #방문한적이 없다면
        queue.append(i) #큐에 넣고 방문표시 남김
        vis[i] = True
        connections += 1

        while queue:
            cur = queue.popleft()
            for nxt in graph[cur]:
                if vis[nxt] == 0:
                    queue.append(nxt)
                    vis[nxt] = True
    

print(connections)