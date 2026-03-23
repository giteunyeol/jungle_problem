from collections import deque

node = int(input())
graph = {} # 노드들 어떻게 연결돼있는지 구현할 그래프
ans = [0] * (node + 1) #답을 저장할 arr
vis = [False] *(node + 1) #방문여부 저장
for i in range(1, node + 1):
    graph[i] = []

#양방향 그래프로 리스트 생성
for i in range(node - 1):
    a, b = map(int, input().split())
    graph[a].append(b)
    graph[b].append(a)

queue = deque()
queue.append(1)
vis[1] = True

while queue:
    cur = queue.popleft()
    for nxt in graph[cur]:
        if not vis[nxt] :
            ans[nxt] = cur
            vis[nxt] = True
            queue.append(nxt)

#ans에 저장했던 답 출력
for i in range(2, node + 1):
    print(ans[i])