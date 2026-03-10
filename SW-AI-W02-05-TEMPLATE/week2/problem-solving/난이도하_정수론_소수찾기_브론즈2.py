import math

tc = int(input())
ans = 0 #답을 출력할 변수

numbers = list(map(int, input().split()))
for i in numbers: # i 로 numbers순회
    if i == 1:
        continue
    is_prime = True 
    for j in range(2, math.floor(math.sqrt(i)) + 1): #2부터 number의 루트를 씌운 값까지 순회
        if i % j == 0:
            is_prime = False
            break
    if is_prime:
        ans += 1
        
    
print(ans)