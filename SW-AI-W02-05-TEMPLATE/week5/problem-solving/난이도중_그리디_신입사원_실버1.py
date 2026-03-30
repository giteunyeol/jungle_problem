import sys
input = sys.stdin.readline

tc = int(input()) 

for _ in range(tc):
    app_count = int(input()) #이번 테스트 케이스에 지원자가 몇명인지
    applicants = [[0] * 2 for _ in range(app_count)]
    ans = 1
    for i in range(app_count):
        applicants[i][0], applicants[i][1] = map(int, input().split())

    applicants = sorted(applicants)
    min = applicants[0][1] #참가자들 0번 인덱스: 서류성적, 1번 인덱스: 면접 성적
    for i in range(1, len(applicants)):
        if min > applicants[i][1]:
            min = applicants[i][1]
            ans += 1
    print(ans)