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
            printf("ù��° vertex�� ������ : ");
            scanf_s("%d", &key2);
            u = key2;
            DFS_Graph(h, u);
            init_visited();
            break;
        case 'b': case 'B':
            printf("ù��° vertex�� ������ : ");
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
    *h = (GraphType*)malloc(sizeof(GraphType)); //������ h�� �����Ҵ��� ���ش�
    (*h)->vn = 0; //������h�� ������ ���� 0���� �������
    for (i = 0; i < MAX_VTX; i++)
    {
        //adj_list�� vertex�� link�� �ʱ�ȭ���ش�.
        (*h)->adj_list[i].vertex = -9999;
        (*h)->adj_list[i].link = NULL;
    }
    //visited�迭�� ���� ��� FALSE�� ����
    for (int x = 0; x < MAX_VTX; x++)
    {
        visited[x] = FALSE;
    }

    return h;
}


void InsertVertex(GraphType* h, int key)
{
    if ((h->vn) + 1 > MAX_VTX) //���� ������ ���� ������ �ִ� ������ ������ ũ�ٸ� ������� ���
    {
        printf("���̻� vertex�� ������ �� �����ϴ�!\n");
        return;
    }
    if (key >= MAX_VTX)
    {
        printf("key�� ����! \n");
        return;
    }
    for (int i = 0; i < h->vn; i++) //���� ������ ����ŭ �ݺ�
    {
        if (h->adj_list[i].vertex == key) //���� adj_list[i]�� ������ ���� key���� ���ٸ�
        {
            //�ߺ��̹Ƿ� return�� ���ش�
            return;
        }
    }
    h->adj_list[h->vn].vertex = key; // ���� ������ ��ȣ�� �ش��ϴ� �ε����� vertex�� key�� ����
    h->adj_list[h->vn].link = NULL; // ���� ������ ��ȣ�� �ش��ϴ�  �ε����� link�� NULL�� ����
    h->vn = (h->vn) + 1; //������ ��ȣ�� 1�� �����ش�
}

void InsertEdge(GraphType* h, int edgekey1, int edgekey2)
{
    //�ʿ��� ���� ����
    short int a = 0;
    int v1, v2 = 0;
    GraphNode* node1, * node2;


    for (int i = 0; i < h->vn; i++)
    {
        if (h->adj_list[i].vertex == edgekey1) //edgekey1�� ���� ���� ������ ������ �����ϸ� a�� 1�� �����ش�
        {
            a++;
        }
        if (h->adj_list[i].vertex == edgekey2) //edgekey2�� ���� ���� ������ ������ �����ϸ� a�� 1�� �����ش�
        {
            a++;
        }
    }
    if (a != 2) {
        //������ �����ϴ�.
        return;
    }
    //FindVertex�Լ��� �̿��Ͽ� v1�� v2�� �ش� �ε��� ��ȣ�� �޾ƿ�
    v1 = FindVertex(h, edgekey1);
    v2 = FindVertex(h, edgekey2);
    //node1�� node2�� �����Ҵ��� ���� �� vertex���� ���� edgekey1,edgekey2�� ��������
    node1 = (GraphNode*)malloc(sizeof(GraphNode));
    node1->link = NULL;
    node1->vertex = edgekey1;
    node2 = (GraphNode*)malloc(sizeof(GraphNode));
    node2->link = NULL;
    node2->vertex = edgekey2;
    //���� ������ node2�� node1�� �̿��Ͽ� ������ ���ָ鼭 ������ �������ش�.
    sort(node2, h, v1);
    sort(node1, h, v2);

    return;
}
void DFS_Graph(GraphType* h, int u)
{
    int u1 = 0;
    u1 = FindVertex(h, u); // u1�� �ش� vertex���� �ش��ϴ� �ε������� �޾���
    int u2 = 0;

    GraphNode* cur = NULL;
    GraphNode* cur1 = NULL;
    cur = h->adj_list; //cur�� h->adj_list�迭�� ����
    cur1 = cur[u1].link; // cur1�� �ش� vertex�� ��, ����ڰ� ������ ù��° Ž���� ����� ���� link���� ����
    //Ž�� ����
    visited[u1] = TRUE; //ù��° �ε������� �ش��ϴ� visited�迭�� ���� TRUE�� �����Ѵ�.
    printf("%d", cur[u1].vertex); //u1�� �ε������� �ش��ϴ� vertex���� ���
    printf("\n");

    for (cur1; cur1; cur1 = cur1->link) //cur[u1]�� link�� �ش��ϴ� ������ NULL���� �ɶ����� link�� �ݺ��̵��ϸ� Ž��
    {
        u2 = FindVertex(h, cur1->vertex); //u2�� cur1�� vertex�� �ش��ϴ� �ε������� ����
        if (visited[u2] != TRUE) //���� �湮�� ��尡 �ƴ϶��
            DFS_Graph(h, cur[u2].vertex); //��͸� �̿��Ͽ� �ش��忡 ���� Ž���� ����
    }


}

void bfs_list(GraphType* h, int v)
{
    //���� ���� �� �ʱ�ȭ
    int u1 = 0;
    int u2 = 0;
    u1 = FindVertex(h, v); //  FindVertex�Լ��� �̿��Ͽ� v�� ���� �ش��ϴ� �ε��� ��ȣ�� ����
    GraphNode* cur, * cur1 = NULL; //GraphNode�� ī��Ű�� ������ ������ ���� �� �ʱ�ȭ
    cur = h->adj_list; //cur�� h->adj_list�� ����

    init_queue(); // queue�� �ʱ�ȭ����
    //Ž�� ����
    visited[u1] = TRUE; //�ε����� u1�� �ش��ϴ� visited�� ���� TRUE�� ����


    printf("%d ", cur[u1].vertex); //cur[u1]�� ������ ������ ���
    printf("\n");
    enQueue(u1); //u1�� ť�� ����
    while (u2 != -9999) //u2�� -9999, �� ť�� ���� ���� ��� ����
    {

        u2 = deQueue(); //u2�� ť�� ù��° ��

        if (u2 != -9999)  //u2�� -9999�� �ƴ϶�� (���� �����Ѵٸ�)
        {
            for (cur1 = cur[u2].link; cur1; cur1 = cur1->link) //cur1�� cur[u2]�� link�� �ش��ϴ� ��尡 �ǰ� cur1�� NULL���� �Ǹ� ����
            {
                u2 = FindVertex(h, cur1->vertex); //u2�� cur1�� ������ �����ϴ� adj_list�� �ε������� �ȴ�.
                if (visited[u2] != TRUE) // u2�� �ش��ϴ� �ε�����ȣ�� �������� �ʾҴٸ�
                {
                    visited[u2] = TRUE; //visited[u2]�� ���� TRUE�� �����Ͽ� �湮�Ͽ��ٴ� ǥ�ø� ����
                    printf("%d ", cur[u2].vertex); //cur[u2]�� ������ ���� ���
                    printf("\n");
                    enQueue(u2);//u2�� ť�� ����

                }

            }
        }


    }
}

void init_queue()
{
    //ť�� �ʱ�ȭ ���ִ� �Լ� �ʱⰪ�� -9999�� �������ش�
    int x = 0;
    rear = front = -1;
    for (x; x < MAX_VTX; x++)
    {
        queue[x] = -9999;
    }
}

void PrintGraph(GraphType* h)
{
    //���� ����
    int i = 0;
    GraphNode* cur = NULL;
    GraphNode* cur1 = NULL;
    if (h->adj_list[0].vertex == -9999)
    {
        //���� �迭�� ù��° vertex�� -9999��� �迭�� ���� �������� �����Ƿ� ������� ���
        printf("�׷����� ����ֽ��ϴ�.\n");
        return;
    }
    cur = h->adj_list; //cur�� h->adj_list�� ����
    for (i; i < (h->vn); i++) //���� ������ ������ŭ �ݺ�
    {
        printf("%d -> ", cur[i].vertex); //cur[i]�� ������ ���� ���
        cur1 = cur[i].link; //cur1�� cur[i]�� link�� ����Ű�� ��尡 ��
        while (cur1) //cur1�� NULL�� �ɶ����� �ݺ�
        {
            printf("  %d  ", cur1->vertex); //cur1�� vertex���� �������
            cur1 = cur1->link; //cur1�� cur1�� link������ ����
        }
        printf("\n");
    }
}

