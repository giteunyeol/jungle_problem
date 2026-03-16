#처음 풀이
"""
top_count = int(input())
top_height_save = map(int, input().split())
top_height_save = list(top_height_save)
print_list = []
for i in range(top_count):
    start_height = top_height_save[i] #0번부터 순회
    cur_index = i
    
    while cur_index != 0:
        cur_index -= 1 # 한칸씩 왼쪽으로 감
        if top_height_save[cur_index] >= start_height:
            print_list.append(cur_index + 1)
            break
    if cur_index == 0:
        print_list.append(0)

print(*print_list, sep=' ', end ='')
print()
"""


n = int(input())
tops = list(map(int, input().split())) #top에 높이 저장
ans = [0] * n
stack = [] #[index, value] 순서로 넣을거임

for i in range(n):
    while stack:
        if stack[-1][1] >= tops[i]: # 스택이 차있고 제일 최근에 삽입된 탑의 밸류값이 현재 판별할 탑보다 높거나 같을때
            ans[i] = stack[-1][0]
            break   
        else: 
            stack.pop()
    stack.append([i + 1, tops[i]])

print(*ans)
    

     