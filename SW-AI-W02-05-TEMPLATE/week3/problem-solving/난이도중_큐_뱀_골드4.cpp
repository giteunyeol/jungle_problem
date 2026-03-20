#include <iostream>
#include <deque>
#include <queue>

using namespace std;

#define X first // first
#define Y second 

bool board[102][102]; //false로 초기화 하고 사과가 있는 곳을 True로 갱신. ((n - 1) * (n - 1)

int dx[4] = {1, 0, -1, 0}; //dx,dy를 조합해서 방향. 0 1 2 3 차례대로 남 동 북 서
int dy[4] = {0, 1, 0, -1};
int dir = 1; //초기값은 오른쪽을 향함
int cur_time = 0;  // 진행되면서 체크할 현재 시간
pair<int, int> head = {0, 0}; //head에 뱀의 머리 좌표 저장, 덱에서 뽑아서 바로 해도 될 것 같은데 그냥 편하게 하려고 따로 둠

void game_end(int n, deque<pair <int, int>> snake) // 현재 시간, 좌표, 보드의 크기를 받아옴
{
    //cout << "test 보드 실행!!! -> " << "x좌표:" << head.X << " y좌표:" << head.Y << "\n";
    //보드에 부딪힘
    if(head.X < 0 || head.Y < 0 || head.X >= n || head.Y >= n)
    {
        cout << cur_time;
        exit(0);
    }

    int idx = 0;
    for(auto i : snake)
    {   
        if(idx++ == 0) continue; //제일 처음 인덱스 스킵
        
        if(i.X == head.X && i.Y == head.Y)
        {
            cout << cur_time;
            exit(0);
        }
        
    }
}

void spin_head(char cmd) //뱀이 머리를 돌리는 함수
{
    if(cmd == 'L')
    {
        dir++;
        if(dir > 3) { dir = 0; }      
    }
    else //cmd == D인 경우에, 인덱스 넘어가면 반대 끝으로 보내줌
    {
        dir--;
        if(dir < 0) { dir = 3; }
    }
}

// 1.헤드가 먼저 움직임, 그래서 머리가 다음칸으로 이동
// 2.헤드가 벽이나 자기 자신의 몸과 부딛히면 게임 종료

// 3. if 헤드가 위치한 자리에 사과가 있으면? 사과가 없어짐, 꼬리 가만히 있음.
// 4. else(헤드 위치에 사과가 없다면), 꼬리위치칸을 비워줌. 몸길이는계속 유지!

// 그러니까 head, tail의 좌표를 계속 세이브 해줘야할듯? 그리고 몸 좌표도 계속 세이브 해놔야할 것 같음. 몸이랑 테일은 걍 큐로 연결하면 되겠네

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n; 
    cin >> k; //k만큼 사과의 위치를 입력받음 

    //사과위치 저장, [n - 1][n - 1]로 저장했음! 0,0부터 시작할거니까
    for(int i = 0; i < k; i++)
    {
        int col, row;
        cin >> col >> row;
        board[col - 1][row - 1] = true; // col - 1, row - 1
    }

    int L;
    cin >> L; //커맨드 몇번 실행될건지 입력받음
    queue < pair <int, char> > time_cmd_q; //시간과 커맨드를 저장할 큐
    
    //큐에 입력받는 for문
    for (int i = 0; i < L; i++)
    {
        //time_Q에 푸쉬, X가 몇초 이후인지, Y가 커맨드가 뭔지
        int time;
        char cmd;
        cin >> time >> cmd;
        time_cmd_q.push({time, cmd}); //time과 커맨드를 받아서 큐에 푸쉬
    }
    
    deque <pair<int, int>> snake; //뱀의 좌표를 저장! 머리를 늘리면 덱 앞에 넣어주고, 꼬리는 덱의 뒤쪽에.
    snake.push_back({0, 0}); //snake가 0초일때 시작값을 넣어줌, 방향값은 전역으로 오른쪽을 보게 선언해 놓음(변수명: dir)

    while(true) //game_end에 닿을때까지 무한루프
    {
        cur_time++; //시간 증가. 뱀이 행동을 시작함
        //cout << "테스트 현재 시간" << cur_time << "\n"; //////////////////test
        //행동1. 몸이 벽이나 자기 자신의 몸과 부딪히면 게임종료.
        head.X += dx[dir]; //우선 좌표 이동
        head.Y += dy[dir];
        game_end(n, snake); // 행동2. 게임이 끝나는지 체크한다
        snake.push_front({head.X, head.Y}); // 머리를 뱀의 프론트에 넣어줌

        // 이동했는데 헤드가 위치한곳에 사과가 있는 경우
        if (board[head.X][head.Y] == true)
        {
            board[head.X][head.Y] = false;
        }
        else // 사과가 없는 경우 board[head.X][head.Y] == false
        {
            snake.pop_back(); // 덱 제일 뒤 팝
        }
        
        // X초가 끝난 뒤에 머리 스핀
        if (cur_time == time_cmd_q.front().X && !time_cmd_q.empty()) // 큐의 제일 처음 요소가 시간이니 비어있지 않고, 시간이 같으면 if문 실행
        {
            //cout << "현재 방향" << dir << "\n";
            spin_head(time_cmd_q.front().Y); // 머리를 돌림, 제일 처음 요소의 커맨드 가져옴
            time_cmd_q.pop();                     // 그리고 팝
            //cout << "현재 방향" << dir << "\n";
        }
    }

    return 0;
}