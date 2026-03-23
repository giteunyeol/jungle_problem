#전위순회: 루트 -> 왼쪽 -> 오른쪽
#후위순회: 왼쪽 -> 오른쪽 -> 루트 

import sys
sys.setrecursionlimit(20000)

preorder = [] #preorder에 숫자 삽입
for line in sys.stdin:
    preorder.append(int(line))

def solve(start, end):
    if start > end: #base case
        return 
    
    root = preorder[start]

    mid = end + 1
    for i in range(start + 1, end + 1): #i가 preorder
        if preorder[i] > root:
            mid = i
            break
    
    solve(start+1, mid - 1)
    solve(mid, end)
    print(root)

solve(0, len(preorder) - 1)