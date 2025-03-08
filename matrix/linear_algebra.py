import math

# Complexidade Temporal O(n)
# A complexidade temporal mede o tempo que um algoritmo leva para executar em função do tamanho da entrada. 
# A notação O(n) significa que o tempo de execução cresce linearmente com o tamanho da entrada.


# Complexidade Espacial O(n)
# A complexidade espacial mede o espaço de memória que um algoritmo usa em função do tamanho da entrada. 
# A notação O(n) significa que o espaço de memória usado cresce linearmente com o tamanho da entrada.

class Vector:
    """
    Classe para representar vetores e realizar operações de álgebra linear.
    """
    def __init__(self, data):
        """
        Inicializa um vetor com os dados fornecidos.
        
        Args:
            data: Lista de valores que compõem o vetor
        """
        self.data = list(data)
        self.size = len(data)
    
    @classmethod
    def from_list(cls, data):
        """
        Cria um vetor a partir de uma lista.
        
        Args:
            data: Lista de valores
            
        Returns:
            Um novo objeto Vector
        """
        return cls(data)
    
    def __getitem__(self, idx):
        """
        Permite aceder a elementos do vetor usando a notação de índice.
        
        Args:
            idx: Índice do elemento a aceder
            
        Returns:
            O valor na posição idx
        """
        return self.data[idx]
    
    def __setitem__(self, idx, value):
        """
        Permite definir valores no vetor usando a notação de índice.
        
        Args:
            idx: Índice do elemento a modificar
            value: Novo valor a atribuir
        """
        self.data[idx] = value
    
    def __len__(self):
        """
        Retorna o tamanho do vetor.
        
        Returns:
            Número de elementos no vetor
        """
        return self.size
    
    def __str__(self):
        """
        Representação do vetor como string.
        
        Returns:
            String formatada do vetor
        """
        #return "\n".join([f"[{x}]" for x in self.data])
        return f"[{', '.join(str(x) for x in self.data)}]"
    
    def __eq__(self, other):
        """
        Verifica se dois vetores são iguais (para fins de teste).
        
        Args:
            other: Outro vetor para comparar
            
        Returns:
            True se os vetores forem iguais, False caso contrário
        """
        if not isinstance(other, Vector) or len(self) != len(other):
            return False
        
        for i in range(len(self)):
            if abs(self.data[i] - other.data[i]) > 1e-6:
                return False
        
        return True
    
    # Exercise 00: Add, Subtract, Scale
    def add(self, v):
        """
        Adiciona outro vetor a este vetor.
        
        Complexidade temporal: O(n), onde n é o tamanho do vetor
        Complexidade espacial: O(1), modificação in-place
        
        Args:
            v: Vetor a adicionar
            
        Raises:
            ValueError: Se os vetores tiverem tamanhos diferentes
        """
        if len(v) != self.size:
            raise ValueError("Os vetores devem ter o mesmo tamanho")
        
        for i in range(self.size):
            self.data[i] += v[i]
    
    def sub(self, v):
        """
        Subtrai outro vetor deste vetor.
        
        Complexidade temporal: O(n), onde n é o tamanho do vetor
        Complexidade espacial: O(1), modificação in-place
        
        Args:
            v: Vetor a subtrair
            
        Raises:
            ValueError: Se os vetores tiverem tamanhos diferentes
        """
        if len(v) != self.size:
            raise ValueError("Os vetores devem ter o mesmo tamanho")
        
        for i in range(self.size):
            self.data[i] -= v[i]
    
    def scl(self, a):
        """
        Multiplica este vetor por um escalar.
        
        Complexidade temporal: O(n), onde n é o tamanho do vetor
        Complexidade espacial: O(1), modificação in-place
        
        Args:
            a: Valor escalar para multiplicar o vetor
        """
        for i in range(self.size):
            self.data[i] *= a

    
    #Exercise 03 - Dot product
    def dot(self, v):
        """
        Calcula o produto escalar (dot product) entre este vetor e outro.
        
        Complexidade temporal: O(n), onde n é o tamanho dos vetores
        Complexidade espacial: O(1), apenas um valor escalar é calculado
        
        Args:
            v: Vetor com o qual calcular o produto escalar
            
        Returns:
            Valor escalar resultante do produto escalar
            
        Raises:
            ValueError: Se os vetores tiverem tamanhos diferentes
        """
        if len(self) != len(v):
            raise ValueError("Os vetores devem ter o mesmo tamanho")
        
        result = 0.0
        for i in range(self.size):
            result += self.data[i] * v[i]
        
        return result


    # Exercise 04 - Norm
    def norm_1(self):
        """
        Calcula a norma-1 (norma de Manhattan/Táxi) deste vetor.
        
        Complexidade temporal: O(n), onde n é o tamanho do vetor
        Complexidade espacial: O(1), apenas um valor escalar é calculado
        
        Returns:
            A soma dos valores absolutos de todas as componentes do vetor
        """
        return sum(abs(x) for x in self.data)

    def norm(self):
        """
        Calcula a norma-2 (norma Euclidiana) deste vetor.
        
        Complexidade temporal: O(n), onde n é o tamanho do vetor
        Complexidade espacial: O(1), apenas um valor escalar é calculado
        
        Returns:
            A raiz quadrada da soma dos quadrados das componentes do vetor
        """
        return math.sqrt(sum(x * x for x in self.data))

    def norm_inf(self):
        """
        Calcula a norma-infinito (norma do supremo) deste vetor.
        
        Complexidade temporal: O(n), onde n é o tamanho do vetor
        Complexidade espacial: O(1), apenas um valor escalar é calculado
        
        Returns:
            O valor absoluto máximo entre todas as componentes do vetor
        """
        if not self.data:
            return 0.0
        return max(abs(x) for x in self.data)

 

class Matrix:
    """
    Classe para representar matrizes e realizar operações de álgebra linear.
    """
    def __init__(self, data):
        """
        Inicializa uma matrix com os dados fornecidos.
        
        Args:
            data: Lista de listas representando a matrix
        """
        self.data = [list(row) for row in data]
        self.rows = len(data)
        self.cols = len(data[0]) if self.rows > 0 else 0
    
    @classmethod
    def from_list(cls, data):
        """
        Cria uma matrix a partir de uma lista de listas.
        
        Args:
            data: Lista de listas representando a matrix
            
        Returns:
            Um novo objeto Matrix
        """
        return cls(data)
    
    def __str__(self):
        """
        Representação da matrix como string.
        
        Returns:
            String formatada da matrix
        """
        #return "\n".join([f"[{', '.join(str(x) for x in row)}]" for row in self.data]) #vova linha
        return " ".join([f"[{', '.join(str(x) for x in row)}]" for row in self.data])
    
    def __eq__(self, other):
        """
        Verifica se duas matrizes são iguais (para fins de teste).
        
        Args:
            other: Outra matrix para comparar
            
        Returns:
            True se as matrizes forem iguais, False caso contrário
        """
        if not isinstance(other, Matrix) or self.rows != other.rows or self.cols != other.cols:
            return False
        
        for i in range(self.rows):
            for j in range(self.cols):
                if abs(self.data[i][j] - other.data[i][j]) > 1e-6:
                    return False
        
        return True
    
    # Exercise 00: Add, Subtract, Scale
    def add(self, m):
        """
        Adiciona outra matrix a esta matrix.
        
        Complexidade temporal: O(n), onde n é o número total de elementos na matrix
        Complexidade espacial: O(1), modificação in-place
        
        Args:
            m: Matrix a adicionar
            
        Raises:
            ValueError: Se as matrizes tiverem dimensões diferentes
        """
        if self.rows != m.rows or self.cols != m.cols:
            raise ValueError("As matrizes devem ter as mesmas dimensões")
        
        for i in range(self.rows):
            for j in range(self.cols):
                self.data[i][j] += m.data[i][j]
    
    def sub(self, m):
        """
        Subtrai outra matrix desta matrix.
        
        Complexidade temporal: O(n), onde n é o número total de elementos na matrix
        Complexidade espacial: O(1), modificação in-place
        
        Args:
            m: Matrix a subtrair
            
        Raises:
            ValueError: Se as matrizes tiverem dimensões diferentes
        """
        if self.rows != m.rows or self.cols != m.cols:
            raise ValueError("As matrizes devem ter as mesmas dimensões")
        
        for i in range(self.rows):
            for j in range(self.cols):
                self.data[i][j] -= m.data[i][j]
    
    def scl(self, a):
        """
        Multiplica esta matrix por um escalar.
        
        Complexidade temporal: O(n), onde n é o número total de elementos na matrix
        Complexidade espacial: O(1), modificação in-place
        
        Args:
            a: Valor escalar para multiplicar a matrix
        """
        for i in range(self.rows):
            for j in range(self.cols):
                self.data[i][j] *= a
    
    # Exercise 07: Linear map, Matrixmultiplication
 
    def mul_vec(self, vec):
        """
        Multiplica esta matrix por um vetor.
        
        Complexidade temporal: O(n*m), onde n é o número de linhas e m é o número de colunas
        Complexidade espacial: O(n), para armazenar o vetor resultante
        
        Args:
            vec: Vetor a ser multiplicado pela matrix
            
        Returns:
            Um novo vetor resultante da multiplicação da matrix pelo vetor
            
        Raises:
            ValueError: Se o número de colunas da matrix não for igual ao tamanho do vetor
        """
        if self.cols != len(vec):
            raise ValueError("O número de colunas da matrix deve ser igual ao tamanho do vetor")
        
        result = Vector([0.0] * self.rows)
        for i in range(self.rows):
            for j in range(self.cols):
                result.data[i] += self.data[i][j] * vec[j]
        
        return result

    def mul_mat(self, mat):
        """
        Multiplica esta matrix por outra matrix.
        
        Complexidade temporal: O(n*m*p), onde n é o número de linhas da primeira matrix,
                            m é o número de colunas da primeira matrix, e
                            p é o número de colunas da segunda matrix
        Complexidade espacial: O(n*p), para armazenar a matrix resultante
        
        Args:
            mat: Matrix a ser multiplicada pela matrix atual
            
        Returns:
            Uma nova matrix resultante da multiplicação das duas matrizes
            
        Raises:
            ValueError: Se o número de colunas da primeira matrix não for igual ao número de linhas da segunda
        """
        if self.cols != mat.rows:
            raise ValueError("O número de colunas da primeira matrix deve ser igual ao número de linhas da segunda")
        
        result = Matrix([[0.0 for _ in range(mat.cols)] for _ in range(self.rows)])
        for i in range(self.rows):
            for j in range(mat.cols):
                for k in range(self.cols):
                    result.data[i][j] += self.data[i][k] * mat.data[k][j]
        
        return result


    # Exercise 08: Trace
    def trace(self):
        """
        Calcula o traço da matrix (soma dos elementos da diagonal principal).
        
        Complexidade temporal: O(n), onde n é a dimensão da matrix
        Complexidade espacial: O(1), apenas um valor escalar é calculado
        
        Returns:
            O traço da matrix (soma dos elementos na diagonal principal)
            
        Raises:
            ValueError: Se a matrix não for quadrada
        """
        if self.rows != self.cols:
            raise ValueError("O traço só é definido para matrizes quadradas")
        
        result = 0
        for i in range(self.rows):
            result += self.data[i][i]
        
        return result
    
    # Exercise 09:  Transpose
    def transpose(self):
        """
        Calcula a matrix transposta.
        
        Complexidade temporal: O(nm), onde n é o número de linhas e m é o número de colunas
        Complexidade espacial: O(nm), para armazenar a matrix resultante
        
        Returns:
            Uma nova matrix que é a transposta da matrix atual
        """
        # Criar uma nova matrix com dimensões invertidas
        result = Matrix([[0.0 for _ in range(self.rows)] for _ in range(self.cols)])
        
        # Preencher a matrix transposta
        for i in range(self.rows):
            for j in range(self.cols):
                result.data[j][i] = self.data[i][j]
        
        return result
    
    # Exercise 10:   Row echelon
    def row_echelon(self):
        """
        Calcula a forma escalonada reduzida da matrix (RREF).
        
        Returns:
            A forma escalonada reduzida da matrix
        """
        # Fazer uma cópia para não modificar a original
        result = Matrix([row[:] for row in self.data])
        m = result.rows
        n = result.cols
        
        # Para cada linha
        r = 0
        for c in range(n):
            # Encontrar a linha com o valor máximo na coluna c, a partir da linha r
            max_r = r
            for i in range(r + 1, m):
                if abs(result.data[i][c]) > abs(result.data[max_r][c]):
                    max_r = i
                    
            # Se a coluna é toda zero, vá para a próxima
            if abs(result.data[max_r][c]) < 1e-10:
                continue
                
            # Trocar as linhas r e max_r
            result.data[r], result.data[max_r] = result.data[max_r], result.data[r]
            
            # Normalizar a linha r
            pivot = result.data[r][c]
            for j in range(n):
                result.data[r][j] /= pivot
                
            # Eliminar outras linhas
            for i in range(m):
                if i != r:
                    factor = result.data[i][c]
                    for j in range(n):
                        result.data[i][j] -= factor * result.data[r][j]
                        
            r += 1
            if r == m:
                break
                
        return result
    
    # Exercise 11:  Determinant
    def determinant(self):
        """
        Calcula o determinante da matrix.

        
        Complexidade temporal: O(n³), onde n é a dimensão da matrix
        Complexidade espacial: O(n²), para armazenar cópias de trabalho
        
        Returns:
            O determinante da matrix
            
        Raises:
            ValueError: Se a matrix não for quadrada
        """
        if self.rows != self.cols:
            raise ValueError("O determinante só é definido para matrizes quadradas")
        
        n = self.rows
        
        # Casos especiais para matrizes pequenas (mais eficiente)
        if n == 1:
            return self.data[0][0]
        
        if n == 2:
            return self.data[0][0] * self.data[1][1] - self.data[0][1] * self.data[1][0]
        
        if n == 3:
            a, b, c = self.data[0][0], self.data[0][1], self.data[0][2]
            d, e, f = self.data[1][0], self.data[1][1], self.data[1][2]
            g, h, i = self.data[2][0], self.data[2][1], self.data[2][2]
            
            return a*e*i + b*f*g + c*d*h - c*e*g - b*d*i - a*f*h
        
        # Para matrizes maiores, usar eliminação gaussiana
        # Fazemos uma cópia da matrix para não modificar a original
        temp = Matrix([row[:] for row in self.data])
        det_sign = 1.0  # Para rastrear as trocas de linha
        
        # Implementando eliminação gaussiana
        for i in range(n):
            # Encontrar o pivô máximo em valor absoluto na coluna atual
            max_val = abs(temp.data[i][i])
            max_row = i
            
            for j in range(i + 1, n):
                if abs(temp.data[j][i]) > max_val:
                    max_val = abs(temp.data[j][i])
                    max_row = j
            
            # Se o máximo for zero, o determinante é zero
            if max_val < 1e-10:
                return 0.0
            
            # Troca de linhas se necessário
            if max_row != i:
                temp.data[i], temp.data[max_row] = temp.data[max_row], temp.data[i]
                det_sign *= -1  # Cada troca de linha muda o sinal do determinante
            
            # Eliminação gaussiana
            for j in range(i + 1, n):
                factor = temp.data[j][i] / temp.data[i][i]
                
                for k in range(i, n):
                    temp.data[j][k] -= factor * temp.data[i][k]
        
        # O determinante é o produto dos elementos diagonais
        det = det_sign
        for i in range(n):
            det *= temp.data[i][i]

        # no espaço vetorial, sendo det(A) = 0 entao não podemos inverter a transformação. OBS. podmeos ver na proxima function
        #O determinante de uma matrix associada a uma transformação linear fornece uma medida de como a transformação altera volumes (ou áreas) 
        # Se ∣det⁡(A)∣>1∣det(A)∣>1: A transformação expande volumes.
        # Se 0<∣det⁡(A)∣<10<∣det(A)∣<1: A transformação contrai volumes.
        # Se det⁡(A)=0det(A)=0: O volume é reduzido a zero, indicando que a transformação colapsa o espaço em uma dimensão menor 
        # (por exemplo, transformando um plano em uma linha ou um espaço 3D em um plano).
        # Se det⁡(A)<0det(A)<0: Além de afetar o volume, a transformação inverte a orientação (espelha o espaço).

        
        return det    
    

    # Exercise 12:  Inverse
    def inverse(self):
        """
        Calcula a matrix inversa usando o método da matrix aumentada e a forma escalonada.
        
        Complexidade temporal: O(n³), onde n é a dimensão da matrix
        Complexidade espacial: O(n²), para armazenar a matrix aumentada
        
        Returns:
            A matrix inversa
            
        Raises:
            ValueError: Se a matrix não for quadrada ou for singular
        """
        if self.rows != self.cols:
            raise ValueError("A matrix inversa só é definida para matrizes quadradas")
        
        n = self.rows
        
        # Verificar se a matrix é singular usando o determinante
        if abs(self.determinant()) < 1e-10:
            raise ValueError("A matrix é singular e não possui inversa")
        
        # Criar uma matrix aumentada [A|I]
        augmented_data = []
        for i in range(n):
            row = self.data[i].copy()
            # Adicionar a matrix identidade à direita
            for j in range(n):
                row.append(1.0 if i == j else 0.0)
            augmented_data.append(row)
        
        # Criar a matrix aumentada
        augmented_matrix = Matrix(augmented_data)
        
        # Aplicar a forma escalonada à matrix aumentada
        ref = augmented_matrix.row_echelon()
        
        # Extrair a matrix inversa (parte direita da matrix aumentada)
        inverse_data = []
        for i in range(n):
            inverse_row = []
            for j in range(n, 2 * n):
                inverse_row.append(ref.data[i][j])
            inverse_data.append(inverse_row)
        
        return Matrix(inverse_data)

    # Exercise 13:  Trace
    def rank(self):
        """
        O posto de uma matrix é o número máximo de linhas (ou colunas) linearmente independentes na matrix
        é a dimensão do espaço vetorial gerado pelas linhas (ou colunas) da matrix.
 
        
        Complexidade temporal: O(n³), onde n é a dimensão máxima da matrix
        Complexidade espacial: O(N/A)
        
        Returns:
            O posto da matrix (um número inteiro)
        """
        # Obtém a forma escalonada da matrix
        ref = self.row_echelon()
        
        # Conta o número de linhas não-nulas
        rank = 0
        for i in range(ref.rows):
            is_zero_row = True
            for j in range(ref.cols):
                if abs(ref.data[i][j]) > 1e-10:  # Tolerância para erros de ponto flutuante : elipson
                    is_zero_row = False
                    break
            if not is_zero_row:
                rank += 1
        
        return rank    