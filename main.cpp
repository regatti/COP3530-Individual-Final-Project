#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;

// swap function from lecture slides for Quick Sort
//used to be able to swap elements in an array
void swap(double* a, double* b) {
    double t = *a;
    *a = *b;
    *b = t;
}

// printArray function from lecture slides for Quicksort
//used for printing elements in the vector
void printArray(const vector<int>& array) {
    for (int i = 0; i < array.size(); ++i)
        cout << array[i] << " ";

}

// partition function from lecture slides for Quick Sort
// the pivot is selected and then it partitions the array
int partition(vector<double>& array, int low, int high) {
    double pivot = array[low];
    int up = low, down = high;

    while (up < down) {
        // finds element larger than pivot from left
        while (up < high && array[up] <= pivot)
            up++;
        //smaller than pivot right
        while (down > low && array[down] >= pivot)
            down--;

        //swaps elements in the halves
        if (up < down)
            swap(&array[up], &array[down]);
    }

    //swaps pivot into correct position
    swap(&array[low], &array[down]);
    return down;
}

//quickSort function from lecture slides for Quick Sort
void quickSort(vector<double>& array, int low, int high) {
    if (low < high) {
        int pivot = partition(array, low, high);
        quickSort(array, low, pivot - 1);
        quickSort(array, pivot + 1, high);
    }
}


// from lecture slides for Merge Sort to merge two sorted sub arrays
void merge(vector<double>& data, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    //temporary arrays for the left and right sub arrays
    vector<double> L(n1);
    vector<double> R(n2);

    //data assigned to these left and right arrays
    for (int i = 0; i < n1; i++)
        L[i] = data[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = data[mid + 1 + j];

    //merges arrays
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            data[k] = L[i];
            i++;
        }
        else {
            data[k] = R[j];
            j++;
        }
        k++;
    }

    //remaining elements
    while (i < n1) {
        data[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        data[k] = R[j];
        j++;
        k++;
    }
}

//from lecture slides for Merge Sort
void mergeSort(vector<double>& data, int left, int right) {
    if (left < right) {
        //finds middle point of array by dividing it by 2
        int mid = left + (right - left) / 2;

        //recursively sorts the first and second halves
        mergeSort(data, left, mid);
        mergeSort(data, mid + 1, right);

        //merges the sorted halves
        merge(data, left, mid, right);
    }
}


int main() {
    const int numFiles = 12;
    const string fileNames[] = {
            "5ascend", "5descend", "5random",
            "10ascend", "10descend", "10random",
            "15ascend", "15descend", "15random",
            "25ascend", "25descend", "25random"
    };

    // asks user for sorting algorithm choice
    cout << "Choose a sorting algorithm by typing in the number 1 or 2:\n";
    cout << "1. Quicksort\n";
    cout << "2. Mergesort\n";
    int choice;
    cin >> choice;

    //stores data from all the csv files
    vector<double> allData;

    //start time for all files, this is not used for the individual sorts that the project is asking for: look at line 141
    //thiss is used at the end after all sorts have been done
    // reference: https://learn.microsoft.com/en-us/cpp/standard-library/steady-clock-struct?view=msvc-170
    auto totalStartTime = chrono::steady_clock::now();

    //goes thru each file individually
    for (int i = 0; i < numFiles; ++i) {
        vector<double> fileData;  // sata for each file

        string fileName = fileNames[i] + ".csv";
        ifstream file(fileName);

        double value;
        while (file >> value) {
            fileData.push_back(value);
        }

        file.close();

        //reference: https://learn.microsoft.com/en-us/cpp/standard-library/steady-clock-struct?view=msvc-170
        // starts the time for the individual sorts now like the project pdf asked
        auto startTime = chrono::steady_clock::now();

        // sorting based on user choice
        switch (choice) {
            case 1:
                quickSort(fileData, 0, fileData.size() - 1);
                break;
            case 2:
                mergeSort(fileData, 0, fileData.size() - 1);
                break;
            default:
                cout << "Invalid choice, please make sure you choose either 1 or 2 next time\n";
                return 1;
        }

        //end time for each file
        auto endTime = chrono::steady_clock::now();

        // this calculates and outputs the time for each file in nanoseconds
        auto duration = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);
        //cout << "Time taken for sorting " << fileName << ": " << duration.count() << " nanoseconds\n";
        //^had to change above line of code because I originally just displayed the file names so I could easily tell if the code was working
        // and because I knew what the file names meant
        //but then I realized it would be better for a user to see the number of data points and whether the data was random, or in ascending/descending order

        //code below reference: https://www.educative.io/answers/what-is-stringnpos-in-cpp
        string label;
        if (fileName.find("25ascend") != string::npos)
            label = "25000 ascending data points";
        else if (fileName.find("25descend") != string::npos)
            label = "25000 descending data points";
        else if (fileName.find("25random") != string::npos)
            label = "25000 random data points";
        else if (fileName.find("15ascend") != string::npos)
            label = "15000 ascending data points";
        else if (fileName.find("15descend") != string::npos)
            label = "15000 descending data points";
        else if (fileName.find("15random") != string::npos)
            label = "15000 random data points";
        else if (fileName.find("10ascend") != string::npos)
            label = "10000 ascending data points";
        else if (fileName.find("10descend") != string::npos)
            label = "10000 descending data points";
        else if (fileName.find("10random") != string::npos)
            label = "10000 random data points";
        else if (fileName.find("5ascend") != string::npos)
            label = "5000 ascending data points";
        else if (fileName.find("5descend") != string::npos)
            label = "5000 descending data points";
        else if (fileName.find("5random") != string::npos)
            label = "5000 random data points";
        else
            label = "data points";

        cout << "Time taken for sorting " << label << ": " << duration.count() << " nanoseconds\n";

        // append sorted data so it doesnt get lost and can be used to display total time
        allData.insert(allData.end(), fileData.begin(), fileData.end());
    }

    //sorting time for all 12 files for chosen sort
    // reference: https://learn.microsoft.com/en-us/cpp/standard-library/steady-clock-struct?view=msvc-170
    auto totalEndTime = chrono::steady_clock::now();
    auto totalDuration = chrono::duration_cast<chrono::nanoseconds>(totalEndTime - totalStartTime);
    cout << "Total time taken for sorting all " << numFiles << " files: " << totalDuration.count() << " nanoseconds\n";

}
