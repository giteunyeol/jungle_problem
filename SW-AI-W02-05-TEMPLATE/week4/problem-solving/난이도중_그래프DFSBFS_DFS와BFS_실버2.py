from collections import deque

n, m, v = map(int, input().split()) #노드 갯수, 엣지 갯수, start노드

graph = {}
for i in range(1, n + 1):  #그래프 초기화
    graph[i] = []


for i in range(m): #삽입
    a, b = map(int, input().split())
    graph[a].append(b)
    graph[b].append(a)

for i in range(1, n + 1):
    graph[i].sort() #작은것부터 해야하니 우선 sort 

stack = []
vis = [False] * (n + 1) #DFS
dfs_save = []
stack.append(v)

while stack:
    cur = stack.pop()
    if vis[cur]:
        continue

    vis[cur] = True
    dfs_save.append(cur)

    for nxt in reversed(graph[cur]):
        stack.append(nxt)



queue = deque() #큐 선언
vis = [False] * (n + 1) #BFS 해야하니 다시 초기화
bfs_save = []
queue.append(v)
vis[v] = True

while queue:
    cur = queue.popleft() 
    bfs_save.append(cur)
    for nxt in graph[cur]:
        if not vis[nxt]: #만약 nxt가 방문하지 않았다면
            queue.append(nxt) 
            vis[nxt] = True

print(*dfs_save)
print(*bfs_save)
