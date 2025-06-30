import time
from generators import *
from wiedemann import wiedemann

class BlackBox: 
    def __init__(self, matrix): 
        self.__matrix = matrix
    def prod(self, vector):
        return self.__matrix * vector
    def get_matrix(self):
        return self.__matrix

def main():
    A, b, dim, field = generate_linear_system()
    bbox_A = BlackBox(A)
    start = time.time()
    x = wiedemann(bbox_A, b, dim, field)
    end = time.time()
    print(f"Finished Wiedemann in {end - start:.3f}s")
    return True

if __name__ == '__main__':
    i = 0
    failed = 0
    while failed == 0 and i < 30:
        i += 1
        try:
            print(f'Case {i}...', end=' ')
            main()
            print('Passed')
        except Exception as e:
            print(f'Failed: {e}')
            failed += 1
    print(f'Failed {failed} cases')
