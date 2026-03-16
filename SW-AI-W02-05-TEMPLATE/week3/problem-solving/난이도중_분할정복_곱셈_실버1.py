a, b, c = map(int, input().split())

def recursion(a, b, c):
    if b == 0:
        return 1

    temp = recursion(a, b // 2, c)

    if b % 2 == 0: #짝수일 경우
        return (temp * temp) % c
    else:
        return (temp * temp * a) % c

print(recursion(a, b, c))
