#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;

class Sort {
public:
    void bubble(vector<double>& inputArr) {
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
        vector<Node *> buckets(n, nullptr);
        
        double minValue = *min_element(inputArr.begin(), inputArr.end());
        double maxValue = *max_element(inputArr.begin(), inputArr.end());
        
        double range = (maxValue - minValue) / n;

        for (auto& elem : inputArr) {
            int i = (int)((elem - minValue) / range);
            if (i >= n) i = n - 1;

            Node *newNode = new Node{ elem, nullptr };

            if (buckets[i] == nullptr) {
                buckets[i] = newNode;
            } else {
                Node *curr = buckets[i];
                Node *prev = nullptr;

                while (curr != nullptr && curr->data < newNode->data) {
                    prev = curr;
                    curr = curr->next;
                }

                if (prev == nullptr) {
                    newNode->next = buckets[i];
                    buckets[i] = newNode;
                } else {
                    prev->next = newNode;
                    newNode->next = curr;
                }
            }
        }

        int index = 0;
        for (auto& bucket : buckets) {
            Node *curr = bucket;
            
            while (curr != nullptr) {
                inputArr[index++] = curr->data;
                Node *temp = curr;
                curr = curr->next;
                delete temp;
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
        _quickSort(inputArr, 0, inputArr.size() - 1);
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

    int partition(vector<double>& inputArr, int low, int high) {
        int pivot = inputArr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (inputArr[j] < pivot) {
                i++;
                swap(inputArr[i], inputArr[j]);
            }
        }
        
        swap(inputArr[i + 1], inputArr[high]);  

        return i + 1;
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

    void _quickSort(vector<double>& inputArr, int low, int high) {
        if (low < high) {
            int pi = partition(inputArr, low, high);
            _quickSort(inputArr, low, pi - 1);
            _quickSort(inputArr, pi + 1, high);
        }
    }
};

int main(int argc, char *argv[]) {
    vector<double> inputArr(stoi(argv[1]));
    Sort sort;
    
    std::chrono::duration<double, std::milli> durations[3];
    double sum = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < inputArr.size(); j++) {
            switch (argv[2][0]) {
            case 'a':
                inputArr[j] = (rand() % 100000) / 100;
                break;
            case 'o':
                inputArr[j] = j / 1000.0;
                break;
            default:
                inputArr[j] = (inputArr.size() - j) / 1000.0;
                break;
            }
        }

        auto start = chrono::high_resolution_clock::now();
        sort.quick(inputArr);
        auto end = chrono::high_resolution_clock::now();

        durations[i] = end - start;
    }
    
    for (int i = 0; i < 3; i++) {
        cout << durations[i].count() << " ms, ";
        sum += durations[i].count();
    }

    cout << "média: " << sum / 3.0 << " ms" << endl;
}
