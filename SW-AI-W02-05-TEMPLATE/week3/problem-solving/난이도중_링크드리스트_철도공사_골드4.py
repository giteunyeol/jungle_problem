import sys 
input = sys.stdin.readline

n, m = list(map(int, input().split()))  
arr = [0] * 1000002
prev_arr = [0] * 1000002
temp_input = list(map(int, input().split()))

#삽입
for i in range(n):
    cur = temp_input[i]
    nxt = temp_input[(i + 1) % n]
    arr[cur] = nxt
    prev_arr[nxt] = cur

result = []

for i in range(m):
    cmd = input().split()
    command = cmd[0]
    value = int(cmd[1])
    if command == "BN": #커맨드로 BN이 들어오면
        j = int(cmd[2])
        nxt = arr[value]
        result.append(str(nxt))

        # value -> j -> nxt
        arr[value] = j
        arr[j] = nxt
        prev_arr[j] = value
        prev_arr[nxt] = j
    elif command == "BP":
        j = int(cmd[2])
        prev = prev_arr[value]
        result.append(str(prev))

        # value -> j -> prev
        arr[prev] = j
        prev_arr[j] = prev
        arr[j] = value
        prev_arr[value] = j
    elif command == "CN": #고유번호 i를 가진 다음 역을 폐쇄, 그 역의 번호 출력. command이 커맨드, value이 고유번호, arr[value]이 다음 주소
        p_nxt = arr[value]
        result.append(str(p_nxt))

        nxt = arr[p_nxt] #다음 주소 가리키는 포인터
        arr[value] = nxt
        prev_arr[nxt] = value
    else: #커맨드:CP
        p_prev = prev_arr[value]
        result.append(str(p_prev))

        prev = prev_arr[p_prev] #다음 주소 가리키는 포인터
        prev_arr[value] = prev
        arr[prev] = value
    
print("\n".join(result))