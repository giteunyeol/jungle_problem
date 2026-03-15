tc = int(input())
strings = [] #문자열들 세이브할 리스트
for i in range(tc):
    cur_string = input()
    if cur_string == cur_string[::-1]: #회문인 경우
        print(len(cur_string), cur_string[len(cur_string) // 2])
        exit(0)
    else: #회문이 아닌 경우 
        #string를 순회하며 회문이 있는지 검사해보고, 없다면 string에 푸쉬
        for j in strings:
            if cur_string == j[::-1]: #현재 문자열과 저장된 문자열들을 뒤집은 것
                print(len(cur_string), cur_string[len(cur_string) // 2])
                exit(0)
        strings.append(cur_string)#순회를 다 했는데 회문이 없는 경우

