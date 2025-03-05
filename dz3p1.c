#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
typedef struct node{
    float x;
    float y;
    float r;
    int data;
    struct node* next;
}Node;
typedef struct graph{
    int brMina;
    Node** liste;
}Graph;
//kreiranje praznog grafa
Graph * createGraph(int brMina)
{
    Graph * graf=malloc(sizeof(Graph));
    if(graf==NULL)
        exit(0);
    graf->brMina=brMina;
    graf->liste=(Node**)malloc(brMina*sizeof(Node*));
    if(graf->liste==NULL)
        exit(0);
    int i;
    for (i = 0; i < brMina; ++i) {
        graf->liste[i]=NULL;
    }
    return graf;
}
//dodavanje cvora u graf
int addVertex(Graph*graph,float x1, float y1, float r1, int br)
{
    Node*tmp=graph->liste[0];
    while(tmp){
        if(tmp->x==x1 && tmp->y==y1 && tmp->r==r1)
        {
            printf("Cvor je vec u grafu.\n");
            return 0;
        }
        tmp=tmp->next;
    }
    Node* novi=(Node*)malloc(sizeof(Node));
    if(novi==NULL)
        exit(0);
    novi->x=x1;
    novi->y=y1;
    novi->r=r1;
    novi->data=br+1;
    novi->next=NULL;
    graph->liste[br]=novi;
    return 1;
}
//uklanjanje cvora iz grafa
void removeVertex(Graph* graph, int br, int n) {
    int i;
    Node *currentNode = graph->liste[br]->next;
    while (currentNode != NULL) {
        Node *temp = currentNode;
        free(temp);
        currentNode = currentNode->next;
    }
    graph->liste[br] = NULL;
    for (i = 0; i < n; i++) {
        if (i != br && graph->liste[i]!=NULL) {
            Node *curr = graph->liste[i]->next;
            Node *prev = graph->liste[i];

            while (curr != NULL) {
                if (curr->data == br + 1) {
                    prev->next = curr->next;
                    Node *temp = curr;
                    free(temp);
                    break;
                }
                prev = curr;
                curr = curr->next;
            }
        }
    }
}
//dodavanje grane izmedju dva cvora tj usmerene grane: ako vert1 detonira vert2
//u ovoj reprezentaciji; dodavanje elementa sa indeksom vertexIndex2 na kraj ulancane liste elementa sa indeksom vertexIndex1
void addEdge(Graph* graph, int vertexIndex1, int vertexIndex2) {
    Node* newNode = malloc(sizeof(Node));
    if(newNode==NULL)
        exit(0);
    Node* temp=graph->liste[vertexIndex2];
    newNode->data=temp->data;
    newNode->x=temp->x;
    newNode->y=temp->y;
    newNode->r=temp->r;
    newNode->next=NULL;
    Node*curr=graph->liste[vertexIndex1];
    while(curr->next!=NULL) {
        curr = curr->next;
        if(curr->data==newNode->data)
        {
            printf("Vec postoji grana.\n");
            return;
        }
    }
    curr->next = newNode;
}
//brisanje grane u ulancanoj listi cvora sa indeksom vertexIndex1
void removeEdge(Graph* graph, int vertexIndex1, int vertexIndex2) {
    if(graph->liste[vertexIndex1]->next==NULL)
    {
        printf("Zadata grana ne postoji.\n");
        return;
    }
    Node* currentNode = graph->liste[vertexIndex1]->next;
    Node* prevNode = graph->liste[vertexIndex1];

    while (currentNode != NULL) {
        if (currentNode->data == vertexIndex2+1) {
                prevNode->next = currentNode->next;
                Node*temp=currentNode;
                free(temp);
                break;
            }
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
}
//brisanje grafa
void deleteGraph(Graph* graph) {
    int i;
    for (i = 0; i < graph->brMina; i++) {
        Node* currentNode = graph->liste[i];
        while (currentNode != NULL) {
            Node* nextNode = currentNode->next;
            free(currentNode);
            currentNode = nextNode;
        }
    }
    free(graph->liste);
    free(graph);
}
//ispis reprezentacije grafa
void printGraph(Graph* graph) {
    int i;
    for (i = 0; i < graph->brMina; i++) {
        Node* currentNode = graph->liste[i];
        if(currentNode!=NULL) {
            printf("Mina %d (x=%.2f, y=%.2f, r=%.2f):", currentNode->data, currentNode->x, currentNode->y,
                   currentNode->r);
            currentNode = currentNode->next;
            while (currentNode) {
                printf(" -> %d (x=%.2f, y=%.2f, r=%.2f)", currentNode->data, currentNode->x, currentNode->y,
                       currentNode->r);
                currentNode = currentNode->next;
            }
            printf("\n");
        }
    }
}
int findVertex(Graph *graph, float x, float y, float r, int n){
    int i;
    for(i=0;i<n;i++) {
        if (graph->liste[i] != NULL) {
            if (graph->liste[i]->x == x && graph->liste[i]->y == y && graph->liste[i]->r == r) {
                return graph->liste[i]->data;
            }
        }
    }
    return 0;
}

void update(Graph *graph, int n){
    int i;
    for (i = 0; i < n-1; ++i) {
        if(graph->liste[i]==NULL)
        {
            graph->liste[i]=graph->liste[i+1];
            Node* curr=graph->liste[i];
            while(curr!=NULL)
            {
                if(curr->data>i+1)
                    curr->data--;
                curr=curr->next;
            }
            graph->liste[i+1]=NULL;
        }
    }
}
int detonira(Node *a, Node*b){
    double rast= sqrt(pow(a->x-b->x,2)+pow(a->y-b->y,2));
    if(rast<=a->r)
        return 1;
    return 0;
}
int nijePovezano(Graph*graph, int ind1, int ind2) {
    Node*curr=graph->liste[ind1]->next;
    while(curr!=NULL){
        if(curr->data-1==ind2)
            return 0;
        curr=curr->next;
    }
    return 1;
}
void BFS(Graph * graph, int startIndex)
{
    int i;
    int *visited = (int *)malloc(graph->brMina * sizeof(int));
    for (i = 0; i < graph->brMina; i++) {
        visited[i] = 0;
    }
    int *queue = (int *)malloc(graph->brMina * sizeof(int));
    int front = 0;
    int rear = 0;
    visited[startIndex] = 1;
    queue[rear] =startIndex;
    while (front <= rear) {
        int currentVertexIndex = queue[front++];
        Node* currentNode = graph->liste[currentVertexIndex];
        if(currentVertexIndex!=startIndex && nijePovezano(graph,startIndex,currentVertexIndex))
            addEdge(graph,startIndex,currentVertexIndex);
        Node* neighborNode = currentNode->next;
        while (neighborNode != NULL) {
            int neighborVertexIndex = neighborNode->data - 1;
            if (!visited[neighborVertexIndex]) {
                visited[neighborVertexIndex] = 1;
                queue[++rear] = neighborVertexIndex;
            }
            neighborNode = neighborNode->next;
        }
    }

    free(visited);
    free(queue);

}
Node* findMax(Graph* graph, int n)
{
    int maks=0;
    int br=0;
    Node*curr;
    Node*maksMina;
    int i;
    for(i=0;i<n;i++){
        curr=graph->liste[i]->next;
        while(curr){
            br++;
            curr=curr->next;
        }
        if(br>maks) {
            maks = br;
            maksMina=graph->liste[i];
        }
        br=0;
    }
    return maksMina;
}
int isInsideCircle(double x, double y, Node* circle) {
    double distance = sqrt(pow(x - circle->x, 2) + pow(y - circle->y, 2));
    return distance <= circle->r;
}
double findMaxDetSurface(Graph *graph, Node*mina){
    int numPoints= 1000000;
    int numInside = 0; // Counter for points inside the union area
    double minX = mina->x;
    double maxX =mina->x;
    Node*curr=mina;
    srand((unsigned int)time(NULL));
    while(curr!=NULL) {
        if (curr->x - curr->r < minX) {
            minX = curr->x - curr->r;
        }
        if ( curr->x + curr->r > maxX) {
            maxX = curr->x +curr->r ;
        }
        curr=curr->next;
    }
    curr=mina;
    double minY=mina->y;
    double maxY=mina->y;
    while(curr!=NULL) {
        if (curr->y - curr->r < minY) {
            minY = curr->y - curr->r;
        }
        if ( curr->y + curr->r > maxY) {
            maxY = curr->y +curr->r ;
        }
        curr=curr->next;
    }
    int i;
    for ( i = 0; i < numPoints; i++) {
        double x = minX + ((double)rand() / RAND_MAX) * (maxX - minX);
        double y = minY + ((double)rand() / RAND_MAX) * (maxY - minY);

        int isInside = 0;
        Node *tmp = mina;
        while (tmp) {
            if (isInsideCircle(x, y, tmp)) {
                isInside = 1;
                break;
            }
            tmp = tmp->next;
        }

        if (isInside) {
            numInside++;
        }
    }
    double probability = (double)numInside / numPoints;
    double boundingBoxArea = (maxX - minX) * (maxY - minY);
    double unionArea = probability * boundingBoxArea;

    return unionArea;
}

int findEficiency(Graph*graph,int br){
    Node*tmp=graph->liste[br]->next;
    int b=0;
    while(tmp){
        b++;
        tmp=tmp->next;
    }
    return b;
}

int main() {
    const char *filePath;
    int brMina, br;
    int numNodes;
    Graph *graph;
    printf("%s\n", "----------GLAVNI MENI---------");
    printf("Unesite opciju\n1.kreiranje grafa gde su cvorovi mine od tri polja\n2.igra \"Detonacija mina\"\n");
    int op;
    scanf("%d", &op);
    if (op == 1) {
        printf("Unesite broj cvorova grafa: \n");
        scanf("%d", &numNodes);
        graph = createGraph(numNodes);
        int choice;
        br = 0;
        while (1) {
            printf("\nIzaberite opciju:\n");
            printf("1. Dodaj cvor\n");
            printf("2. Ukloni cvor\n");
            printf("3. Dodaj granu\n");
            printf("4. Ukloni granu\n");
            printf("5. Ispisi graf (reprezentacija-lista susednosti)\n");
            printf("6. Obrisi graf iz memorije/izlaz iz programa\n");
            printf("Unesite broj opcije: \n");
            scanf("%d", &choice);
            float x, y, r;
            switch (choice) {
                case 1:
                    if (br < numNodes) {
                        printf("Unesite koordinate (x, y, r) cvora koji zelite da dodate u graf: \n");
                        scanf("%f%f%f", &x, &y, &r);
                        int k=addVertex(graph, x, y, r, br);
                        if(k==1) {
                            printf("Cvor %d je dodat u graf.\n", br + 1);
                            br++;
                        }
                    } else {
                        printf("Graf zadate dimenzije je pun.\n");
                    }
                    break;
                case 2:
                    printf("Unesite koordinate (x, y, r) cvora koji zelite da uklonite iz grafa: \n");
                    scanf("%f%f%f", &x, &y, &r);
                    int br1 = findVertex(graph, x, y, r, numNodes);
                    //printf("%d\n", br1);
                    if (br1 == 0) printf("%s\n", "Zeljeni cvor nije u grafu.");
                    else {
                        removeVertex(graph, br1 - 1, numNodes);
                        printf("Cvor je %d uklonjen iz grafa.\n", br1);
                        br--;
                    }
                    update(graph, numNodes);
                    break;

                case 3:
                    printf("Unesite koordinate (x, y, r) polaznog cvora: \n");
                    scanf("%f%f%f", &x, &y, &r);
                    int br11 = findVertex(graph, x, y, r, numNodes);
                    if (br11 == 0) {
                        printf("Cvor nije u grafu.\n");
                        break;
                    }
                    printf("Unesite koordinate (x, y, r) odredisnog cvora: \n");
                    scanf("%f%f%f", &x, &y, &r);
                    int br2 = findVertex(graph, x, y, r, numNodes);
                    if (br2 == 0) {
                        printf("Cvor nije u grafu.\n");
                        break;
                    }
                    addEdge(graph, br11 - 1, br2 - 1);
                    printf("Grana je dodata izmedju cvora %d i %d.\n", br11, br2);
                    break;

                case 4:
                    printf("Unesite koordinate (x, y, r) polaznog cvora: \n");
                    scanf("%f%f%f", &x, &y, &r);
                    br1 = findVertex(graph, x, y, r, numNodes);
                    if (br1 == 0) {
                        printf("Cvor nije u grafu.\n");
                        break;
                    }
                    printf("Unesite koordinate (x, y, r) odredisnog cvora: \n");
                    scanf("%f%f%f", &x, &y, &r);
                    br2 = findVertex(graph, x, y, r, numNodes);
                    if (br2 == 0) {
                        printf("Cvor nije u grafu.\n");
                        break;
                    }
                    removeEdge(graph, br1 - 1, br2 - 1);
                    printf("Grana je obrisana izmedju cvorova %d i %d.\n", br1, br2);
                    break;

                case 5:
                    printGraph(graph);
                    break;

                case 6:
                    deleteGraph(graph);
                    printf("Graf je obrisan iz memorije. Kraj programa\n");
                    exit(0);

                default:
                    printf("Nevazeca opcija. Molimo pokusajte ponovo.\n");
            }
        }
    }
    else if (op == 2) {
        filePath = "C:\\Users\\Korisnik\\OneDrive\\Desktop\\graf1.txt";
        FILE *inputFile = fopen(filePath, "r");
        if (inputFile == NULL) {
            printf("GRESKA\n");
            return 0;
        }
        fscanf(inputFile, "%d", &brMina);
        graph = createGraph(brMina);
        int i;
        br = 0;
        for (i = 0; i < brMina; i++) {
            float x, y, r;
            fscanf(inputFile, "%f %f %f", &x, &y, &r);
            int k=addVertex(graph, x, y, r, br);
            br++;
        }
        int j;
        for (i = 0; i < brMina; i++) {
            for (j = 0; j < brMina; ++j) {
                if (i != j) {
                    if (detonira(graph->liste[i], graph->liste[j])) {
                        addEdge(graph, i, j);
                    }
                }
            }
        }
        int l;
        for(l=0;l<brMina;l++){
            BFS(graph,l);
        }
        printf("Graf je kreiran.\n");
        printGraph(graph);
        Node *maksmina = findMax(graph, brMina);
        printf("\nMina maksimalne efikasnosti je mina %d (x=%.2f, y=%.2f, r=%.2f)\n", maksmina->data, maksmina->x,
               maksmina->y, maksmina->r);
        printf("Mine koje ona detonira su: \n\n");
        Node *curr = maksmina->next;
        while (curr != NULL) {
            printf("Mina %d (x=%.2f, y=%.2f, r=%.2f)\n", curr->data, curr->x, curr->y, curr->r);
            curr = curr->next;
        }
        double maksExp = findMaxDetSurface(graph, maksmina);
        printf("\nPovrsina detonacije mine maksimalne efikasnosti je %.2f\n", maksExp);
        while (1) {
            printf("\n--------MENI-------\n");
            printf("Izaberite opciju:\n1.Efikasnost zadate mine\n2.Eksploziju zadate rakete\n3.kraj programa\n");
            int op1;
            scanf("%d", &op1);
            float x, y, r;
            if (op1 == 1) {
                printf("\nUnesite koordinate (x, y, r) mine ciju efikasnost zelite da odredite:\n");
                scanf("%f%f%f", &x, &y, &r);
                int b = findVertex(graph, x, y, r, brMina);
                if (b == 0) {
                    printf("Mina nije u grafu\n");
                } else {
                    int k = findEficiency(graph, b - 1);
                    Node *mina = graph->liste[b - 1];
                    printf("Efikasnost zadate mine je %d\n", k);
                    printf("Mine koje ona detonira su:\n\n");
                    Node *curr1 = mina->next;
                    while (curr1 != NULL) {
                        printf("Mina %d (x=%.2f, y=%.2f, r=%.2f)\n", curr1->data, curr1->x, curr1->y, curr1->r);
                        curr1 = curr1->next;
                    }
                }
            }
            else if (op1 == 2) {
                printf("\nUnesite koordinate rakete i njen radijus:\n");
                float xr,yr,rr;
                scanf("%f%f%f",&xr,&yr,&rr);
                Graph *g1= createGraph(brMina+1);
                int t;
                for(t=0;t<brMina;t++)
                {
                    //printf("Sofija");
                    addVertex(g1,graph->liste[t]->x,graph->liste[t]->y,graph->liste[t]->r,t);
                }
                //printf("Sofija");
                addVertex(g1,xr,yr,rr,brMina);
                printf("\nAko dodamo raketu u graf, sada graf izgleda ovako:\n");
                for (i = 0; i < brMina+1; i++) {
                    for (j = 0; j < brMina+1; ++j) {
                        if (i != j) {
                            if (detonira(g1->liste[i], g1->liste[j])) {
                                addEdge(g1, i, j);
                            }
                        }
                    }
                }
                for(t=0;t<brMina+1;t++)
                {
                    BFS(g1,t);
                }
                printGraph(g1);
                int k= findEficiency(g1, brMina);
                printf("\nEfikasnost rakete je %d.\n",k);
                printf("Mine koje ona detonira su:\n\n");
                Node *curr1 = g1->liste[brMina]->next;
                while (curr1 != NULL) {
                    printf("Mina %d (x=%.2f, y=%.2f, r=%.2f)\n", curr1->data, curr1->x, curr1->y, curr1->r);
                    curr1 = curr1->next;
                }
                deleteGraph(g1);
            }
            else if (op1 == 3) {
                printf("Kraj programa.\n");
                deleteGraph(graph);
                return 0;
            }
            else {
                printf("Nevalidna opcija. Kraj igre.");
                deleteGraph(graph);
                return 0;
            }

        }
        fclose(inputFile);
    }
    else {
        printf("%s", "Niste izabrali ispravnu opciju!");
        return 0;
    }
    return 0;
}