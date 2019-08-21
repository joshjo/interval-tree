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

    void expand(const Interval & other) {
        if (other.left < left) {
            left = other.left;
        }
        if (right < other.right) {
            right = other.right;
        }
    }

    bool includes(Interval & other) {
        return (left < other.left && right > other.right);
    }

    bool intersects(Interval & other) {
        // cout << "(*this) <= other   " << ((*this) <= other) << endl;
        // cout << "!((*this) < other) " << (!((*this) < other)) << endl;
        // cout << "(*this) >= other   " << ((*this) >= other) << endl;
        // cout << "!((*this) > other) " << (!((*this) > other)) << endl;

        return (((*this) <= other && !((*this) < other)) || ((*this) >= other && !((*this) > other)));
    }

    bool operator < (const Interval & other) {
        return (right < other.left);
    }

    bool operator <= (const Interval & other) {
        // Totally at left
        if ((*this) < other) {
            return true;
        }
        // Partial at left
        if (this->left <= other.left && this->right < other.right) {
            return true;
        }
        // Totally at right
        if (this->left > other.right) {
            return false;
        }
        // Partial at right
        if (this->left >= other.left && this->right > other.right) {
            return false;
        }
        int left_distance = abs(other.left - left);
        int right_distance = abs(other.right - right);
        return left_distance <= right_distance;
    }

    bool operator > (const Interval & other) {
        return (left > other.right);
    }

    bool operator >= (const Interval & other) {
        // Totally at right
        if (this->left > other.right) {
            return true;
        }
        // Partial at right
        if (this->left >= other.left && this->right > other.right) {
            return true;
        }
        // Totally at left
        if ((*this) < other) {
            return false;
        }
        // Partial at left
        if (this->left <= other.left && this->right < other.right) {
            return false;
        }
        int left_distance = abs(other.left - left);
        int right_distance = abs(other.right - right);
        return right_distance <= left_distance;
    }

    bool operator == (const Interval & other) {
        return (left == other.left) && (right == other.right);
    }

    void split(Interval & a, Interval & b) {
        T middle = (right - left) / 2;
        a = Interval(left, left + middle);
        b = Interval(left + middle, right);
    }

    void slice_right(Interval & other){
        if (right > other.left && right < other.right) {
            right = other.left;
        }
    }

    void slice_left(Interval & other){
        if (left < other.right && left > other.left) {
            left = other.right;
        }
    }

    void splice(T size, vector<Interval<T> > & arr) {
        if (distance() <= size) {
            Interval<T> tmp (left, right);
            arr.push_back(tmp);
        }
        else {
            T x = left;
            while ((right - x) > size) {
                Interval<T> tmp (x, x + size);
                arr.push_back(tmp);
                x += size;
            }
            Interval<T> tmp (x, right);
            arr.push_back(tmp);
        }
    }

    friend ostream & operator << (ostream &out, const Interval & i) {
        out << '(' << i.left << ',' << i.right << ')';
        return out;
    }

    T left, right;
};


#endif // INTERVAL_H
