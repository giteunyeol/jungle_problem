Tc = int(input())

for i in range(Tc):
    R, alp_string = list(input().split())
    R = int(R)
    result_string = ""
    for j in alp_string:
        result_string += j * R
    print(result_string)
