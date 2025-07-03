import time
import sys
import os
modules_path = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'modules'))
if modules_path not in sys.path:
    sys.path.insert(0, modules_path)
from generators import *
from wiedemann import wiedemann

# Blackbox class to imitate behavior of a black box
class BlackBox: 
    def __init__(self, matrix): 
        self.__matrix = matrix
    def prod(self, vector):
        return self.__matrix * vector
    def get_matrix(self):
        return self.__matrix

# Main function
def main():    
    A, b, dim, field = generate_linear_system() # Generate a random sequence
    bbox_A = BlackBox(A)
    start = time.time()
    x, attempts = wiedemann(bbox_A, b, dim, field)
    end = time.time()
    print(f"Finished Wiedemann in {end - start:.3f}s ({attempts} attempts)")
    if x == A.solve_right(b):
        print('Solution verified against Sage built-in solver')
    else: 
        raise Exception('Solution different from Sage built-in solver')

if __name__ == '__main__':
    i = 0
    failed = 0
    while failed == 0 and i <= 300:
        i += 1
        try:
            print(f'Case {i}...', end=' ')
            main()
            print('Passed')
        except Exception as e:
            print(f'Failed: {e}')
            failed += 1
    print(f'Failed {failed} cases')
