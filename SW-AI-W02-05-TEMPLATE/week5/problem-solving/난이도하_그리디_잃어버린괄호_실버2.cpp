#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string formula;
    cin >> formula;
    
    int ans = 0;

    int num = 0; // 자릿수
    bool is_minus = false; // -가 나온 순간 그 후로는 다 음수로 더해줘야하니 판별할 변수

    for(int i = 0; i < formula.length(); i++)
    {
        if(formula[i] == '+') //+가 나오면
        {
            if(is_minus == true)
            {
                ans -= num;
                num = 0;
                continue;
            }
            else //아직 Minus가 안나온경우
            {
                ans += num;
                num = 0;
                continue;
            }
        }
        else if(formula[i] == '-') //-가 나오면
        {
            if(is_minus == true)
            {
                is_minus = true;
                ans -= num;
                num = 0;
                continue;
            }
            if(is_minus == false)
            {
                is_minus = true;
                ans += num;
                num = 0;
                continue;
            }
        }
        //위에서 안걸렸다면, 숫자라는 소리a
        num = num * 10 + (formula[i] - '0');
    }
    if(is_minus == false)
    {
        ans += num;
    }
    else
    {
        ans -= num;
    }
    cout << ans;

    return 0;
}

//리팩토링코드
/* 
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string formula;
    cin >> formula;

    int ans = 0;
    int num = 0;
    bool is_minus = false;

    for (int i = 0; i < formula.length(); i++) {
        if (isdigit(formula[i])) {
            num = num * 10 + (formula[i] - '0');
        } else {
            // 연산자 만났을 때 공통 처리
            if (is_minus) ans -= num;
            else ans += num;

            num = 0;

            // '-' 만나면 이후는 전부 빼기
            if (formula[i] == '-') {
                is_minus = true;
            }
        }
    }

    // 마지막 숫자 처리
    if (is_minus) ans -= num;
    else ans += num;

    cout << ans;
    return 0;
}
*/