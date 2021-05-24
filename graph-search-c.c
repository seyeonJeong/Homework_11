#include<stdio.h>
#include<stdlib.h>

#define MAX_VTX 10 //�ִ� vertex��
//TRUE, FALSE ���� ����
#define TRUE 1
#define FALSE 0
//for Graph
typedef struct Node {
    int vertex; // ������ ��
    struct GraphNode* link; // edge������ ���� link
}GraphNode;

typedef struct Type {
    int vn; // ������ ��
    GraphNode adj_list[MAX_VTX]; // ������ �����ϴ� �迭
}GraphType;

//for queue

int queue[MAX_VTX];
int front = -1;
int rear = -1;

int deQueue(); // ť����
void enQueue(int q); // ť����
void init_queue(); //ť �ʱ�ȭ

int InitializeGraph(GraphType** h); // �׷����� �ʱ�ȭ���ִ� �Լ�
void InsertVertex(GraphType* h, int vn); // ������ �����ϴ� �Լ�
void InsertEdge(GraphType* h, int edgekey1, int edgekey2); // ������ �������ִ� �Լ�
int FindVertex(GraphType* h, int edgekey); // ������ �ε������� ã�� �Լ�
void PrintGraph(GraphType* h); //�׷����� ����ϴ� �Լ�
void sort(GraphNode* n1, GraphType* h, int v); // ���� ����� �������ִ� �Լ�
void DFS_Graph(GraphType* h, int u); // DFS����� Ž��
void bfs_list(GraphType* h, int v); //BFS����� Ž��
void init_visited(); //visited�� �ʱ�ȭ���ִ� �Լ�
void freegraph(GraphType** h); // �׷����� �������ִ� �Լ�
//for DFS & BFS
int visited[MAX_VTX]; //DFS�� BFS���� �湮�ߴٴ� ǥ�ø� ���ִ� �迭






int main()
{
    char command;
    GraphType* h = NULL;
    int key;
    int edgekey1, edgekey2;
    int key2, key3;
    int u = 0;
    int v = 0;
    printf("[----- [������] [2018038027] -----]\n");

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
            printf("vertex�� ���� �Է��Ͻÿ� : ");
            scanf_s("%d", &key);
            InsertVertex(h, key);
            break;
        case 'e': case 'E':
            printf("vertex�� �����Ͻÿ� :");
            scanf_s("%d", &edgekey1);
            printf("\n");
            printf("������ vertex�� �����Ͻÿ� : ");
            scanf_s("%d", &edgekey2);
            printf("\n");

            InsertEdge(h, edgekey1, edgekey2);
            break;
        case 'd': case 'D':
            printf("ù��° vertex�� �������� : ");
            scanf_s("%d", &key2);
            u = key2;
            DFS_Graph(h, u);
            init_visited();
            break;
        case 'b': case 'B':
            printf("ù��° vertex�� �������� : ");
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
