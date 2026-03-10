Tc = int(input())

for i in range(Tc):
    arr = list(map(int, input().split()))
    n = arr[0]
    nums = arr[1:]
    average = sum(nums) / n
    over_average = 0
    for j in nums:
        if average < j:
            over_average += 1
    print(f"{(over_average / len(nums)) * 100:.3f}%")
