#!/usr/bin/env python

"""
Implementing same algorithms in python
for prototyping and testing
"""

import numpy as np
import random

from pprint import pprint

def gen_matrix(len):
    matrix = [[random.random() for _ in range(len)] for _ in range(len)]
    for i in range(len):
        matrix[i][i] += len
    return matrix

def gen_vector(len):
    return [random.random() for _ in range(len)]

# Use numpy whenever possible
# mat = np.matrix(gen_matrix(10))

def solve(L, y):
    "Return x such that L*x = y where L is triangular"
    x = [None]*len(L)
    for i in range(len(x)):
        before = sum(L[i][j]*x[j] for j in range(i))
        x[i] = float(y[i] - before) / L[i][i]
    return x

def gen_tri_matrix(len):
    "Generates a random triangular matrix of size len*len"
    return [[random.randrange(1,100) for i in range(j)] for j in range(1, len+1)]

def gen_int_vector(len):
    return [random.randrange(1, 10) for i in range(len)]

tri_l = [[1, 0, 0], [2, 1, 0], [3, 2, 1]]
tri_y = [1, 1, 1]

print solve(tri_l, tri_y)

rtri = gen_tri_matrix(100)
vtri = gen_int_vector(100)
print rtri
pprint(solve(rtri, vtri))
