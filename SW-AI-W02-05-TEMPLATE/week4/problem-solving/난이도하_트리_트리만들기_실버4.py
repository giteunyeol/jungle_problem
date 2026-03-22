n, m = map(int, input().split())

i = 0

for j in range(1, n):
    print(i, j)
    if(i < n-m):
        i+=1