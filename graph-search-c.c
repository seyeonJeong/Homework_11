#include<stdio.h>
#include<stdlib.h>

#define MAX_VTX 10 //최대 vertex수
//TRUE, FALSE 값을 선언
#define TRUE 1
#define FALSE 0
//for Graph
typedef struct Node {
    int vertex; // 정점의 값
    struct GraphNode* link; // edge연결을 위한 link
}GraphNode;

typedef struct Type {
    int vn; // 정점의 수
    GraphNode adj_list[MAX_VTX]; // 정점을 저장하는 배열
}GraphType;

//for queue

int queue[MAX_VTX];
int front = -1;
int rear = -1;

int deQueue(); // 큐삭제
void enQueue(int q); // 큐삽입
void init_queue(); //큐 초기화

int InitializeGraph(GraphType** h); // 그래프를 초기화해주는 함수
void InsertVertex(GraphType* h, int vn); // 정점을 삽입하는 함수
void InsertEdge(GraphType* h, int edgekey1, int edgekey2); // 간선을 연결해주는 함수
int FindVertex(GraphType* h, int edgekey); // 정점의 인덱스값을 찾는 함수
void PrintGraph(GraphType* h); //그래프를 출력하는 함수
void sort(GraphNode* n1, GraphType* h, int v); // 간선 연결시 정렬해주는 함수
void DFS_Graph(GraphType* h, int u); // DFS방식의 탐색
void bfs_list(GraphType* h, int v); //BFS방식의 탐색
void init_visited(); //visited를 초기화해주는 함수
void freegraph(GraphType** h); // 그래프를 해제해주는 함수
//for DFS & BFS
int visited[MAX_VTX]; //DFS와 BFS에서 방문했다는 표시를 해주는 배열






int main()
{
    char command;
    GraphType* h = NULL;
    int key;
    int edgekey1, edgekey2;
    int key2, key3;
    int u = 0;
    int v = 0;
    printf("[----- [정세연] [2018038027] -----]\n");

    do {
        printf("----------------------------------------------------------------\n");
        printf("                     Graph Searches                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Grape     = z  \n");
        printf(" Insert Vertex        = v          Insert Edge             = e \n");
        printf(" Depth First Search   = d          Breath First Search     = b\n");
        printf(" Print Graph          = p          Quit                    = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf_s(" %c", &command);

        switch (command) {
        case 'z': case 'Z':
            InitializeGraph(&h);
            break;
        case 'v': case 'V':
            printf("vertex의 값을 입력하시오 : ");
            scanf_s("%d", &key);
            InsertVertex(h, key);
            break;
        case 'e': case 'E':
            printf("vertex를 선택하시오 :");
            scanf_s("%d", &edgekey1);
            printf("\n");
            printf("연결할 vertex를 선택하시오 : ");
            scanf_s("%d", &edgekey2);
            printf("\n");

            InsertEdge(h, edgekey1, edgekey2);
            break;
        case 'd': case 'D':
            printf("첫번째 vertex를 고르세요 : ");
            scanf_s("%d", &key2);
            u = key2;
            DFS_Graph(h, u);
            init_visited();
            break;
        case 'b': case 'B':
            printf("첫번째 vertex를 고르세요 : ");
            scanf_s("%d", &key3);
            v = key3;
            bfs_list(h, v);
            init_visited();
            init_queue();
            break;
        case 'p': case 'P':
            PrintGraph(h);
            break;
        case 'q': case 'Q':
            freegraph(&h);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

int InitializeGraph(GraphType** h)
{
    int i;
    *h = (GraphType*)malloc(sizeof(GraphType)); //포인터 h에 동적할당을 해준다
    (*h)->vn = 0; //포인터h의 정점의 수를 0으로 만들어줌
    for (i = 0; i < MAX_VTX; i++)
    {
        //adj_list의 vertex와 link를 초기화해준다.
        (*h)->adj_list[i].vertex = -9999;
        (*h)->adj_list[i].link = NULL;
    }
    //visited배열의 값을 모두 FALSE로 설정
    for (int x = 0; x < MAX_VTX; x++)
    {
        visited[x] = FALSE;
    }

    return h;
}


void InsertVertex(GraphType* h, int key)
{
    if ((h->vn) + 1 > MAX_VTX) //만약 정점의 수가 설정된 최대 정점의 수보다 크다면 경고문구를 출력
    {
        printf("더이상 vertex를 생성할 수 없습니다!\n");
        return;
    }
    if (key >= MAX_VTX)
    {
        printf("key값 오류! \n");
        return;
    }
    for (int i = 0; i < h->vn; i++) //현재 정점의 수만큼 반복
    {
        if (h->adj_list[i].vertex == key) //만약 adj_list[i]의 정점의 값이 key값과 같다면
        {
            //중복이므로 return을 해준다
            return;
        }
    }
    h->adj_list[h->vn].vertex = key; // 현재 정점의 번호에 해당하는 인덱스의 vertex를 key로 설정
    h->adj_list[h->vn].link = NULL; // 현재 정점의 번호에 해당하는  인덱스의 link를 NULL로 설정
    h->vn = (h->vn) + 1; //정점의 번호에 1을 더해준다
}

void InsertEdge(GraphType* h, int edgekey1, int edgekey2)
{
    //필요한 변수 정의
    short int a = 0;
    int v1, v2 = 0;
    GraphNode* node1, * node2;


    for (int i = 0; i < h->vn; i++)
    {
        if (h->adj_list[i].vertex == edgekey1) //edgekey1와 같은 값을 가지는 정점이 존재하면 a에 1을 더해준다
        {
            a++;
        }
        if (h->adj_list[i].vertex == edgekey2) //edgekey2와 같은 값을 가지는 정점이 존재하면 a에 1을 더해준다
        {
            a++;
        }
    }
    if (a != 2) {
        //정점이 없습니다.
        return;
    }
    //FindVertex함수를 이용하여 v1과 v2에 해당 인덱스 번호를 받아옴
    v1 = FindVertex(h, edgekey1);
    v2 = FindVertex(h, edgekey2);
    //node1과 node2에 동적할당을 해준 후 vertex값을 각각 edgekey1,edgekey2로 설정해줌
    node1 = (GraphNode*)malloc(sizeof(GraphNode));
    node1->link = NULL;
    node1->vertex = edgekey1;
    node2 = (GraphNode*)malloc(sizeof(GraphNode));
    node2->link = NULL;
    node2->vertex = edgekey2;
    //값이 설정된 node2와 node1을 이용하여 정렬을 해주면서 간선을 연결해준다.
    sort(node2, h, v1);
    sort(node1, h, v2);

    return;
}
void DFS_Graph(GraphType* h, int u)
{
    int u1 = 0;
    u1 = FindVertex(h, u); // u1에 해당 vertex값에 해당하는 인덱스값을 받아줌
    int u2 = 0;

    GraphNode* cur = NULL;
    GraphNode* cur1 = NULL;
    cur = h->adj_list; //cur은 h->adj_list배열로 설정
    cur1 = cur[u1].link; // cur1을 해당 vertex값 즉, 사용자가 선택한 첫번째 탐색의 대상의 다음 link값을 설정
    //탐색 시작
    visited[u1] = TRUE; //첫번째 인덱스값에 해당하는 visited배열의 값을 TRUE로 설정한다.
    printf("%d", cur[u1].vertex); //u1의 인덱스값에 해당하는 vertex값을 출력
    printf("\n");

    for (cur1; cur1; cur1 = cur1->link) //cur[u1]의 link에 해당하는 노드부터 NULL값이 될때까지 link를 반복이동하며 탐색
    {
        u2 = FindVertex(h, cur1->vertex); //u2에 cur1의 vertex에 해당하는 인덱스값을 설정
        if (visited[u2] != TRUE) //만약 방문한 노드가 아니라면
            DFS_Graph(h, cur[u2].vertex); //재귀를 이용하여 해당노드에 대한 탐색을 실행
    }


}

void bfs_list(GraphType* h, int v)
{
    //변수 선언 및 초기화
    int u1 = 0;
    int u2 = 0;
    u1 = FindVertex(h, v); //  FindVertex함수를 이용하여 v의 값에 해당하는 인덱스 번호를 설정
    GraphNode* cur, * cur1 = NULL; //GraphNode를 카리키는 포인터 변수를 생성 후 초기화
    cur = h->adj_list; //cur에 h->adj_list를 설정

    init_queue(); // queue를 초기화해줌
    //탐색 시작
    visited[u1] = TRUE; //인덱스가 u1에 해당하는 visited의 값을 TRUE로 설정


    printf("%d ", cur[u1].vertex); //cur[u1]의 정점의 ㄱ밧을 출력
    printf("\n");
    enQueue(u1); //u1을 큐에 삽입
    while (u2 != -9999) //u2가 -9999, 즉 큐에 값이 없을 경우 종료
    {

        u2 = deQueue(); //u2는 큐의 첫번째 값

        if (u2 != -9999)  //u2가 -9999가 아니라면 (값이 존재한다면)
        {
            for (cur1 = cur[u2].link; cur1; cur1 = cur1->link) //cur1은 cur[u2]의 link에 해당하는 노드가 되고 cur1이 NULL값이 되면 종료
            {
                u2 = FindVertex(h, cur1->vertex); //u2는 cur1의 정점이 존재하는 adj_list의 인덱스값이 된다.
                if (visited[u2] != TRUE) // u2에 해당하는 인덱스번호에 접근하지 않았다면
                {
                    visited[u2] = TRUE; //visited[u2]의 값을 TRUE로 변경하여 방문하였다는 표시를 해줌
                    printf("%d ", cur[u2].vertex); //cur[u2]의 정점의 값을 출력
                    printf("\n");
                    enQueue(u2);//u2를 큐에 삽입

                }

            }
        }


    }
}

void init_queue()
{
    //큐를 초기화 해주는 함수 초기값을 -9999로 설정해준다
    int x = 0;
    rear = front = -1;
    for (x; x < MAX_VTX; x++)
    {
        queue[x] = -9999;
    }
}

void PrintGraph(GraphType* h)
{
    //변수 선언
    int i = 0;
    GraphNode* cur = NULL;
    GraphNode* cur1 = NULL;
    if (h->adj_list[0].vertex == -9999)
    {
        //만약 배열의 첫번째 vertex가 -9999라면 배열의 값이 존재하지 않으므로 경고문구를 출력
        printf("그래프가 비어있습니다.\n");
        return;
    }
    cur = h->adj_list; //cur을 h->adj_list로 설정
    for (i; i < (h->vn); i++) //현재 정점의 개수만큼 반복
    {
        printf("%d -> ", cur[i].vertex); //cur[i]의 정점의 값을 출력
        cur1 = cur[i].link; //cur1은 cur[i]의 link가 가리키는 노드가 됨
        while (cur1) //cur1이 NULL이 될때까지 반복
        {
            printf("  %d  ", cur1->vertex); //cur1의 vertex값을 출력한후
            cur1 = cur1->link; //cur1을 cur1의 link값으로 설정
        }
        printf("\n");
    }
}

