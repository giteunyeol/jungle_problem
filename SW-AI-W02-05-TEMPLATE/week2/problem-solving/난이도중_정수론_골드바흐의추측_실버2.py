#두 짝수의 합 = 소수 + 소수

tc = int(input())
for k in range(tc): #tc번만큼 
    even_num = int(input())
    prime_list = []
    gap = 1e9 #처음에 굉장히 큰 숫자로 설정해놔서 바뀌게함, gap이 작을때 교체니까.
    first_num = 0 #나중에 출력할 첫번째,두번째 숫자
    second_num = 0  
    for i in range(even_num): # (even_num - 1) 까지 순회하면서 소수면 prime_list에 저장
        #숫자 I가 소수인지 아닌지!
        is_Prime = True
        for j in range(2, i):
            if i % j == 0:
                is_Prime = False
                break
        if is_Prime == True:
            prime_list.append(i)
    #투포인터로 순회. prime_list에 소수 리스트가 저장돼있음
    idx_1 = 0 #초기값은 둘다 0으로 초기화
    idx_2 = 0
    for cur_idx in range(1, len(prime_list)): #투포인터로 순회하려면 인덱스를 돌아야하니까 prime_list의 길이만큼 
        if prime_list[idx_1] + prime_list[idx_2] == even_num and prime_list[idx_2] - prime_list[idx_1] <= gap:
            first_num = prime_list[idx_1]
            second_num = prime_list[idx_2]
            gap = prime_list[idx_2] - prime_list[idx_1]
        #포인터 움직이기(idx_2 한칸 밀기)
        idx_2 = cur_idx 
        if prime_list[idx_1] + prime_list[idx_2] == even_num and prime_list[idx_2] - prime_list[idx_1] <= gap:
            first_num = prime_list[idx_1]
            second_num = prime_list[idx_2]
            gap = prime_list[idx_2] - prime_list[idx_1]
        #포인터 움직이기(idx_1 한칸 밀기)
        idx_1 = cur_idx
        if prime_list[idx_1] + prime_list[idx_2] == even_num and prime_list[idx_2] - prime_list[idx_1] <= gap:
            first_num = prime_list[idx_1]
            second_num = prime_list[idx_2]
            gap = prime_list[idx_2] - prime_list[idx_1]
    print(first_num, second_num)