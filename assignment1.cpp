#include <iostream>
using namespace std;

// ============================================================================
// Q1 - ARRAYS AND SEARCHING (10 Marks)
// ============================================================================

// THEORY ANSWERS - Q1.A
/*
Q1.A.1 - Contiguous Memory Allocation:
Contiguous memory allocation means that all array elements are stored in adjacent memory
locations. Arrays use this because it allows fast random access. By knowing the base address
and element size, any element can be accessed directly using: address = base + (index * element_size).
This provides O(1) access time regardless of array size.

Q1.A.2 - Memory Leak:
A memory leak occurs when dynamically allocated memory is not freed after use.
Realistic scenario: int* arr = new int[100]; is created but never deleted. If this line is
inside a function that's called multiple times, or if an exception occurs before delete,
the memory remains allocated forever, consuming system resources.

Q1.A.3 - Fixed-size vs Dynamic Arrays:
Fixed-size (static) arrays have their size determined at compile time and are allocated on
the stack. Dynamic arrays have their size determined at runtime and are allocated on the heap.
Fixed size matters because: (1) Stack space is limited, so large fixed arrays crash, (2) We
often don't know needed size until runtime, (3) Fixed arrays waste space if we don't use all of it.

Q1.A.4 - O(1) Array Access:
Array access is O(1) because arrays store elements in contiguous memory. To access arr[i],
the CPU computes: memory_address = base_address + (i * sizeof(element)) in a single step,
regardless of array size. Linked lists are O(n) because nodes are scattered in memory;
to reach index i, we must traverse i nodes sequentially.
*/

// Q1.B.1:
int linearSearch(int arr[], int size, int key) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

// Q1.B.2:
void findMinMax(int arr[], int size, int &minVal, int &maxVal) {
    //if (size <= 0) return;
    
    minVal = arr[0];
    maxVal = arr[0];
    
    for (int i = 1; i < size; i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        } else if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
}

int main() {
    int arr[10] = {4, 15, 7, 23, 1, 9, 42, 18, 6, 30};
    int size = 10;
    
    int searchKey = 42;
    
    cout << "--- Q1: Arrays and Searching ---" << endl;
    
    int index = linearSearch(arr, size, searchKey);
    if (index != -1) {
        cout << "Linear Search: Value " << searchKey << " found at index " << index << "." << endl;
    } else {
        cout << "Linear Search: Value " << searchKey << " not found." << endl;
    }
    
    int minVal, maxVal;
    findMinMax(arr, size, minVal, maxVal);
    
    cout << "Min/Max Search: Minimum value is " << minVal << " and Maximum value is " << maxVal << ".\n" << endl;

    return 0;
}

// ============================================================================
// Q2 - BUBBLE SORT (10 Marks) - SELF LEARNING
// ============================================================================

// THEORY ANSWERS - Q2.A
/*
Q2.A.1 - How Bubble Sort Works:
Bubble Sort repeatedly steps through the list, compares adjacent elements, and swaps them
if they are in the wrong order. In each pass, the largest unsorted element "bubbles" to its
correct position at the end. After n-1 passes, all elements are sorted. It's called "Bubble"
because larger elements gradually move to the end, like bubbles rising to the surface.

Q2.A.2 - Time Complexity of Bubble Sort:
Best case: O(n) - when array is already sorted with optimization flag (early exit)
Average case: O(n²) - random order requires many swaps and comparisons
Worst case: O(n²) - when array is reverse sorted, every element must be compared to every other
With optimization flag checking if no swaps occur in a pass, the algorithm exits early if the
array becomes sorted before all passes complete.

Q2.A.3 - Bubble Sort vs Selection Sort:
Selection Sort is generally preferred over Bubble Sort because:
- Selection Sort has fewer actual swaps (at most n-1 swaps vs up to n²/2 swaps in Bubble Sort)
- Both have O(n²) time complexity, but Selection Sort has better practical performance
Scenario for Bubble Sort: Use when array is known to be nearly sorted, as optimization flag
makes it O(n) in best case. Use Selection Sort for unsorted data or when memory writes are expensive.
*/

// BUBBLE SORT WITH OPTIMIZATION - Q2.B.1 & Q2.B.2
void bubbleSort(int arr[], int size, int& swapCount) {
    swapCount = 0;
    
    // Print initial array
    cout << "\nInitial array: ";
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
    
    // Outer loop for passes
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;  // Optimization flag
        
        // Inner loop for comparisons
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapCount++;
                swapped = true;
            }
        }
        
        // Print array after each pass
        cout << "After pass " << (i + 1) << ": ";
        for (int k = 0; k < size; k++) cout << arr[k] << " ";
        cout << endl;
        
        // If no swaps occurred, array is sorted
        if (!swapped) {
            cout << "Array sorted early at pass " << (i + 1) << "!" << endl;
            break;
        }
    }
}

// ============================================================================
// Q3 - BINARY SEARCH ALGORITHM (10 Marks)
// ============================================================================

// THEORY ANSWERS - Q3.A
/*
Q3.A.1 - Prerequisite for Binary Search:
The array MUST be sorted in ascending (or descending) order. This is critical because
Binary Search relies on eliminating half of the remaining elements by comparing the middle
element with the key. If the array is unsorted, the comparison logic breaks and returns
incorrect results or fails to find elements that exist.

Q3.A.2 - Dry-run of Binary Search on {2, 5, 8, 12, 16, 23, 38, 45} with key = 23:
Step 1: low=0, high=7, mid=3, arr[3]=12 < 23, so low=4
Step 2: low=4, high=7, mid=5, arr[5]=23 == 23, FOUND at index 5
Result: Element 23 found at index 5

Q3.A.3 - Binary Search vs Linear Search:
Binary Search: O(log n)
Linear Search: O(n)
Intuition: Binary Search halves the search space each iteration. For n=1,000,000:
- Linear: ~500,000 operations average
- Binary: ~20 operations (log₂ 1,000,000 ≈ 20)
Binary Search is exponentially faster for large datasets.
*/

// ITERATIVE BINARY SEARCH - Q3.B.1 & Q3.B.2
int binarySearch(int arr[], int size, int key, int& iterationCount) {
    iterationCount = 0;
    int low = 0, high = size - 1;
    
    while (low <= high) {
        iterationCount++;
        int mid = low + (high - low) / 2;
        
        if (arr[mid] == key) {
            return mid;
        } else if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    return -1;
}

// ============================================================================
// Q4 - COMPLEXITY ANALYSIS (BIG O) (10 Marks)
// ============================================================================

// THEORY ANSWERS - Q4.A
/*
Q4.A.1 - What Big O Notation Describes:
Big O describes how an algorithm's time or space requirements grow as input size increases.
We use Big O instead of runtime in seconds because:
- Runtime depends on hardware (fast vs slow computers)
- Runtime changes with different inputs of same size
- Big O is hardware-independent and shows scalability
- It helps predict behavior on large inputs

Q4.A.2 - Big O, Big Omega, Big Theta (Analogy):
Imagine a taxi fare: Big O is the worst-case scenario (worst traffic, longest route).
Big Omega is the best-case scenario (no traffic, shortest route). Big Theta is the
typical/average case (normal traffic, typical route). Big O gives an upper bound,
Big Omega a lower bound, and Big Theta characterizes both (tight bound).

Q4.A.3 - Ranking from Fastest to Slowest (large n):
O(1) < O(log n) < O(n) < O(n log n) < O(n²)

Q4.A.4 - Space Complexity:
Space Complexity describes how much memory an algorithm uses relative to input size.
If a function creates a temporary array of size n internally, its space complexity is O(n)
because memory usage grows linearly with input size. The temporary array requires n*sizeof(element) bytes.

Q4.A.5 - O(n²) vs O(n log n) Comparison:
NO, the student is incorrect. Asymptotic analysis proves O(n log n) always beats O(n²) for
sufficiently large n, regardless of hardware speed. Example: Even if O(n²) runs 1000x faster,
at n=1,000,000: O(n log n) ≈ 20,000,000 ops vs O(n²) ≈ 1,000,000,000,000 ops.
The asymptotic growth rate dominates constant factors for large inputs.
*/

// NESTED LOOP FUNCTION - Q4.B.1
void nestedLoopFunction(int arr[], int n) {
    /*
    Time Complexity Analysis:
    - Outer loop runs: n times
    - Inner loop runs: n times for each outer iteration
    - Total iterations: n * n = n²
    - Each iteration does O(1) work
    - Total Time Complexity: O(n²)
    */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i] * arr[j] << " ";
        }
    }
    cout << endl;
}

// SINGLE LOOP FUNCTION - Q4.B.1
void singleLoopFunction(int arr[], int n) {
    /*
    Time Complexity Analysis:
    - Loop runs: n times
    - Each iteration does O(1) work
    - Total Time Complexity: O(n)
    
    Comparison: Single loop O(n) is linear, nested O(n²) is quadratic.
    For n=1000: Single = 1000 ops, Nested = 1,000,000 ops (1000x slower)
    */
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// CHECK IF ALL ELEMENTS EXIST - Q4.B.2
bool allElementsExist(int A[], int B[], int n) {
    /*
    Time Complexity Analysis of Current Approach:
    Algorithm: For each element in A, search linearly in B
    - Outer loop: O(n) iterations for each element in A
    - Inner loop: O(n) iterations in array B for each search
    - Total: O(n) * O(n) = O(n²)
    This is inefficient for large arrays.
    
    More Efficient Approach (not coded, as per requirement):
    1. Sort array B: O(n log n)
    2. For each element in A, binary search in B: O(n log n)
    3. Total: O(n log n) - much better than O(n²)
    
    Alternative (even better):
    1. Create hash set from B: O(n)
    2. For each element in A, lookup in hash set: O(n)
    3. Total: O(n) with O(n) space
    */
    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < n; j++) {
            if (A[i] == B[j]) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

// ============================================================================
// Q5 - SINGLY LINKED LIST (10 Marks)
// ============================================================================

// NODE STRUCTURE - Q5.B.1
struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

// LINKED LIST CLASS
class LinkedList {
private:
    Node* head;
    
public:
    // Constructor - Q5.B.1
    LinkedList() : head(nullptr) {}
    
    // INSERT AT HEAD - Q5.B.2
    void insertAtHead(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }
    
    // INSERT AT TAIL - Q5.B.2
    void insertAtTail(int val) {
        Node* newNode = new Node(val);
        
        if (head == nullptr) {
            head = newNode;
            return;
        }
        
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    
    // DISPLAY - Q5.B.2
    void display() {
        cout << "List: ";
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "null\n";
    }
    
    // DELETE BY VALUE - Q5.B.3
    void deleteByValue(int val) {
        // Case: Delete head node
        if (head != nullptr && head->data == val) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Deleted " << val << " from head\n";
            return;
        }
        
        // Case: Delete from middle or tail
        Node* current = head;
        while (current != nullptr && current->next != nullptr) {
            if (current->next->data == val) {
                Node* temp = current->next;
                current->next = temp->next;
                delete temp;
                cout << "Deleted " << val << " from list\n";
                return;
            }
            current = current->next;
        }
        
        // Case: Value not found
        cout << "Value " << val << " not found in list\n";
    }
    
    // Destructor to free memory
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

// THEORY ANSWERS - Q5.A
/*
Q5.A.1 - Singly Linked List:
A Singly Linked List is a linear data structure where each element (node) contains data
and a pointer to the next node. Memory Structure Difference from Arrays:
- Arrays: Contiguous memory blocks, fixed size, O(1) access
- Linked Lists: Scattered memory (nodes allocated individually), dynamic size, O(n) access
- Arrays allocate all at once; Linked Lists allocate per insertion

Q5.A.2 - Time Complexities in Singly Linked List:
- Insertion at head: O(1) - new node points to current head, update head pointer
- Insertion at tail: O(n) - must traverse to find last node (no tail pointer stored)
- Deletion by value: O(n) - must search for node (worst case: traverse whole list)

Q5.A.3 - Memory Leak in Linked Lists:
If you remove a node without calling delete, the memory remains allocated but inaccessible.
This is called a "memory leak." To avoid: Always call delete on the node before unlinking it.
Example: When removing node X, first save X's address, unlink it, then delete X.
*/

// ============================================================================
// MAIN FUNCTION - DEMONSTRATION
// ============================================================================

int main() {
    cout << "========== DATA STRUCTURES AND ALGORITHMS ASSIGNMENT 1 ==========\n";
    
    // Q1 - ARRAYS AND SEARCHING
    cout << "\n--- Q1: Arrays and Searching ---\n";
    int arr1[10] = {4, 15, 7, 23, 1, 9, 42, 18, 6, 30};
    
    cout << "Q1.B.1 - Linear Search:\n";
    int searchIdx = linearSearch(arr1, 10, 42);
    if (searchIdx != -1) {
        cout << "Element 42 found at index: " << searchIdx << endl;
    } else {
        cout << "Element 42 not found\n";
    }
    
    cout << "\nQ1.B.2 - Min and Max:\n";
    int minVal, maxVal;
    findMinMax(arr1, 10, minVal, maxVal);
    cout << "Minimum value: " << minVal << endl;
    cout << "Maximum value: " << maxVal << endl;
    
    // Q2 - BUBBLE SORT
    cout << "\n--- Q2: Bubble Sort ---\n";
    int arr2[7] = {64, 34, 25, 12, 22, 11, 90};
    int swapCount = 0;
    bubbleSort(arr2, 7, swapCount);
    cout << "\nQ2.B.2 - Total swaps made: " << swapCount << endl;
    
    // Q3 - BINARY SEARCH
    cout << "\n--- Q3: Binary Search ---\n";
    int arr3[10] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72};
    
    cout << "Q3.B.1 - Binary Search for 56:\n";
    int iterCount = 0;
    int foundIdx = binarySearch(arr3, 10, 56, iterCount);
    cout << "Found at index: " << foundIdx << endl;
    cout << "Iterations taken: " << iterCount << endl;
    
    cout << "\nQ3.B.2 - Binary Search with two cases:\n";
    iterCount = 0;
    int result1 = binarySearch(arr3, 10, 23, iterCount);
    cout << "Search for 23 (exists): Found at index " << result1 
         << ", Iterations: " << iterCount << endl;
    
    iterCount = 0;
    int result2 = binarySearch(arr3, 10, 100, iterCount);
    cout << "Search for 100 (not exists): Result " << result2 
         << ", Iterations: " << iterCount << endl;
    
    // Q4 - COMPLEXITY ANALYSIS
    cout << "\n--- Q4: Complexity Analysis ---\n";
    int arr4[5] = {1, 2, 3, 4, 5};
    cout << "Q4.B.1 - Nested loop O(n²):\n";
    nestedLoopFunction(arr4, 5);
    
    cout << "\nQ4.B.1 - Single loop O(n):\n";
    singleLoopFunction(arr4, 5);
    
    cout << "\nQ4.B.2 - Check if all elements exist:\n";
    int A[3] = {1, 2, 3};
    int B[5] = {1, 2, 3, 4, 5};
    bool result = allElementsExist(A, B, 3);
    cout << "All elements of A exist in B: " << (result ? "Yes" : "No") << endl;
    
    // Q5 - SINGLY LINKED LIST
    cout << "\n--- Q5: Singly Linked List ---\n";
    LinkedList list;
    
    cout << "Q5.B.4 - Demonstration:\n";
    cout << "Inserting 5 nodes (mix of head and tail):\n";
    
    list.insertAtTail(10);
    list.display();
    
    list.insertAtHead(5);
    list.display();
    
    list.insertAtTail(15);
    list.display();
    
    list.insertAtHead(1);
    list.display();
    
    list.insertAtTail(20);
    list.display();
    
    cout << "\nDeleting existing value (15):\n";
    list.deleteByValue(15);
    list.display();
    
    cout << "\nAttempting to delete non-existing value (100):\n";
    list.deleteByValue(100);
    list.display();
    
    cout << "\n========== END OF ASSIGNMENT ==========\n";
    // GitHub: https://github.com/haristalat/DSA-assignments/tree/main
    
    return 0;
}
