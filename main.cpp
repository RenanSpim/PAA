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

    void heap(vector<double>& inputArr) {
        int n = inputArr.size();

        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(inputArr, n, i);
        }

        for (int i = n - 1; i >= 0; i--) {
            swap(inputArr[0], inputArr[i]);
            heapify(inputArr, i, 0);
        }
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

    void merge(vector<double>& inputArr) {
        _merge_sort(inputArr, 0, inputArr.size() - 1);
    }

    void quick(vector<double>& inputArr) {
        _quick_sort(inputArr, 0, inputArr.size() - 1);
    }

    void radix(vector<double>& inputArr) {
        int m = inputArr[0];

        for (int i = 1; i < inputArr.size(); i++) {
            if (m < inputArr[i]) m = inputArr[i];
        }

        for (int exp = 1; m / exp > 0; exp *= 10) {
            _countSort(inputArr, exp);
        }
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

    void shell(vector<double>& inputArr) {
        int i, j, n = inputArr.size();
        double temp;

        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (i = gap; i < n; i++) {
                temp = inputArr[i];
                for (j = i; j >= gap && inputArr[j - gap] > temp; j -= gap) {
                    inputArr[j] = inputArr[j - gap];
                }

                inputArr[j] = temp;
            }
        }
    }

private:
    struct Node {
        double data;
        Node *next;
    };

    void _countSort(vector<double>& inputArr, int exp) {
        int i, n = inputArr.size();
        vector<int> count(10, 0);
        vector<double> output(n);
        for (i = 0; i < n; i++) {
            count[(int)(inputArr[i] / exp) % 10]++;
        }

        for (i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (i = n - 1; i >= 0; i--) {
            output[count[(int)(inputArr[i] / exp) % 10]-- - 1] = inputArr[i];
        }

        for (int i = 0; i < n; i++) {
            inputArr[i] = output[i];
        }
    }

    void heapify(vector<double>& inputArr, int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * (i + 1);

        if (l < n && inputArr[l] > inputArr[largest]) {
            largest = l;
        }

        if (r < n && inputArr[r] > inputArr[largest]) {
            largest = r;
        }

        if (largest != i) {
            swap(inputArr[i], inputArr[largest]);
            heapify(inputArr, n, largest);
        }
    }
    
    void _merge_sort(vector<double>& inputArr, int left, int right) {
        if (left >= right) return;

        int mid = left + (right - left) / 2;

        _merge_sort(inputArr, left, mid);
        _merge_sort(inputArr, mid + 1, right);

        int n1 = mid - left + 1;
        int n2 = right - mid;
        vector<double> L(n1), R(n2);
        double *pointer = L.data();

        for (int i = 0; i < n1; i++) {
            L[i] = inputArr[left + i];
        }

        for (int i = 0; i < n2; i++) {
            R[i] = inputArr[mid + 1 + i];
        }

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                inputArr[k++] = L[i++];
            } else {
                inputArr[k++] = R[j++];
            }
        }

        int pointerInt = i;
        int pointerMax = n1;

        if (n1 - i == 0) {
            pointer = R.data();
            pointerInt = j;
            pointerMax = n2;
        }

        while (pointerInt < pointerMax) {
            inputArr[k++] = pointer[pointerInt++];
        }
    }

    void _quick_sort(vector<double>& inputArr, int low, int high) {
        if (low >= high) return;

        double pivot = inputArr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (inputArr[j] >= pivot) continue;
            
            i++;
            swap(inputArr[j], inputArr[i]);
        }

        swap(inputArr[i + 1], inputArr[high]);
        int partitionI = i + 1;

        _quick_sort(inputArr, low, partitionI - 1);
        _quick_sort(inputArr, partitionI + 1, high);
    }
};

int main() {
    vector<double> inputArr = { 2, 24, 1, 2, 5, 1, 10, 8, 8, 4, 6, 0 };
    Sort sort;
    
    sort.radix(inputArr);
    
    for (auto& elem : inputArr)
        cout << elem << " ";
    cout << endl;
}
