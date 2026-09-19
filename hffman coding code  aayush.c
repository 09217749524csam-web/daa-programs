#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_HT 100

struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode **array;
};

struct MinHeapNode *newNode(char data, unsigned freq) {
    struct MinHeapNode *temp = malloc(sizeof(struct MinHeapNode));
    temp->data = data;
    temp->freq = freq;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct MinHeap *createMinHeap(unsigned capacity) {
    struct MinHeap *minHeap = malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = malloc(capacity * sizeof(struct MinHeapNode *));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b) {
    struct MinHeapNode *temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct MinHeap *minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < (int)minHeap->size &&
        minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < (int)minHeap->size &&
        minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

struct MinHeapNode *extractMin(struct MinHeap *minHeap) {
    struct MinHeapNode *temp = minHeap->array[0];

    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;

    if (minHeap->size > 0)
        minHeapify(minHeap, 0);

    return temp;
}

void insertMinHeap(struct MinHeap *minHeap,
                   struct MinHeapNode *node) {
    int i = minHeap->size;
    minHeap->size++;

    while (i > 0 &&
           node->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = node;
}

void buildMinHeap(struct MinHeap *minHeap) {
    if (minHeap->size <= 1)
        return;

    for (int i = (int)(minHeap->size / 2) - 1; i >= 0; i--)
        minHeapify(minHeap, i);
}

struct MinHeap *createAndBuildMinHeap(char data[],
                                      int freq[],
                                      int size) {
    struct MinHeap *minHeap = createMinHeap(size);

    for (int i = 0; i < size; i++)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

int isLeaf(struct MinHeapNode *root) {
    return root->left == NULL && root->right == NULL;
}

struct MinHeapNode *buildHuffmanTree(char data[],
                                     int freq[],
                                     int size) {
    struct MinHeap *minHeap;
    struct MinHeapNode *left;
    struct MinHeapNode *right;
    struct MinHeapNode *top;

    minHeap = createAndBuildMinHeap(data, freq, size);

    while (minHeap->size > 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

void printCodes(struct MinHeapNode *root, int arr[], int top) {
    if (root->left != NULL) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right != NULL) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (isLeaf(root)) {
        printf("%c : ", root->data);

        for (int i = 0; i < top; i++)
            printf("%d", arr[i]);

        printf("\n");
    }
}

void HuffmanCodes(char data[], int freq[], int size) {
    struct MinHeapNode *root;
    int arr[MAX_TREE_HT];

    root = buildHuffmanTree(data, freq, size);

    if (size == 1) {
        printf("%c : 0\n", data[0]);
        return;
    }

    printCodes(root, arr, 0);
}

int main() {
    int n;

    printf("Enter number of characters: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of characters.\n");
        return 1;
    }

    char data[n];
    int freq[n];

    printf("Enter characters:\n");
    for (int i = 0; i < n; i++)
        scanf(" %c", &data[i]);

    printf("Enter frequencies:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &freq[i]);

    printf("\nHuffman Codes:\n");
    HuffmanCodes(data, freq, n);

    return 0;
}
