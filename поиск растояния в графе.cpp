#include <iostream>
#include <list>
#include <queue>
using namespace std;

template<typename T>
class MyList {
public:
    class Iterator;
    MyList() : size(0), head(nullptr), tail(nullptr) {}
    ~MyList() {}

    T GetSize() { return size; }
    bool isEmpty() { return(head == nullptr); }
    void push_back(T data);
    T& operator[](const T index);
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }


private:

    template<typename T>
    struct Node {
        T data;
        Node* next;
        Node* pred;

        Node(T data = T(), Node* pNext = nullptr, Node* pPred = nullptr) {
            this->data = data;
            this->next = pNext;
            this->pred = pPred;
        }
    };
    int size;
    Node<T>* head;
    Node<T>* tail;
};
template<typename T>
class MyList<T>::Iterator
{
    Node<T>* ptr;
public:

    Iterator() : ptr(nullptr) {};
    Iterator(Node<T>* p) : ptr(p) {}
    Iterator& operator ++ ()
    {
        if (ptr)
        {
            ptr = ptr->next; //Может быть еще и здесь кинуть исключение
            return *this;
        }
    }
    Iterator& operator -- ()
    {
        if (ptr)
        {
            ptr = ptr->pred;
            return *this;
        }
        else
        {
            ptr = tail;
            return *this;
        }
    }
    T& operator * ()
    {
        if (ptr)
            return ptr->data;

    }
    bool operator != (const Iterator& it) { return ptr != it.ptr; }
    bool operator == (const Iterator& it) { return ptr == it.ptr; }
};
template<typename T>
void MyList<T>::push_back(T data)
{
    Node<T>* temp = new Node<T>(data);
    temp->next = 0;
    temp->data = data;
    temp->pred = tail;

    if (tail != nullptr)
        tail->next = temp;

    if (size == 0) {
        head = tail = temp;
    }
    else {
        tail = temp;
    }
    size++;
}
template<typename T>
T& MyList<T>::operator[](const T index)
{
    int counter_1 = 0, counter_2 = size;
    Node<T>* current_1 = this->head;
    Node<T>* current_2 = this->tail;
    while (current_1 != nullptr || current_2 != nullptr)
    {
        if (counter_1 == index)
            return current_1->data;
        if (counter_2 == index + 1)
            return current_2->data;

        current_1 = current_1->next;
        current_2 = current_2->pred;
        counter_2--;
        counter_1++;
    }
}


class Graph {
private:
    bool* visited;
    /////////////////
    bool** adjMatrix;
    MyList<int>* adjLists;
    int numVertices;

public:

    Graph(int numVertices)
    {
        this->numVertices = numVertices;
        adjMatrix = new bool* [numVertices];
        visited = new bool[numVertices];
        adjLists = new MyList<int>[numVertices];

        for (int i = 0; i < numVertices; i++) {
            adjMatrix[i] = new bool[numVertices];
            visited[i] = false;
            for (int j = 0; j < numVertices; j++)
                adjMatrix[i][j] = false;
        }
    }
    ~Graph() {
        for (int i = 0; i < numVertices; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;
        delete[]visited;
    }
    void memseting(bool a) {
        for (int i = 0; i < numVertices; i++)
            visited[i] = a;
    }
    void toMatrix() {
        for (int i = 0; i < numVertices; i++) {
            cout << i << " : ";
            for (int j = 0; j < numVertices; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    void addEdge(int i, int j) {
        adjMatrix[i][j] = adjMatrix[j][i] = true;

        adjLists[i].push_back(j);
        adjLists[j].push_back(i);
    }

    void BFS_S(int start, int dest);
    void BFS(int start, int dest);
    void DFS_S(int st, int dest);
    void DFS(int v, int dest);

};
void Graph::BFS_S(int start, int dest)
{
    int* dist = new int[numVertices];
    int* pred = new int[numVertices];
    queue<int> queue;

    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }

    visited[start] = true;
    dist[start] = 0;
    queue.push(start);

    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        for (int i = 0; i < adjLists[u].GetSize(); i++) {
            if (!visited[adjLists[u][i]]) {
                visited[adjLists[u][i]] = true;
                queue.push(adjLists[u][i]);
                dist[adjLists[u][i]] = dist[u]++;
                pred[adjLists[u][i]] = u;

                if (adjLists[u][i] == dest) {
                    cout << dest << " ";
                    while (pred[dest] != -1) {
                        cout << pred[dest] << " ";
                        dest = pred[dest];
                    }
                    delete[]dist;
                    delete[]pred;
                    return;
                }
            }
        }
    }
    delete[]dist;
    delete[]pred;
}

void Graph::BFS(int start, int dest)
{
    int* dist = new int[numVertices];
    int* pred = new int[numVertices];
    queue<int> queue;

    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }

    visited[start] = true;
    dist[start] = 0;
    queue.push(start);

    while (!queue.empty()) {
        start = queue.front();
        queue.pop();

        for (int i = 0; i < numVertices; i++) {
                if (adjMatrix[start][i] == 1 && (!visited[i])) {
                    visited[i] = true;
                    queue.push(i);
                    dist[i] = dist[start]++;
                    pred[i] = start;

                    if (i == dest) {
                        cout << dest << " ";
                        while (pred[dest] != -1) {
                            cout << pred[dest] << " ";
                            dest = pred[dest];
                        }
                        delete[]dist;
                        delete[]pred;
                        return;
                    }

                }
            }
    }
    delete[]dist;
    delete[]pred;
}

void Graph::DFS_S(int start, int dest)
{
    visited[start] = true;
    cout << start << " ";

    if (start == dest)
        memseting(1);

    for (auto i : adjLists[start])
        if (!visited[i])
            DFS_S(i, dest);
}

void Graph::DFS(int start, int dest)
{
    visited[start] = true;
    cout << start << " ";

    if (start == dest)
        memseting(1);

    for (int i = 0; i <= numVertices; i++)
        if ((adjMatrix[start][i] != 0) && (!visited[i]))
            DFS(i, dest);
}

int main()
{
    setlocale(0, "");
    srand(time(0));

    int z = 8;
    Graph c(z);

    for (int i = 0; i < z; i++)
    {
        for (int j = i + 1; j < z; j++)
        {
            if (bool(rand() % 2))
                c.addEdge(i, j);
        }
    }

    cout << "Матрица смежности" << endl;
    c.toMatrix();
    int start=0, dest=z-1;

    cout << endl << "Стартовая вершина > "; cin >> start;
    cout << endl << "Конечная вершина > "; cin >> dest;

    double time1, time2;

    cout << "Кратчайший Путь(BFS_список): " << endl;
    c.memseting(0);
    time1 = clock();
    c.BFS_S(start, dest);
    time2 = clock();
    cout << endl << "Время: " << (time2 - time1) / CLOCKS_PER_SEC;
    cout<<endl << endl << "Кратчайший Путь(BFS_матрица):" << endl;
    c.memseting(0);
    time1 = clock();
    c.BFS(start, dest);
    time2 = clock();
    cout << endl << "Время: " << (time2 - time1) / CLOCKS_PER_SEC;
    cout<<endl << endl << "Путь(DFS_список): " << endl;
    c.memseting(0);
    time1 = clock();
    c.DFS_S(start, dest);
    time2 = clock();
    cout << endl << "Время: " << (time2 - time1) / CLOCKS_PER_SEC;
    cout << endl << endl << "Путь(DFS_матрица):" << endl;
    c.memseting(0);
    time1 = clock();
    c.DFS(start, dest);
    time2 = clock();
    cout << endl << "Время: " << (time2 - time1) / CLOCKS_PER_SEC;

    return 0;
}

