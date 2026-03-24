from collections import deque

node_count = int(input())

node_list = [[] for _ in range(node_count + 1)] #node 연결여부
node_use_time = [0] * (node_count + 1) #해당 노드 작업 소요시간
indegree = [0] * (node_count + 1) #indegree갯수 저장해줄 리스트
node_end_time = [0] * (node_count + 1) #현재 노드 끝나는데까지 얼마나 걸렸는지 저장할 리스트

for i in range(1, node_count + 1):
    temp = list(map(int, input().split()))
    node_use_time[i] = temp[0]
    for j in range(2, temp[1] + 2): #temp[1]번만큼 node_list에 삽입
        node_list[temp[j]].append(i)
        indegree[i] += 1 #indegree값 더해줌

queue = deque()

for i in range(1, node_count + 1):
    if indegree[i] == 0: #indegree값이 0이면
        node_end_time[i] = node_use_time[i]
        queue.append(i)
    
while queue:
    cur = queue.popleft() #팝 해주고 
    for i in node_list[cur]:#해당 노드가 선행조건인 노드들 indegree 하나씩 빼줌
        node_end_time[i] = max(node_end_time[cur] + node_use_time[i], node_end_time[i]) #지금 cur가 선행조건인 그 다음 작업 노드의 시간을 계산해줌
        indegree[i] -= 1
        if indegree[i] == 0: #indegree[i]가 0이 되면
            queue.append(i) 

print(max(node_end_time))