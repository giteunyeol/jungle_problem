meet_count = int(input())

meetings = [[0] * 2 for _ in range(meet_count)] #인덱스 0번은 시작시간, 1번은 끝나는 시간

for i in range(meet_count):
    meetings[i][0], meetings[i][1] = map(int, input().split()) 

meetings.sort(key = lambda x: (x[1], x[0]))

selected = []
selected.append(meetings[0]) # 첫번째 meeting의 종료시간 삽입
ans = 1

for i in range(1, meet_count):
    if selected[-1][1] <= meetings[i][0]:
        selected.append(meetings[i])
        ans += 1
print(ans)
