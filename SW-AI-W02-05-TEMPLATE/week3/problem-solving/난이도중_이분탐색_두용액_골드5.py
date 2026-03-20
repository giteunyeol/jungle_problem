n = int(input())
solutions = list(map(int, input().split()))
solutions.sort() #solutions를 입력받아서 정렬

left = 0
right = len(solutions) - 1 #왼쪽, 오른쪽 끝 
sum = abs(solutions[left] + solutions[right]) #초기화
number1, number2 = solutions[left], solutions[right] #초기화

while left < right: #포인터 교차지점 까지
    if abs(solutions[left] + solutions[right]) < sum:
        sum = abs(solutions[left] + solutions[right]) #절댓값이 현재까지 찾은 값보다 작으면 정답 후보를 갱신
        number1 = solutions[left]
        number2 = solutions[right]
    if solutions[left] + solutions[right] < 0:
        left += 1
    elif solutions[left] + solutions[right] > 0:
        right -= 1
    else:
        print(solutions[left], solutions[right])
        exit(0)
print(number1, number2)
