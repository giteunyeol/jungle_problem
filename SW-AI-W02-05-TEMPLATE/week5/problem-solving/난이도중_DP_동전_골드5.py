tc = int(input())

for _ in range(tc):
    coin_count = int(input())
    coins = list(map(int, input().split())) #코인들을 저장할 리스트 
    dest = int(input()) #dest는 목표치 가격 
    dp = [[0] * (dest + 1) for _ in range(len(coins) + 1)]

    dp[0][0] = 1

    for i in range(1, len(coins) + 1):
        dp[i][0] = 1
        for j in range(1, dest + 1):
            if coins[i - 1] > j:
                dp[i][j] = dp[i - 1][j]
            else:
                dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i - 1]]
    
    print(dp[coin_count][dest])


"""
tc = int(input())

for _ in range(tc):
    n = int(input())
    coins = list(map(int, input().split()))
    m = int(input())

    # dp[j] = j원을 만드는 경우의 수
    dp = [0] * (m + 1)
    
    # 0원을 만드는 방법은 "아무것도 안 고르는 경우" 1개
    dp[0] = 1

    # 동전을 하나씩 추가하면서 경우의 수 누적
    for coin in coins:
        
        # coin부터 시작하는 이유:
        # j < coin이면 coin을 사용할 수 없기 때문
        for j in range(coin, m + 1):
            
            # 핵심 점화식
            # (j - coin)을 만드는 모든 방법 뒤에 coin 하나 붙이기
            dp[j] += dp[j - coin]

    # m원을 만드는 총 경우의 수
    print(dp[m])
"""

