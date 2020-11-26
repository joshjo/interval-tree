import numpy as np
import math
import pydot

from pprint import pprint


def get_median(arr):
    len_arr = len(arr)
    half = int(len_arr / 2)
    if len_arr % 2:
        return arr[half]
    return (arr[half] + arr[half - 1]) / 2



class CenteredIntervalTree:

    def build(self, intervals):
        tree = {}
        self.intervals = intervals
        self.split(intervals, tree)
        pprint(tree)

    def split(self, intervals, tree):
        flat = [item for interval in intervals for item in interval]
        flat.sort()
        len_flat = len(flat)
        if len_flat <= 1:
            tree['center'] = {}
            return
        median = np.median(flat)
        lefts = []
        rights = []
        centers = []
        for elem in intervals:
            if elem[-1] < median:
                lefts.append(elem)
            elif elem[0] > median:
                rights.append(elem)
            else:
                centers.append({
                    'interval': elem,
                    'index': self.intervals.index(elem) + 1,
                })
        tree['aode'] = median
        tree['center'] = centers
        tree[f'left'] = {}
        tree[f'right'] = {}

        self.split(lefts, tree[f'left'])
        self.split(rights, tree[f'right'])


class SegmentTree:
    def build(self, intervals):
        flat = list(
            set([item for interval in intervals for item in interval]))
        flat.append(-math.inf)
        flat.append(math.inf)
        flat.sort()
        print('flat', flat, len(flat))
        tree = {}
        self.split(flat, tree)
        pprint(tree)

    def split(self, flat, tree, level=1):
        len_flat = len(flat)
        if len_flat <= 1:
            tree['zode'] = flat
            return
        half = math.ceil(len_flat / 2)
        tree['left'] = {}
        tree['right'] = {}
        self.split(flat[:half], tree['left'], level + 1)
        self.split(flat[half:], tree['right'], level + 1)
        tree['zode'] = [
            tree['left']['zode'][0],
            tree['right']['zode'][-1],
        ]


if __name__ == '__main__':
    intervals = [
        (750, 830),
        # (720, 790),
        (830, 860),
        # (570, 630),
        (520, 600),
        (540, 550),
        (530, 620),
        # (330, 340),
        (310, 360),
        (300, 330),
        (50, 120),
        # (100, 150),
        (90, 140),
        (970, 980),
        # (920, 950),
        (950, 970),
        (630, 1000),
    ]

    # segment_tree = SegmentTree()
    # segment_tree.build(intervals)
    # interval_tree = CenteredIntervalTree()
    # interval_tree.build(intervals)

    # for index, i in enumerate(intervals):
    #     print(index + 1, i)
    #     # print(f'intervals.push_back(Tinterval({i[0]}, {i[1]}));')
    #     # print(f'Segment({i[0]}, {i[1]}),')
    # # for a, b in intervals:
