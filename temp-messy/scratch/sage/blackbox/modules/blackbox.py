class BlackBox: 
    def __init__(self, matrix): 
        self.__matrix = matrix.sparse_matrix()
    def prod(self, vector):
        return self.__matrix * vector