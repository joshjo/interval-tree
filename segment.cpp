#include <cstdio>
#include <iostream>
#include <vector>

//Tipo de los puntos
#define Point int
//Representa +infinito
#define FLT_MAX 10000

using namespace std;


struct Segment
{
    Segment(Point minValue, Point maxValue) {
        this->minValue = minValue;
        this->maxValue = maxValue;
    }
    Point minValue;
    Point maxValue;
};


Segment ss[] = {
    Segment(750, 830),
    Segment(830, 860),
    Segment(520, 600),
    Segment(540, 550),
    Segment(530, 620),
    Segment(310, 360),
    Segment(300, 330),
    Segment(50, 120),
    Segment(90, 140),
    Segment(970, 980),
    Segment(950, 970),
    Segment(630, 1000),
};

//Nodos del árbol de segmento
struct BinaryTree
{
    BinaryTree() {
        leftChild = NULL;
        rightChild = NULL;
    }
    Point minValue;
    bool minOpen;
    Point maxValue;
    bool maxOpen;
    vector<Segment> subSet;
    BinaryTree *leftChild;
    BinaryTree *rightChild;
};

//Built methods

//Comparar dos puntos
//utilizados para ordenar la lista de puntos extremos
int cmp(const void *arg1, const void *arg2)
{
    Point value1 = *(Point *)arg1;
    Point value2 = *(Point *)arg2;
    if (value1 < value2)
        return -1;
    if (value1 > value2)
        return 1;
    return 0;
}

int getIndex(Segment segment) {
    int i = 0;
    while(true) {
        if (ss[i].minValue == segment.minValue && ss[i].maxValue == segment.maxValue) {
            return i + 1;
        }
        i += 1;
        if (i > 100) break;
    }
    return -1;
}

void printTree(BinaryTree * tree, string preppend, int level, string side = "") {
    if (tree == NULL) {
        return;
    }
    cout << preppend + side + to_string(level) + " " << "[" << tree->minValue << ", ";
    cout << tree->maxValue << "]" << " --> ";
    cout << "subset: ";
    if ( ! tree->subSet.size()) {
        cout << "------";
    }
    for (int i = 0; i < tree->subSet.size(); i += 1) {
        cout << "S" << to_string(getIndex(tree->subSet[i])) << ", ";
    }
    cout << endl;
    preppend += "\t";
    printTree(tree->leftChild, preppend, level - 1, "L");
    printTree(tree->rightChild, preppend, level - 1, "R");
}

inline BinaryTree* Union(BinaryTree* nodeMin, BinaryTree* nodeMax)
{
    BinaryTree* result = new BinaryTree();
    result->minValue = nodeMin->minValue;
    result->minOpen = nodeMin->minOpen;
    result->maxValue = nodeMax->maxValue;
    result->maxOpen = nodeMax->maxOpen;
    return result;
}

inline BinaryTree* CreateLeafNode(Point minValue, Point maxValue, bool minOpen, bool maxOpen)
{
    BinaryTree* newNode = new BinaryTree();
    newNode->minOpen = minOpen;
    newNode->maxOpen = maxOpen;
    newNode->minValue = minValue;
    newNode->maxValue = maxValue;
    newNode->leftChild = 0;
    newNode->rightChild = 0;
    newNode->subSet = vector<Segment>();
    return newNode;
}

BinaryTree* BuiltBalancedBinaryTree(Point endPoints[], int countEndPoint)
{
        BinaryTree* elementaryInterval[countEndPoint * 2 + 1];
        Point minValue = -FLT_MAX;
        for(int i = 0; i < countEndPoint; i++)
        {
            int towI = 2 * i;
            elementaryInterval[towI] = CreateLeafNode(minValue, endPoints[i], true, true);
            elementaryInterval[towI + 1] = CreateLeafNode(endPoints[i], endPoints[i], false, false);
            minValue = endPoints[i];
        }
        int countNodes = countEndPoint * 2 + 1;
        elementaryInterval[countNodes - 1] = CreateLeafNode(endPoints[countEndPoint - 1], FLT_MAX, true, true);
        while (countNodes > 1)
        {
            for(int i = 0; i < countNodes / 2; i++)
            {
                int towI = 2 * i;
                BinaryTree *newNode = Union(elementaryInterval[towI], elementaryInterval[towI + 1]);
                newNode->leftChild = elementaryInterval[towI];
                newNode->rightChild = elementaryInterval[towI + 1];
                newNode->subSet = vector<Segment>();
                elementaryInterval[i] = newNode;
            }
            if (countNodes % 2)
            {
                elementaryInterval[countNodes / 2] = elementaryInterval[countNodes - 1];
            }
            countNodes = countNodes / 2 + (countNodes % 2);
        }
        return elementaryInterval[0];
}

inline bool ContainsIntNode(Segment segment, BinaryTree *tree)
{
    return tree->minValue >= segment.minValue & tree->maxValue <= segment.maxValue;
}

inline bool IntersectIntNode(Segment segment, BinaryTree *tree)
{
     return (segment.minValue < tree->maxValue | (segment.minValue == tree->maxValue & !tree->maxOpen))
        & (segment.maxValue > tree->minValue | (segment.maxValue == tree->minValue & !tree->minOpen));
}

void InsertSegment(Segment segment, BinaryTree *tree)
{
    if (ContainsIntNode(segment, tree))
    {
        tree->subSet.push_back(segment);
        return;
    }
    //Si es nodo hoja
    if (!tree->leftChild)
        return;
    if (IntersectIntNode(segment, tree->leftChild))
        InsertSegment(segment, tree->leftChild);
    if (IntersectIntNode(segment, tree->rightChild))
        InsertSegment(segment, tree->rightChild);
}

void DeleteEqualPoint(Point *endPoint, int *countEndPoint)
{
    int count = *countEndPoint;
    int index = 0;
    int i = 0;
    while (i < count)
    {
        endPoint[index] = endPoint[i];
        while (i < count && endPoint[index] == endPoint[i])
            i++;
        index++;
    }
    *countEndPoint = index;
}

//Crea el árbol de segmento a partir del conjunto de segmentos
BinaryTree* BuiltTree(Segment segments[], int segmentCount)
{
    int countEndPoint = segmentCount * 2;
    Point *endPoints = new Point[countEndPoint];
    for(int i = 0; i < segmentCount; i++)
    {
        int towI = 2 * i;
        endPoints[towI] = segments[i].maxValue;
        endPoints[towI + 1] = segments[i].minValue;
    }
    qsort(endPoints, countEndPoint, sizeof(Point), cmp);
    DeleteEqualPoint(endPoints, &countEndPoint);
    BinaryTree *tree = BuiltBalancedBinaryTree(endPoints, countEndPoint);
    delete [] endPoints;
    for (int i = 0; i < segmentCount; i++)
        InsertSegment(segments[i], tree);
    return tree;
}

//Libera la memoria ocupada por el árbol construido
void DeleteTree(BinaryTree *tree)
{
    if (tree->leftChild != 0)
        DeleteTree(tree->leftChild);
    if (tree->rightChild != 0)
        DeleteTree(tree->rightChild);
    delete tree;
}

int main() {
    BinaryTree * tree = BuiltTree(ss, 12);
    // cout << "Hellowww" << endl;
    printTree(tree, "", 7);
    // cout << tree->subSet.size() << endl;
    // cout << "hola" << endl;
    return 0;
}
