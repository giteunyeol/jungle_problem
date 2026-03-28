number = int(input())

dp = [0] * 1000002
dp[1] = 1
dp[2] = 2 


for i in range(3, number + 1):
    dp[i] = (dp[i - 1] + dp[i - 2]) % 15746

print(dp[number])