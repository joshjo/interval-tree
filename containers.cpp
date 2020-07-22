#include "src/includes.h"

using namespace std;


vector<long> getValues(int size) {
    vector<long> result;

    for (long i = 0; i < size; i++) {
        result.push_back(rand() % size);
    }

    return result;
}


int main () {
    srand(100);
    long size = 10000000;
    vector<long> values = getValues(size);

    auto start_time_vector = std::chrono::system_clock::now();
    vector<long> vec;
    for (long i = 0; i < size; i++) {
        vec.push_back(values[i]);
    }
    auto end_time_vector = std::chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end_time_vector - start_time_vector;
    cout << "vector size: " << vec.size() << endl;
    cout << "vector time: " << elapsed_seconds.count() << endl;

    auto start_time_vector2 = std::chrono::system_clock::now();
    vector<long> vec2;
    for (long i = 0; i < size; i++) {
        if (!binary_search(vec2.begin(), vec2.end(), values[i])) {
            vec2.push_back(values[i]);
        }
    }
    auto end_time_vector2 = std::chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds2 = end_time_vector2 - start_time_vector2;
    cout << "vector 2 size: " << vec2.size() << endl;
    cout << "vector 2 time: " << elapsed_seconds2.count() << endl;

    // auto start_time_set = std::chrono::system_clock::now();
    // set<long> s;
    // for (long i = 0; i < size; i++) {
    //     s.insert(values[i]);
    // }
    // auto end_time_set = std::chrono::system_clock::now();
    // chrono::duration<double> elapsed_seconds_set = end_time_set - start_time_set;
    // cout << "uset size: " << s.size() << endl;
    // cout << "set time: " << elapsed_seconds_set.count() << endl;

    auto start_time_u_set = std::chrono::system_clock::now();
    unordered_set<long> us;
    for (long i = 0; i < size; i++) {
        us.insert(values[i]);
    }
    auto end_time_u_set = std::chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds_u_set = end_time_u_set - start_time_u_set;
    cout << "uset size: " << us.size() << endl;
    cout << "uset time: " << elapsed_seconds_u_set.count() << endl;

    auto start_time_u_set2 = std::chrono::system_clock::now();
    unordered_set<long> us2;
    us2.reserve(size * 10);
    for (long i = 0; i < size; i++) {
        us2.insert(values[i]);
    }
    auto end_time_u_set2 = std::chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds_u_set2 = end_time_u_set2 - start_time_u_set2;
    cout << "uset time: " << elapsed_seconds_u_set2.count() << endl;

    return 0;
}
