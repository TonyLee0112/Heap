#include <iostream>
#define  Max_Size 10000
using namespace std;

//insert, delete, max값 ,min 값 ,작은순대로 sorting,Heap size,

class Max_Heap {

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

    void Insert(Heap & h,int key){
        int current_index=h.Heap_Size+1;

        if(h.Heap_Size==0){
            h.heap[current_index]=key;
            h.Heap_Size=h.Heap_Size+1;
            h.heap[0]=h.Heap_Size;

            return ;
        }

        h.heap[current_index]=key;
        h.Heap_Size=h.Heap_Size+1;
        h.heap[0]=h.Heap_Size;

        //0 일때도 고려
        while(current_index>1) {
            int parent_index=current_index/2;
            if (h.heap[parent_index] < key)  {
                int temp=h.heap[parent_index];
                h.heap[parent_index]=h.heap[current_index];
                h.heap[current_index]=temp;
                current_index=parent_index;

            }
            // parent>key
            else{
                break;
            }

        }

        return;

    }


    int Delete(Heap &h) {

        if(h.Heap_Size==1){
            int MAX_Key=h.heap[1];
            h.heap[1]=NULL;
            h.heap[0]=0;
            h.Heap_Size=h.heap[1];

            return MAX_Key;

        }


        int MAX_Key = h.heap[1];
        int Last_key = h.heap[h.Heap_Size];
        h.heap[h.Heap_Size] = 0;
        h.Heap_Size = h.Heap_Size - 1;
        h.heap[0] = h.Heap_Size;
        h.heap[1] = Last_key;

        int current_index = 1;

        while (true) {
            int left_child = current_index * 2;
            int right_child = current_index * 2 + 1;
            int max_child = current_index; // 현재 노드와 비교할 노드

            if (left_child <= h.Heap_Size && h.heap[left_child] > h.heap[max_child]) {
                max_child = left_child;
            }
            if (right_child <= h.Heap_Size && h.heap[right_child] > h.heap[max_child]) {
                max_child = right_child;
            }

            if (max_child != current_index) {
                int temp = h.heap[max_child];
                h.heap[max_child] = h.heap[current_index];
                h.heap[current_index] = temp;
                current_index = max_child;
            } else {
                return MAX_Key;
            }
        }
    }



public:
    Max_Heap(){
        this->HEAP;
    }

    void Display() {
        cout << " ---------Heap---------" << endl;
        cout << "** Select the number **" << endl;
        cout << " 1. Insert Key         " << endl;
        cout << " 2. Delete             " << endl;
        cout << " 3. Show Heap          " << endl;
        cout << " 4. Show Maximum key   " << endl;
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
                    cout<<"Maximum: "<<this->HEAP.heap[1]<<endl;        //Heap 비워도 값이 남아있음
                    break;

                case 5:
                    Heap_size();
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

        for(int i=1;i<this->HEAP.Heap_Size+1;i++){
            cout<< this->HEAP.heap[i]<<" ";
        }
        cout<<endl;


    }

    void Delete_heap(){
        if(this->HEAP.Heap_Size==0){
            cout<<"현재 Heap은 비어있습니다."<<endl;
            return;
        }

        Delete(this->HEAP);
        return;

    }

    void Heap_size(){
        cout<<"현재 Heap의 사이즈는 "<<this->HEAP.Heap_Size<<" 입니다."<<endl;
    }








};




int main() {

    Max_Heap H;
    H.SelectMenu();

    return 0;
}
