This project uses C++11 to compile just run:

```
g++ main.cpp -o main.out --std=c++11
```

And then run the project with:

```
./main.out
```

You will see something like:

```
*** ADDITIONAL STRATEGY ***
insert ops   : 0
transfer ops : 0
share ops    : 0
merge ops    : 0
insert time  : 0
transfer time: 0
share time   : 0
merge time   : 0
total time: 0.019995

*** EAGER STRATEGY ***
size: 15
indexed      : 24796
insert ops   : 49546
transfer ops : 60
share ops    : 18
merge ops    : 32
insert time  : 0.011934
transfer time: 0.000444
share time   : 9.6e-05
merge time   : 0.000814
total time: 0.034851

*** LAZY STRATEGY ***
size: 15
indexed      : 24808
insert ops   : 24773
transfer ops : 30
share ops    : 9
merge ops    : 16
insert time  : 0.009711
transfer time: 3.8e-05
share time   : 8e-05
merge time   : 0.000395
total time: 0.031687
```
