start_side = int(input())
white = 0
blue = 0 #전역변수

def recursion(side, x, y): #현재 변의 길이, x,y 좌표를 받아줌
    global white, blue

    #basecase 다 같은색 종이면 리턴
    #x,y부터 x + side, y + side까지검사, same_color가 false면 내려가서 재귀
    start_color = board[x][y]
    same_color = True #시작 변수 True로 초기화
    for i in range(x, x + side):
        for j in range(y, y + side):
            if start_color != board[i][j]: #현재 순회하고있는 좌표와 시작 컬러가 다르면 
                same_color = False #break문은 성능개선용임
                break
        if not same_color:
            break

    if same_color: #same컬러일때(같은 색일때 수를 더해주고 리턴)
        if start_color == 0: #0이면(white면)
            white += 1
        else:
            blue += 1
        return

    half = side // 2
     
    recursion(half, x, y)
    recursion(half, x, y + half)
    recursion(half, x + half, y)
    recursion(half, x + half, y + half)
        
#board에 입력받기
board = [list(map(int, input().split())) for _ in range(start_side)] #하얀색이 0, 파란색이 1
recursion(start_side, 0, 0)

print(white)
print(blue)