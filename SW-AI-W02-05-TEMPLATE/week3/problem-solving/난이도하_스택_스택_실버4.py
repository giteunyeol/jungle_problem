tc = int(input())
stack = []
for _ in range(tc):
    cmd = input().split() # 둘이 나누고 첫번째 인덱스를 가져옴
    
    if cmd[0] == "push":
        stack.append(int(cmd[1]))
    elif cmd[0] == "pop":
        if not stack:
            print("-1")
        else:
            print(stack[-1])
            stack.pop()
    elif cmd[0] == "size":
        print(len(stack))
    elif cmd[0] == "empty":
        if not stack:
            print("1")
        else:
            print("0")
    elif cmd[0] == "top":
        if not stack:
            print("-1")
        else:
            print(stack[-1])