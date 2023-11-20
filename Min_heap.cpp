#include <iostream>
#define  Max_Size 10000
using namespace std;

class Min_Heap{

private:
    typedef struct Heap{
        int heap[Max_Size]={NULL};
        int Heap_Size=0;
    };

    Heap HEAP;

    int IsKey(Heap &h,int key){
        for(int i=1;i<h.Heap_Size+1;i++){
            if(h.heap[i]==key){
                return 1;
            }
        }
        return 0;
    }

    void Insert(Heap & h, int key) { 
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

    int Delete(Heap &h) {

        if(HEAP.Heap_Size == 1){
            int MIN_Key=h.heap[1];
            h.heap[1]=NULL;
            h.heap[0]=0; 
            h.Heap_Size=h.heap[0];
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
            } else {
                return MIN_Key;
            }
        }
    }

public:
    Min_Heap(){
        this->HEAP;
    }

    void Display() {
        cout << " ---------Heap---------" << endl;
        cout << "** Select the number **" << endl;
        cout << " 1. Insert Key         " << endl;
        cout << " 2. Delete             " << endl;
        cout << " 3. Show Heap          " << endl;
        cout << " 4. Show Minimum key   " << endl;
        cout << " 5. Show Heap Size     " << endl;
        cout << " 6. exit        " << endl;
        cout << endl;
    }

    void SelectMenu() {
        Display();
        int i ;

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
                    cout<<"Minimum: "<<this->HEAP.heap[1]<<endl;        //Heap 비워도 값이 남아있음
                    break;

                case 5:
                    cout<<"Heap Size는 "<<this->HEAP.Heap_Size<<endl;

                    break;

                case 6:
                    return ;

                default:
                    cout << "Error: Select the number 1~8 \n"<<endl;
                    return;
            }
        }
    }

    void Insert_heap(){
        int key;
        cout << "key to insert :  ";
        cin >> key;

        if(IsKey(this->HEAP,key)==1){
            cout<<key<<" 값은 이미 존재합니다! 다른 수를 입력해주세요"<<endl;
            return;
        }

        Insert(this->HEAP,key);
        return;
    }

    void Print_Heap(){
        if(this->HEAP.Heap_Size==0){
            cout<<"현재 Heap은 비어있습니다."<<endl;
            return ;
        }

        for(int i=1;i<this->HEAP.Heap_Size+1;i++){
            cout<< this->HEAP.heap[i]<<" ";
        }
        cout<<endl;
        return;


    }

    void Delete_heap(){
        if(this->HEAP.Heap_Size==0){
            cout<<"현재 Heap은 비어있습니다."<<endl;
            return;
        }

        Delete(this->HEAP);
        return;

    }
};

int main() {
    Min_Heap H;
    H.SelectMenu();
    return 0;
}
