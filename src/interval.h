#ifndef INTERVAL_H
#define INTERVAL_H
#include "includes.h"

#define MIDDLE 0
#define LEFT 1
#define RIGHT 2


using namespace std;


template <class T>
class Interval {
public:

    Interval() {
        left = 0;
        right = 0;
    }

    Interval(T a, T b) {
        if (a > b) {
            swap(a, b);
        }
        this->left = a;
        this->right = b;
    }

    bool is_interval() {
        return left != right;
    }

    T distance() {
        return right - left;
    }

    T distance(Interval<T> other) {
        return max(
            abs(left - other.right),
            abs(right - other.left)
        );
    }

    T get_location(Interval<T> other) {
        if (other.left < left) {
            return LEFT;
        } else if (right < other.left) {
            return RIGHT;
        }
        return MIDDLE;
    }

    friend ostream & operator << (ostream &out, const Interval & i) {
        out << '(' << i.left << ',' << i.right << ')';
        return out;
    }

    T left, right;
};


#endif // INTERVAL_H
