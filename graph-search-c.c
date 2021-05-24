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

