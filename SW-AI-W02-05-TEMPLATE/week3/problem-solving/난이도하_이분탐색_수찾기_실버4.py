N = int(input())
save = set(map(int, input().split()))
M = int(input())
is_exist = map(int, input().split())
for i in is_exist:
    if i in save:
        print(1)
    else:
        print(0)

