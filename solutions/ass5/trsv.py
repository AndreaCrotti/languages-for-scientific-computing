#!/usr/bin/env python

"""
Implementing same algorithms in python
for prototyping and testing
"""

import numpy as np
import random

def gen_matrix(len):
    matrix = [[random.random() for _ in range(len)] for _ in range(len)]
    for i in range(len):
        matrix[i][i] += len
    return matrix

def gen_vector(len):
    return [random.random() for _ in range(len)]

mat = np.matrix(gen_matrix(10))
