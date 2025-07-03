import sys
import os
modules_path = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'modules'))
if modules_path not in sys.path:
    sys.path.insert(0, modules_path)
from generators import *
from wiedemann import *
from random import random

def test_random_matrices(num_tests):
    i = 0
    failed = 0
    while i < num_tests:
        i += 1
        try:
            print('---')
            print(f'Case {i}...', end=' ')
            sparsity = 0.85 + (0.95 - 0.85) * random() # Random sparsity in [0.85, 0.95]
            A, b, dim, field = generate_linear_system(sparsity = sparsity)
            wiedemann_timed_test(A, b, dim, field)
        except Exception as e:
            print(f'Failed: {e}')
            failed += 1
    print(f'Failed {failed} cases')


if __name__ == '__main__':
    test_random_matrices(30)

