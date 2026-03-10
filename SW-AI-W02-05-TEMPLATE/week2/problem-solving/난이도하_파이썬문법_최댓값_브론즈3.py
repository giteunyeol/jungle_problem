nums = list()

for i in range(9):
    nums.append(int(input()))

max = nums[0]
index = 0
for i in range(0, 9):
    if (nums[i] > max):
        max = nums[i]
        index = i

print(max)
print(index + 1)