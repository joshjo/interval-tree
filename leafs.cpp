#include <chrono>
#include <ctime>


#include "src/leaftree.h"


using namespace std;


int main () {
    int key_domain_size = 1000;
    int leaf_size = 100;
    int Q = 150;
    int query_number = 100;

    vector<Interval<int> > intervals;
    LeafTree<int, Interval<int> * > t;

    // for (int i = 0; i < query_number; i += 1) {
    //     int S1 = rand() % key_domain_size;
    //     int R1 = rand() % Q;
    //     Interval<int> I(S1, S1 + R1);
    //     // cout << I << endl;
    //     intervals.push_back(I);
    //     tree.insert(I);
    // }

    Interval<int> IA(407663,1015348);
    Interval<int> IB(1015348,1974033);
    Interval<int> IC(1974033,2591355);
    Interval<int> ID(2591355,3059559);
    Interval<int> IE(3059559,3733149);
    Interval<int> IF(3733149,4406740);
    Interval<int> IG(4406740,5391866);
    Interval<int> IH(5391866,5718249);
    Interval<int> II(5718249,6245735);
    Interval<int> IJ(6245735,6751918);
    Interval<int> IK(6751918,7382632);
    Interval<int> IL(7382632,8382632);
    Interval<int> IM(8382632,8798020);
    Interval<int> IN(8798020,9552275);
    Interval<int> IO(9552275,9935194);
    Interval<int> IP(9935194,10864914);
    Interval<int> IQ(10864914,11285687);

    // Interval<int> Q1(650, 700);
    // // Interval<int> Q1(700, 720);


    auto start_time = std::chrono::system_clock::now();
    t.insert(IM);
    t.insert(IC);
    t.insert(IE);
    t.insert(ID);
    t.insert(IA);
    t.insert(IB);
    t.insert(IQ);
    t.insert(IP);
    t.insert(IJ);
    t.insert(IF);
    t.insert(IN);
    t.insert(IG);
    t.insert(IO);
    t.insert(IH);
    t.insert(IK);
    t.insert(IL);
    t.insert(II);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - start_time;

    cout << t.graphviz() << endl;

    cout << elapsed_seconds.count() << endl;
    // tree.print();
    // string * result;
    // int size = t.find(Q1, result);
    // // cout << "size " << size << endl;

    // for (int i = 0; i < size; i++) {
    //     cout << result[i] << endl;
    // }

    return 0;
}
