string = input().upper()

nums = [0] * 26 #인덱스 a to z까지 0 to 25

for i in string: #인덱스를 순회, I 가 인덱스
    nums[ord(i) - ord('A')] += 1

max_val = max(nums)

if nums.count(max_val) >= 2:
    print("?")
else:
    print(chr(nums.index(max_val) + ord('A')))
    
