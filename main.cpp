#include <iostream>
#include <vector>

using namespace std;

class Sort {
public:
    void bubble(vector<int>& inputArr) {
        int n = inputArr.size();

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (inputArr[j] > inputArr[j + 1]) {
                    swap(inputArr[j], inputArr[j + 1]);
                }
            }
        }
    }

    void bucket(vector<double>& inputArr) {
        int n = inputArr.size();
        vector<Node*> buckets(n, nullptr);

        for (auto& elem : inputArr) {
            int i = (int) (elem * n);
            Node *newNode = new Node{ elem, nullptr };

            if (i >= n) i = n - 1;

            if (buckets[i] == nullptr) {
                buckets[i] = newNode;
                continue;
            }

            Node *curr = buckets[i];

            while (curr->next != nullptr) {
                if (curr->data > newNode->data) {
                    swap(curr->data, newNode->data);
                }
                
                curr = curr->next;
            }
            
            if (curr->data > newNode->data) {
                swap(curr->data, newNode->data);
            }

            curr->next = newNode;
        }

        int index = 0;
        Node *curr;
        
        for (auto& bucket : buckets) {
            curr = bucket;

            while (curr != nullptr) {
                inputArr[index++] = curr->data;
                curr = curr->next;
            }
        }
    }

    void counting(vector<double>& inputArr) {
        int n = inputArr.size(), max = -1;
        vector<int> countArr;
        vector<double> outputArr(n);

        for (auto& elem : inputArr) {
            if (elem > max) max = elem;
        }

        countArr.resize(max + 1);

        for (auto& elem : inputArr) {
            countArr[elem]++;
        }
        
        for (int i = 1; i < max + 1; i++) {
            countArr[i] += countArr[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            outputArr[countArr[inputArr[i]]-- - 1] = inputArr[i];
        }
        
        inputArr = outputArr;
    }

    void insertion(vector<double>& inputArr) {
        int n = inputArr.size();

        for (int i = 1; i < n; i++) {
            int j = i;

            while (inputArr[j - 1] > inputArr[j]) {
                swap(inputArr[j - 1], inputArr[j]);
                j--;
            }
        }
    }

    void quick(vector<double>& inputArr) {
        _quick_sort(inputArr, 0, inputArr.size() - 1);
    }

    void selection(vector<double>& inputArr) {
        int n = inputArr.size();

        for (int i = 0; i < n; i++) {
            int min = inputArr[i];

            for (int j = i + 1; j < n; j++) {
                if (min > inputArr[j]) {
                    min = inputArr[j];
                    swap(inputArr[i], inputArr[j]);
                }
            }
        }
    }

private:
    struct Node {
        double data;
        Node *next;
    };

    int partition(vector<double>& arr, int low, int high) {
        double pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[j], arr[i]);
            }
        }

        swap(arr[i + 1], arr[high]);

        return i + 1;
    }

    void _quick_sort(vector<double>& inputArr, int low, int high) {
        if (low >= high) return;

        int partitionI = partition(inputArr, low, high);

        _quick_sort(inputArr, low, partitionI - 1);
        _quick_sort(inputArr, partitionI + 1, high);

    }
};

int main() {
    vector<double> inputArr = { 24, 5, 1, 4, 6, 0 };
    Sort sort;
    
    sort.quick(inputArr);
    
    for (auto& elem : inputArr)
        cout << elem << " ";
    cout << endl;
}
