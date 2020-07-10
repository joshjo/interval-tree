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
insert ops   : 24773
transfer ops : 30
share ops    : 9
merge ops    : 16
insert time  : 0.0008
transfer time: 1e-06
share time   : 1e-06
merge time   : 2e-06
total time: 0.030448

*** EAGER STRATEGY ***
size: 15
indexed      : 24796
insert ops   : 49546
transfer ops : 60
share ops    : 18
merge ops    : 32
insert time  : 0.011666
transfer time: 0.000339
share time   : 9.5e-05
merge time   : 0.000803
total time: 0.033029

*** EAGER STRATEGY ***
size: 15
indexed      : 24808
insert ops   : 24773
transfer ops : 30
share ops    : 9
merge ops    : 16
insert time  : 0.010109
transfer time: 5.7e-05
share time   : 7e-05
merge time   : 0.000437
total time: 0.031926
```
