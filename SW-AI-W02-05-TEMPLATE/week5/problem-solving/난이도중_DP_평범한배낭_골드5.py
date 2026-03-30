n, k = map(int, input().split())

dp = [[0] * (k + 1) for _ in range(n + 1)]
items = [[0] * 2 for _ in range(n + 1)]
 
#첫번째값이 무게, 두번째값이 가치
for i in range(1, n + 1):
    items[i][0], items[i][1] = map(int, input().split())

dp[0][0] = 0

for i in range(1, n + 1): #i:물품 갯수만큼
    weight = items[i][0]
    value = items[i][1]

    for w in range(0, k + 1): #무게한도가 0 ~ k일때 얻을 수 있는 최대 가치
        dp[i][w] = dp[i - 1][w] #dp[i][w] = i번째 물건까지 고려했을때, 베낭 허용 무게가 w면 얻을 수 있는 최대 가치
        if weight <= w:
            dp[i][w] = max(dp[i][w], dp[i - 1][w - weight] + value)

print(dp[n][k])
    