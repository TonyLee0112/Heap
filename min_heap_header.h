#pragma once
class Min_Heap {

private:
    typedef struct Heap { // Define Heap as a new struct
        int heap[Max_Size] = { NULL };
        int Heap_Size = 0; //initialize
    };

    Heap HEAP;

    int IsKey(Heap& h, int key) {
        for (int i = 1; i < h.Heap_Size + 1; i++) {
            if (h.heap[i] == key) {
                return 1;
            }
        }
        return 0;
    }

    void Insert(Heap& h, int key) {
        int current_index = h.Heap_Size + 1; // key 를 추가할 위치 = current_index & Array 의 마지막 원소

        if (h.Heap_Size == 0) {
            h.heap[current_index] = key;
            h.Heap_Size = h.Heap_Size + 1;
            h.heap[0] = h.Heap_Size;

            return;
        }

        h.heap[current_index] = key;
        h.Heap_Size = h.Heap_Size + 1;
        h.heap[0] = h.Heap_Size;

        // 0 일때도 고려
        while (current_index > 1) { // Recursive
            int parent_index = current_index / 2; //부모 node 의 index = 자식 node 의 index를 2로 나눈 몫
            if (h.heap[parent_index] > key) {  // 부등호 방향이 변경됨 -> swap
                int temp = h.heap[parent_index];
                h.heap[parent_index] = h.heap[current_index];
                h.heap[current_index] = temp;
                current_index = parent_index; // Ex) [0,2,3,4,5,1] -> [0,2,1,4,5,3] -> [0,1,2,4,5,3] 
            }
            // parent < key (부등호 방향이 변경됨)
            else {
                break;
            }
        }

        return;
    }

    int Delete(Heap& h) {

        if (HEAP.Heap_Size == 1) {
            int MIN_Key = h.heap[1];
            h.heap[1] = NULL;
            h.heap[0] = 0;
            h.Heap_Size = h.heap[0];
            return MIN_Key;
        }


        int MIN_Key = h.heap[1];  // Max Heap에서 Min Heap으로 수정됨
        int Last_key = h.heap[h.Heap_Size]; // heap_size != 원소의 개수 + 1, = 원소의 개수
        h.heap[h.Heap_Size] = 0;
        h.Heap_Size = h.Heap_Size - 1;
        h.heap[0] = h.Heap_Size;
        h.heap[1] = Last_key;

        int current_index = 1;

        while (true) {
            int left_child = current_index * 2;
            int right_child = current_index * 2 + 1;
            int min_child = current_index; // 현재 노드와 비교할 노드

            // 세 노드에 대하여 최소 값을 가지는 노드 탐색
            if (left_child <= h.Heap_Size && h.heap[left_child] < h.heap[min_child]) {  // 부등호 방향이 변경됨
                min_child = left_child;
            }
            if (right_child <= h.Heap_Size && h.heap[right_child] < h.heap[min_child]) {  // 부등호 방향이 변경됨
                min_child = right_child;
            }
            // 발견된 최소 노드가 탐색 노드(부모 노드)가 아니면 swap
            if (min_child != current_index) {
                int temp = h.heap[min_child];
                h.heap[min_child] = h.heap[current_index];
                h.heap[current_index] = temp;
                current_index = min_child;
            }
            else {
                return MIN_Key;
            }
        }
    }

public:
    Min_Heap() {
        this->HEAP;
    }

    void Display() {
        cout << " ---------Heap---------                   " << endl;
        cout << "** Select the number **                   " << endl;
        cout << " 1. Insert Key                            " << endl;
        cout << " 2. Delete                                " << endl;
        cout << " 3. Show Heap                             " << endl;
        cout << " 4. Show Minimum key                      " << endl;
        cout << " 5. Show Heap Size                        " << endl;
        cout << " 6. Build A Heap From The Given Array     " << endl;
        cout << " 7. exit                                  " << endl;
        cout << endl;
    }

    void SelectMenu() { // 시작프로그램
        Display();
        int i;

        while (true) {
            cout << "select Menu : ";
            cin >> i;
            switch (i) {
            case 1:
                Insert_heap();
                break;
            case 2:
                Delete_heap();
                break;
            case 3:
                Print_Heap();
                break;
            case 4:
                cout << "Minimum: " << this->HEAP.heap[1] << endl;        //Heap 비워도 값이 남아있음
                break;

            case 5:
                cout << "Heap Size는 " << this->HEAP.Heap_Size << endl;

                break;
            case 6:
                Build_a_min_heap_from_array();
                break;

            case 7:
                return;

            default:
                cout << "Error: Select the number 1~8 \n" << endl;
                return;
            }
        }
    }

    void Insert_heap() {
        int key;
        cout << "key to insert :  ";
        cin >> key;

        if (IsKey(this->HEAP, key) == 1) {
            cout << key << " 값은 이미 존재합니다! 다른 수를 입력해주세요" << endl;
            return;
        }

        Insert(this->HEAP, key);
        return;
    }

    void Print_Heap() {
        if (this->HEAP.Heap_Size == 0) {
            cout << "현재 Heap은 비어있습니다." << endl;
            return;
        }

        for (int i = 1; i < this->HEAP.Heap_Size + 1; i++) {
            cout << this->HEAP.heap[i] << " ";
        }
        cout << endl;
        return;


    }

    void Delete_heap() {
        if (this->HEAP.Heap_Size == 0) {
            cout << "현재 Heap은 비어있습니다." << endl;
            return;
        }

        Delete(this->HEAP);
        return;

    }

    void Heapify(int index) { // 3개의 노드들에 대하여 실행
        int left_child = 2 * index; // 
        int right_child = 2 * index + 1;
        int smallest = index;

        // 왼쪽 자식과 비교
        if (left_child <= HEAP.Heap_Size && HEAP.heap[left_child] < HEAP.heap[smallest]) {
            smallest = left_child;
        }

        // 오른쪽 자식과 비교
        if (right_child <= HEAP.Heap_Size && HEAP.heap[right_child] < HEAP.heap[smallest]) {
            smallest = right_child;
        }

        // 현재 노드와 최소값을 가진 자식 노드 교환
        if (smallest != index) {
            swap(this->HEAP.heap[index], this->HEAP.heap[smallest]);
            // 재귀적으로 Heapify 호출
            Heapify(smallest);
        }
    }
    void Array_to_min_heap(int* arr, int n) { 
        this->HEAP.Heap_Size = n;

        // 주어진 배열의 값을 Heap의 배열에 복사
        for (int i = 0; i < n; i++) {
            this->HEAP.heap[i + 1] = *(arr+i);
        }

        // 주어진 배열의 중간부터 시작하여 Heapify
        for (int i = n / 2; i > 0; i--) {
            Heapify(i);
        }
    }
    void Build_a_min_heap_from_array() {
        cout << "배열의 크기를 입력하세요" << endl;
        int a_size;
        cin >> a_size;
        int* myArray = new int[a_size + 1]; // 동적으로 입력값 할당받음
        *myArray = a_size; // myArray[0] = sizeof(myArray)
        cout << "배열에 " << a_size << "개의 정수 값을 입력하세요: ";
        for (int i = 0; i < a_size; i++) {
            cin >> myArray[i + 1];
        }
        Array_to_min_heap(myArray, a_size);
    }

};
