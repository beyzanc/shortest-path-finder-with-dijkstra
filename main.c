#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int isFileRead;
int adjacencyMatrix[26][26];
int isExists[26];
int dist[26];
int parentArr[26];

/* Min Heap */
struct Node
{
    int city;
    int distance;
};

struct MinHeap
{
    struct Node *internalArray;
    int capacity;
    int currentSize;
};

void initializeMinHeap(struct MinHeap *minHeap, int capacity)
{
    minHeap->internalArray = (struct Node*) malloc(capacity*sizeof(struct Node));
    minHeap->capacity = capacity;
    minHeap->currentSize = 0;
}

void swapMinHeapNodes(struct Node *x, struct Node *y)
{
    int tmpCity = x->city;
    int tmpDistance = x->distance;

    x->city = y->city;
    x->distance = y->distance;

    y->city = tmpCity;
    y->distance = tmpDistance;
}

int parentOfHeapNode(int i)
{ 
    return (i-1) / 2; 
}

int leftChildOfHeapNode(int i) 
{ 
    return (2*i + 1); 
}

int rightChildOfHeapNode(int i) 
{ 
    return (2*i + 2); 
}

struct Node getMinElementFromMinHeap(struct MinHeap *minHeap)
{ 
    return minHeap->internalArray[0]; 
}

void insertElementToMinHeap(struct MinHeap *minHeap, struct Node element)
{
    // If the capacity of min heap is not full
    if(minHeap->currentSize < minHeap->capacity)
    {
        // Insert the new element to the end of heap
        minHeap->currentSize++;
        int i = minHeap->currentSize - 1;
        minHeap->internalArray[i] = element;
    
        // To preserve min heap strucuture, move up the new element as required
        while (i != 0 && minHeap->internalArray[parentOfHeapNode(i)].distance > minHeap->internalArray[i].distance)
        {
            swapMinHeapNodes(&minHeap->internalArray[i], &minHeap->internalArray[parentOfHeapNode(i)]);
            i = parentOfHeapNode(i);
        }
    }
}

void heapify(struct MinHeap *minHeap, int i)
{
    int l = leftChildOfHeapNode(i);
    int r = rightChildOfHeapNode(i);

    int smallest = i;
    
    // If the left element is less than current element
    if(l < minHeap->currentSize && minHeap->internalArray[l].distance < minHeap->internalArray[i].distance)
    {
        smallest = l;
    }

    // If the right element is less than both current and left element
    if(r < minHeap->currentSize && minHeap->internalArray[r].distance < minHeap->internalArray[smallest].distance)
    {
        smallest = r;
    }

    // If the smallest one is not current element(left or right)
    if(smallest != i)
    {
        // Change current element with the smallest child and to preserve min heap strucutre
        // call heapify method for the changed node
        swapMinHeapNodes(&minHeap->internalArray[i], &minHeap->internalArray[smallest]);
        heapify(minHeap, smallest);
    }
}

void extractMinElementFromMinHeap(struct MinHeap *minHeap)
{
    // If the min heap is not empty
    if(minHeap->currentSize > 0)
    {
        if(minHeap->currentSize == 1)
        {
            minHeap->currentSize--;
            return;
        }

        // Move to last element to the root instead of the extracted element
        minHeap->internalArray[0] = minHeap->internalArray[minHeap->currentSize-1];
        minHeap->currentSize--;
        
        // To preserve min heap structure, call heapify method for root
        heapify(minHeap, 0);
    }
}

/* Min Heap */

void readInputFile()
{
    /* Initialize matrix and existence list */
    int i, j;
    for(i=0;i<26;i++)
    {
        isExists[i] = 0;
    }
    for(i=0;i<26;i++)
    {
        for(j=0;j<26;j++)
        {
            adjacencyMatrix[i][j] = -1;
        }
    }

    // Get the file name from user
    char fileName[256];
    printf("Enter the file name: ");
    scanf("%s", fileName);

    char first, second, tmp;
    int firstIndex, secondIndex, intensity;

    FILE* inputFile = fopen(fileName, "r");

    // Read information from the input file
    while(fscanf(inputFile, " %c%c%c%c%d", &first, &tmp, &second, &tmp, &intensity) == 5)
    {
        firstIndex = first - 'A';
        secondIndex = second - 'A';
        isExists[firstIndex] = isExists[secondIndex] = 1;
        adjacencyMatrix[firstIndex][secondIndex] = adjacencyMatrix[secondIndex][firstIndex] = intensity;
    }
	
    fclose(inputFile);
    
    // Set isFileRead, since after now the adjaceny matrix is filled and showAdjacencyMatrix and 
    // shortestPath methods can be called.
    isFileRead=1;
    printf("%s successfully read!\n", fileName);
}

void showAdjacencyMatrix()
{
	int i, j;
    if(isFileRead == 0)
    {
        printf("First read an input file!\n");
        return;
    }    

    printf("Adjacency Matrix:\n\n\t");

    for(i=0;i<26;i++)
    {
        if(isExists[i])
        {
            printf("   %c\t", i+'A');
        }
    }

    printf("\n");
    for(i=0;i<26;i++)
    {
        if(isExists[i])
        {
            printf("%c\t", i+'A');                
            for(j=0;j<26;j++)
            {
                if(isExists[j])
                {
                    // If there is no path between i and j
                    if(adjacencyMatrix[i][j] == -1)
                    {
                        printf("   -\t");
                    }
                    else
                    {
                        printf("%4d\t", adjacencyMatrix[i][j]);
                    }
                }
            }
            printf("\n");
        }
    }
}

int showMenuAndGetChoice()
{
    int choice;
    int okay = 0;

    // Get choice from the user until he/she enters a valid choice
    while(okay == 0)
    {
        printf("\n\nMenu\n");
        printf("-----------------------------------------------------\n");
        printf("1 - Read File\n");
        printf("2 - Show Adjacency Matrix\n");
        printf("3 - Find Shortest Path\n");
        printf("4 - Exit\n");
        printf("\nEnter your choice: ");

        scanf("%d", &choice);

        if(1 <= choice && choice <= 4)
        {
            okay = 1;
        }
        else
        {
            printf("\nWrong choice! Please enter again.");
        }
    }

    printf("\n");

    return choice;
}

void printPath(int j)
{
    if(parentArr[j] != - 1)
    {
        printPath(parentArr[j]);
        printf("-> %c ", 'A'+j);
    }
}

void shortestPath()
{
	int i;
    if(isFileRead == 0)
    {
        printf("First read an input file!\n");
        return;
    }

    // Get source and destination cities from the user
    char sourceChar, destinationChar;
    printf("Enter the source vertex: ");
    scanf(" %c", &sourceChar);
    printf("Enter the destination vertex: ");
    scanf(" %c", &destinationChar);

    // Since we use 0-indexed indices, convert chars to integers
    int source = sourceChar - 'A';
    int destination = destinationChar - 'A'; 

    // Crete and initialize the min heap that will be used for calculating the shortest path
    struct MinHeap* myHeap = (struct MinHeap*) malloc(sizeof(struct MinHeap));
    initializeMinHeap(myHeap, 26);
    
    for(i=0;i<26;i++)
    {
        dist[i] = INT_MAX;
    }

    // Insert the source node min heap
    parentArr[source] = -1;
    dist[source] = 0;
    struct Node sourceNode;
    sourceNode.city = source;
    sourceNode.distance = 0;
    insertElementToMinHeap(myHeap, sourceNode);

    // While the min heap is not empty
    while(myHeap->currentSize > 0)
    {
        int currCity = getMinElementFromMinHeap(myHeap).city;
        extractMinElementFromMinHeap(myHeap);

        for(i=0;i<26;i++)
        {
            //If there is a path to that city
            if(i != currCity && adjacencyMatrix[currCity][i] != -1)
            {
                int weight = adjacencyMatrix[currCity][i];
                // If there is a shorter path to i with currCity
                if(dist[i] > dist[currCity] + weight)
                {
                    dist[i] = dist[currCity] + weight;
                    parentArr[i] = currCity;
                    
                    // Insert i to the min heap with updated distance
                    struct Node newNode;
                    newNode.city = i;
                    newNode.distance = dist[i];
                    insertElementToMinHeap(myHeap, newNode);
                }
            }
        }
    }
    
    if(dist[destination] == INT_MAX)
    {
        printf("\nThere is no path from %c to %c\n", sourceChar, destinationChar);
    }
    else
    {
        // Print the shortest path: source to destination
        printf("\nThe shortest path from %c to %c: ", sourceChar, destinationChar);

        printf("%c ", sourceChar);
        printPath(destination);
        
        printf("\nThe length of this path: %d\n", dist[destination]);
    }

    // Deallocate the memory used for min heap
    free(myHeap->internalArray);
    free(myHeap);
}

int main()
{
    isFileRead = 0;
    int userExited = 0;
    
    // Until user wants to exit, continuously ask for choice
    while(userExited == 0)
    {
        int choice = showMenuAndGetChoice();

        if(choice == 1)
        {
            readInputFile();
        }
        else if(choice == 2)
        {
            showAdjacencyMatrix();
        }
        else if(choice == 3)
        {
            shortestPath();
        }
        else if(choice == 4)
        {
            userExited = 1;
            printf("Good bye!\n\n");
        }                                 
    }

    return 0;
}
