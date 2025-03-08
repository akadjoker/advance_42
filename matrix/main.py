
from linear_algebra import Vector, Matrix
from testes import Testes, Cores
from utils import linear_combination, lerp, vector_lerp, matrix_lerp, angle_cos, cross_product

#ALGUNS TERMOS

# Base Canónica:
# A base canónica de um espaço vetorial Rⁿ (espaço de n dimensões com números reais) é formada pelos vetores 
# unitários que apontam nas direções dos eixos coordenados. Estes vetores são frequentemente representados por e₁, e₂, ..., eₙ.

# Vetores Arbitrários:
# Vetores arbitrários são simplesmente vetores quaisquer, sem propriedades ou características específicas. 
# O termo "arbitrário" indica que os vetores foram escolhidos sem nenhum critério particular - são apenas exemplos genéricos.


# Vetores Ortogonais:
# Vetores ortogonais são vetores que são perpendiculares entre si. Em termos matemáticos, dois vetores são ortogonais se e somente se o 
# seu produto escalar é zero.


# Vetores Unitários:
#Um vetor unitário é um vetor que tem comprimento (ou norma) igual a 1. Em termos matemáticos, se u é um vetor unitário, 
#então ||u|| = 1, onde ||u|| representa a norma euclidiana (norma-2) do vetor.

# Vetores Proporcionais:
#Os vetores proporcionais são vetores que têm a mesma direção mas possivelmente magnitudes (comprimentos) diferentes. 
# Matematicamente, dois vetores u e v são proporcionais se existe um escalar λ ≠ 0 tal que:


def test_exercise_00():
    """Testa o Exercise 00: Add, Subtract, Scale."""
    testes = Testes()
    
    # Teste de adição de vetores
    testes.iniciar_grupo("Vector Addition")
    
    u = Vector.from_list([2.0, 3.0])
    v = Vector.from_list([5.0, 7.0])
    
    u_original = Vector.from_list([2.0, 3.0])
    resultado = Vector.from_list([2.0, 3.0])
    resultado.add(v)
    esperado = Vector.from_list([7.0, 10.0])
    
    testes.verificar_vetores("Adição de dois vetores", resultado, esperado)
    testes.verificar_vetores("Vector original não foi modificado", u, u_original)
    
    # Teste de erro para vetores de tamanhos diferentes
    try:
        resultado.add(Vector.from_list([1.0, 2.0, 3.0]))
        testes.verificar("Deve lançar erro para vetores de tamanhos diferentes", False, True)
    except ValueError:
        testes.verificar("Deve lançar erro para vetores de tamanhos diferentes", True, True)
    
    testes.finalizar_grupo()
    
    # Teste de subtração de vetores
    testes.iniciar_grupo("Vector Subtraction")
    
    resultado = Vector.from_list([2.0, 3.0])
    resultado.sub(v)
    esperado = Vector.from_list([-3.0, -4.0])
    
    testes.verificar_vetores("Subtração de dois vetores", resultado, esperado)
    
    # Teste de erro para vetores de tamanhos diferentes
    try:
        resultado.sub(Vector.from_list([1.0, 2.0, 3.0]))
        testes.verificar("Deve lançar erro para vetores de tamanhos diferentes", False, True)
    except ValueError:
        testes.verificar("Deve lançar erro para vetores de tamanhos diferentes", True, True)
    
    testes.finalizar_grupo()
    
    # Teste de escala de vetores
    testes.iniciar_grupo("Vector Scaling")
    
    resultado = Vector.from_list([2.0, 3.0])
    resultado.scl(2.0)
    esperado = Vector.from_list([4.0, 6.0])
    
    testes.verificar_vetores("Escala de um vetor por 2", resultado, esperado)
    
    resultado = Vector.from_list([4.0, 6.0])
    resultado.scl(0.5)
    esperado = Vector.from_list([2.0, 3.0])
    
    testes.verificar_vetores("Escala de um vetor por 0.5", resultado, esperado)
    
    testes.finalizar_grupo()
    
    # Teste de adição de matrizes
    testes.iniciar_grupo("Matrix Addition")
    
    u = Matrix.from_list([
        [1.0, 2.0],
        [3.0, 4.0]
    ])
    v = Matrix.from_list([
        [7.0, 4.0],
        [-2.0, 2.0]
    ])
    
    resultado = Matrix.from_list([
        [1.0, 2.0],
        [3.0, 4.0]
    ])
    resultado.add(v)
    esperado = Matrix.from_list([
        [8.0, 6.0],
        [1.0, 6.0]
    ])
    
    testes.verificar_matrizes("Adição de duas matrizes", resultado, esperado)
    
    # Teste de erro para matrizes de dimensões diferentes
    try:
        resultado.add(Matrix.from_list([
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0]
        ]))
        testes.verificar("Deve lançar erro para matrizes de dimensões diferentes", False, True)
    except ValueError:
        testes.verificar("Deve lançar erro para matrizes de dimensões diferentes", True, True)
    
    testes.finalizar_grupo()
    
    # Teste de subtração de matrizes
    testes.iniciar_grupo("Matrix Subtraction")
    
    resultado = Matrix.from_list([
        [1.0, 2.0],
        [3.0, 4.0]
    ])
    resultado.sub(v)
    esperado = Matrix.from_list([
        [-6.0, -2.0],
        [5.0, 2.0]
    ])
    
    testes.verificar_matrizes("Subtração de duas matrizes", resultado, esperado)
    
    # Teste de erro para matrizes de dimensões diferentes
    try:
        resultado.sub(Matrix.from_list([
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0]
        ]))
        testes.verificar("Deve lançar erro para matrizes de dimensões diferentes", False, True)
    except ValueError:
        testes.verificar("Deve lançar erro para matrizes de dimensões diferentes", True, True)
    
    testes.finalizar_grupo()
    
    # Teste de escala de matrizes
    testes.iniciar_grupo("Matrix Scaling")
    
    resultado = Matrix.from_list([
        [1.0, 2.0],
        [3.0, 4.0]
    ])
    resultado.scl(2.0)
    esperado = Matrix.from_list([
        [2.0, 4.0],
        [6.0, 8.0]
    ])
    
    testes.verificar_matrizes("Escala de uma matrix por 2", resultado, esperado)
    
    resultado = Matrix.from_list([
        [2.0, 4.0],
        [6.0, 8.0]
    ])
    resultado.scl(0.5)
    esperado = Matrix.from_list([
        [1.0, 2.0],
        [3.0, 4.0]
    ])
    
    testes.verificar_matrizes("Escala de uma matrix por 0.5", resultado, esperado)
    
    testes.finalizar_grupo()
    

    testes.mostrar_resultados()


def test_exercise_01():
    """Testa o Exercise 01: Linear Combination."""
    testes = Testes()
    
    testes.iniciar_grupo("Linear Combination")
    
    # Teste 1: Base canónica (vetores da base)
    e1 = Vector.from_list([1.0, 0.0, 0.0])
    e2 = Vector.from_list([0.0, 1.0, 0.0])
    e3 = Vector.from_list([0.0, 0.0, 1.0])
    
    resultado = linear_combination([e1, e2, e3], [10.0, -2.0, 0.5])
    esperado = Vector.from_list([10.0, -2.0, 0.5])
    
    testes.verificar_vetores("Combinação linear dos vetores da base canónica", resultado, esperado)
    
    # Teste 2: Vetores arbitrários
    v1 = Vector.from_list([1.0, 2.0, 3.0])
    v2 = Vector.from_list([0.0, 10.0, -100.0])
    
    resultado = linear_combination([v1, v2], [10.0, -2.0])
    esperado = Vector.from_list([10.0, 0.0, 230.0])
    
    testes.verificar_vetores("Combinação linear de vetores arbitrários", resultado, esperado)
    
    # Teste 3: Erro para número diferente de vetores e coeficientes
    try:
        linear_combination([v1, v2], [1.0, 2.0, 3.0])
        testes.verificar("Deve lançar erro para número diferente de vetores e coeficientes", False, True)
    except ValueError:
        testes.verificar("Deve lançar erro para número diferente de vetores e coeficientes", True, True)
    
    # Teste 4: Erro para vetores de tamanhos diferentes
    try:
        linear_combination([v1, Vector.from_list([1.0, 2.0])], [1.0, 2.0])
        testes.verificar("Deve lançar erro para vetores de tamanhos diferentes", False, True)
    except ValueError:
        testes.verificar("Deve lançar erro para vetores de tamanhos diferentes", True, True)
    
    testes.finalizar_grupo()
    

    testes.mostrar_resultados()


def test_exercise_02():
    """Testa o Exercise 02: Linear Interpolation."""
    testes = Testes()
    
    # Teste de interpolação linear entre escalares
    testes.iniciar_grupo("Scalar Linear Interpolation")
    
    testes.verificar_quase_igual("LERP com t=0", lerp(0.0, 1.0, 0.0), 0.0)
    testes.verificar_quase_igual("LERP com t=1", lerp(0.0, 1.0, 1.0), 1.0)
    testes.verificar_quase_igual("LERP com t=0.5", lerp(0.0, 1.0, 0.5), 0.5)
    testes.verificar_quase_igual("LERP com t=0.3 e valores arbitrários", lerp(21.0, 42.0, 0.3), 27.3)
    
    testes.finalizar_grupo()
    
    # Teste de interpolação linear entre vetores
    testes.iniciar_grupo("Vector Linear Interpolation")
    
    u = Vector.from_list([2.0, 1.0])
    v = Vector.from_list([4.0, 2.0])
    
    resultado = vector_lerp(u, v, 0.3)
    esperado = Vector.from_list([2.6, 1.3])
    
    testes.verificar_vetores("LERP entre dois vetores com t=0.3", resultado, esperado)
    
    # Teste de erro para vetores de tamanhos diferentes
    try:
        vector_lerp(u, Vector.from_list([4.0, 2.0, 0.0]), 0.5)
        testes.verificar("Deve lançar erro para vetores de tamanhos diferentes", False, True)
    except ValueError:
        testes.verificar("Deve lançar erro para vetores de tamanhos diferentes", True, True)
    
    testes.finalizar_grupo()
    
    # Teste de interpolação linear entre matrizes
    testes.iniciar_grupo("Matrix Linear Interpolation")
    
    u = Matrix.from_list([
        [2.0, 1.0],
        [3.0, 4.0]
    ])
    v = Matrix.from_list([
        [20.0, 10.0],
        [30.0, 40.0]
    ])
    
    resultado = matrix_lerp(u, v, 0.5)
    esperado = Matrix.from_list([
        [11.0, 5.5],
        [16.5, 22.0]
    ])
    
    testes.verificar_matrizes("LERP entre duas matrizes com t=0.5", resultado, esperado)
    
    # Teste de erro para matrizes de dimensões diferentes
    try:
        matrix_lerp(u, Matrix.from_list([
            [20.0, 10.0, 5.0],
            [30.0, 40.0, 50.0]
        ]), 0.5)
        testes.verificar("Deve lançar erro para matrizes de dimensões diferentes", False, True)
    except ValueError:
        testes.verificar("Deve lançar erro para matrizes de dimensões diferentes", True, True)
    
    testes.finalizar_grupo()
    

    testes.mostrar_resultados()


def test_exercise_03():
    """Testa o Exercise 03: Dot Product."""
    testes = Testes()
    
    testes.iniciar_grupo("Dot Product")
    
    # Teste 1: Produto escalar de vetores nulos
    u = Vector.from_list([0.0, 0.0])
    v = Vector.from_list([1.0, 1.0])
    testes.verificar_quase_igual("Produto escalar com vetor nulo", u.dot(v), 0.0)
    
    # Teste 2: Produto escalar de vetores idênticos
    u = Vector.from_list([1.0, 1.0])
    v = Vector.from_list([1.0, 1.0])
    testes.verificar_quase_igual("Produto escalar de vetores idênticos", u.dot(v), 2.0)
    
    # Teste 3: Produto escalar de vetores arbitrários
    u = Vector.from_list([-1.0, 6.0])
    v = Vector.from_list([3.0, 2.0])
    testes.verificar_quase_igual("Produto escalar de vetores arbitrários", u.dot(v), 9.0, 1e-6)
    
    # Teste 4: Produto escalar de vetores ortogonais
    u = Vector.from_list([1.0, 0.0])
    v = Vector.from_list([0.0, 1.0])
    testes.verificar_quase_igual("Produto escalar de vetores ortogonais", u.dot(v), 0.0)
    
    # Teste 5: Erro para vetores de tamanhos diferentes
    try:
        u = Vector.from_list([1.0, 2.0])
        v = Vector.from_list([3.0, 4.0, 5.0])
        u.dot(v)
        testes.verificar("Deve lançar erro para vetores de tamanhos diferentes", False, True)
    except ValueError:
        testes.verificar("Deve lançar erro para vetores de tamanhos diferentes", True, True)
    
    testes.finalizar_grupo()
    

    testes.mostrar_resultados()    



def test_exercise_04():
    """Testa o Exercise 04: Norm."""
    testes = Testes()
    
    testes.iniciar_grupo("Vector Norms")
    
    # Teste 1: Normas de um vetor nulo
    u = Vector.from_list([0.0, 0.0, 0.0])
    testes.verificar_quase_igual("Norma-1 de um vetor nulo", u.norm_1(), 0.0)
    testes.verificar_quase_igual("Norma-2 de um vetor nulo", u.norm(), 0.0)
    testes.verificar_quase_igual("Norma-inf de um vetor nulo", u.norm_inf(), 0.0)
    
    # Teste 2: Normas de um vetor de valores positivos
    u = Vector.from_list([1.0, 2.0, 3.0])
    testes.verificar_quase_igual("Norma-1 de um vetor positivo", u.norm_1(), 6.0)
    testes.verificar_quase_igual("Norma-2 de um vetor positivo", u.norm(), 3.7416573867739413)
    testes.verificar_quase_igual("Norma-inf de um vetor positivo", u.norm_inf(), 3.0)
    
    # Teste 3: Normas de um vetor com valores negativos
    u = Vector.from_list([-1.0, -2.0])
    testes.verificar_quase_igual("Norma-1 de um vetor negativo", u.norm_1(), 3.0)
    testes.verificar_quase_igual("Norma-2 de um vetor negativo", u.norm(), 2.23606797749979)
    testes.verificar_quase_igual("Norma-inf de um vetor negativo", u.norm_inf(), 2.0)
    
    # Teste 4: Vetor unitário (norma-2 deve ser 1)
    u = Vector.from_list([0.0, 1.0])
    testes.verificar_quase_igual("Norma-2 de um vetor unitário", u.norm(), 1.0)
    
    testes.finalizar_grupo()
    
    testes.mostrar_resultados()


def test_exercise_05():
    """Testa o Exercise 05: Cosine."""
    testes = Testes()
    
    testes.iniciar_grupo("Angle Cosine")
    
    # Teste 1: Vetores paralelos na mesma direção
    u = Vector.from_list([1.0, 0.0])
    v = Vector.from_list([1.0, 0.0])
    testes.verificar_quase_igual("Ângulo entre vetores paralelos (mesma direção)", angle_cos(u, v), 1.0)
    
    # Teste 2: Vetores ortogonais
    u = Vector.from_list([1.0, 0.0])
    v = Vector.from_list([0.0, 1.0])
    testes.verificar_quase_igual("Ângulo entre vetores ortogonais", angle_cos(u, v), 0.0)
    
    # Teste 3: Vetores paralelos em direções opostas
    u = Vector.from_list([-1.0, 1.0])
    v = Vector.from_list([1.0, -1.0])
    testes.verificar_quase_igual("Ângulo entre vetores paralelos (direções opostas)", angle_cos(u, v), -1.0)
    
    # Teste 4: Vetores proporcionais
    u = Vector.from_list([2.0, 1.0])
    v = Vector.from_list([4.0, 2.0])
    testes.verificar_quase_igual("Ângulo entre vetores proporcionais", angle_cos(u, v), 1.0)
    
    # Teste 5: Vetores arbitrários
    u = Vector.from_list([1.0, 2.0, 3.0])
    v = Vector.from_list([4.0, 5.0, 6.0])
    testes.verificar_quase_igual("Ângulo entre vetores arbitrários", angle_cos(u, v), 0.9746318461970762)
    
    # Teste 6: Erro para vetor nulo
    try:
        u = Vector.from_list([0.0, 0.0])
        v = Vector.from_list([1.0, 1.0])
        angle_cos(u, v)
        testes.verificar("Deve lançar erro para vetor nulo", False, True)
    except ValueError:
        testes.verificar("Deve lançar erro para vetor nulo", True, True)
    
    # Teste 7: Erro para vetores de tamanhos diferentes
    try:
        u = Vector.from_list([1.0, 2.0])
        v = Vector.from_list([1.0, 2.0, 3.0])
        angle_cos(u, v)
        testes.verificar("Deve lançar erro para vetores de tamanhos diferentes", False, True)
    except ValueError:
        testes.verificar("Deve lançar erro para vetores de tamanhos diferentes", True, True)
    
    testes.finalizar_grupo()
    
    testes.mostrar_resultados()    

def test_exercise_06():
    """Testa o Exercise 06: Cross Product."""
    testes = Testes()
    
    testes.iniciar_grupo("Cross Product")
    
    # Teste 1: Produto vetorial de vetores da base canónica
    u = Vector.from_list([0.0, 0.0, 1.0])
    v = Vector.from_list([1.0, 0.0, 0.0])
    resultado = cross_product(u, v)
    esperado = Vector.from_list([0.0, 1.0, 0.0])
    
    testes.verificar_vetores("Produto vetorial de vetores da base canónica", resultado, esperado)
    
    # Teste 2: Produto vetorial de vetores arbitrários
    u = Vector.from_list([1.0, 2.0, 3.0])
    v = Vector.from_list([4.0, 5.0, 6.0])
    resultado = cross_product(u, v)
    esperado = Vector.from_list([-3.0, 6.0, -3.0])
    
    testes.verificar_vetores("Produto vetorial de vetores arbitrários", resultado, esperado)
    
    # Teste 3: Produto vetorial de vetores com valores negativos
    u = Vector.from_list([4.0, 2.0, -3.0])
    v = Vector.from_list([-2.0, -5.0, 16.0])
    resultado = cross_product(u, v)
    esperado = Vector.from_list([17.0, -58.0, -16.0])
    
    testes.verificar_vetores("Produto vetorial de vetores com valores negativos", resultado, esperado)
    
    # Teste 4: Produto vetorial de vetores paralelos
    u = Vector.from_list([2.0, 4.0, 6.0])
    v = Vector.from_list([1.0, 2.0, 3.0])
    resultado = cross_product(u, v)
    esperado = Vector.from_list([0.0, 0.0, 0.0])
    
    testes.verificar_vetores("Produto vetorial de vetores paralelos deve ser nulo", resultado, esperado)
    
    # Teste 5: Erro para vetores não-3D
    try:
        u = Vector.from_list([1.0, 2.0])
        v = Vector.from_list([3.0, 4.0])
        cross_product(u, v)
        testes.verificar("Deve lançar erro para vetores não-3D", False, True)
    except ValueError:
        testes.verificar("Deve lançar erro para vetores não-3D", True, True)
    
    testes.finalizar_grupo()
    

    testes.mostrar_resultados()    


def test_exercise_07():
    """Testa o Exercise 07: Linear map, Matrix multiplication."""
    testes = Testes()
    
    # Teste de multiplicação matrix-vetor
    testes.iniciar_grupo("Matrix-Vector Multiplication")
    
    # Teste 1: Matriz identidade
    u = Matrix.from_list([
        [1.0, 0.0],
        [0.0, 1.0]
    ])
    v = Vector.from_list([4.0, 2.0])
    resultado = u.mul_vec(v)
    esperado = Vector.from_list([4.0, 2.0])
    
    testes.verificar_vetores("Multiplicação por matrix identidade", resultado, esperado)
    
    # Teste 2: Matriz de escala
    u = Matrix.from_list([
        [2.0, 0.0],
        [0.0, 2.0]
    ])
    v = Vector.from_list([4.0, 2.0])
    resultado = u.mul_vec(v)
    esperado = Vector.from_list([8.0, 4.0])
    
    testes.verificar_vetores("Multiplicação por matrix de escala", resultado, esperado)
    
    # Teste 3: Matriz arbitrária
    u = Matrix.from_list([
        [2.0, -2.0],
        [-2.0, 2.0]
    ])
    v = Vector.from_list([4.0, 2.0])
    resultado = u.mul_vec(v)
    esperado = Vector.from_list([4.0, -4.0])
    
    testes.verificar_vetores("Multiplicação por matrix arbitrária", resultado, esperado)

    
    # Teste 4: Erro para dimensões incompatíveis
    try:
        u = Matrix.from_list([
            [1.0, 0.0, 0.0],
            [0.0, 1.0, 0.0]
        ])
        v = Vector.from_list([1.0, 2.0])
        u.mul_vec(v)
        testes.verificar("Deve lançar erro para dimensões incompatíveis", False, True)
    except ValueError:
        testes.verificar("Deve lançar erro para dimensões incompatíveis", True, True)
    
    testes.finalizar_grupo()
    
    # Teste de multiplicação matrix-matrix
    testes.iniciar_grupo("Matrix-Matrix Multiplication")
    
    # Teste 1: Matriz identidade
    u = Matrix.from_list([
        [1.0, 0.0],
        [0.0, 1.0]
    ])
    v = Matrix.from_list([
        [1.0, 0.0],
        [0.0, 1.0]
    ])
    resultado = u.mul_mat(v)
    esperado = Matrix.from_list([
        [1.0, 0.0],
        [0.0, 1.0]
    ])
    
    testes.verificar_matrizes("Multiplicação de matrix identidade por identidade", resultado, esperado)
    
    # Teste 2: Matriz identidade por matrix arbitrária
    u = Matrix.from_list([
        [1.0, 0.0],
        [0.0, 1.0]
    ])
    v = Matrix.from_list([
        [2.0, 1.0],
        [4.0, 2.0]
    ])
    resultado = u.mul_mat(v)
    esperado = Matrix.from_list([
        [2.0, 1.0],
        [4.0, 2.0]
    ])
    
    testes.verificar_matrizes("Multiplicação de matrix identidade por arbitrária", resultado, esperado)
    
    # Teste 3: Multiplicação de matrizes arbitrárias
    u = Matrix.from_list([
        [3.0, -5.0],
        [6.0, 8.0]
    ])
    v = Matrix.from_list([
        [2.0, 1.0],
        [4.0, 2.0]
    ])
    resultado = u.mul_mat(v)
    esperado = Matrix.from_list([
        [-14.0, -7.0],
        [44.0, 22.0]
    ])
    
    testes.verificar_matrizes("Multiplicação de matrizes arbitrárias", resultado, esperado)
    
    # Teste 4: Erro para dimensões incompatíveis
    try:
        u = Matrix.from_list([
            [1.0, 0.0],
            [0.0, 1.0]
        ])
        v = Matrix.from_list([
            [1.0, 0.0, 0.0],
            [0.0, 1.0, 0.0],
            [0.0, 0.0, 1.0]
        ])
        u.mul_mat(v)
        testes.verificar("Deve lançar erro para dimensões incompatíveis", False, True)
    except ValueError:
        testes.verificar("Deve lançar erro para dimensões incompatíveis", True, True)
    
    testes.finalizar_grupo()
    testes.mostrar_resultados()    


def test_exercise_08():
    """Testa o Exercise 08: Trace."""
    testes = Testes()
    
    testes.iniciar_grupo("Matrix Trace")
    
    # Teste 1: Matriz identidade 2x2
    matrix = Matrix.from_list([
        [1.0, 0.0],
        [0.0, 1.0]
    ])
    resultado = matrix.trace()
    testes.verificar_quase_igual("Traço de uma matrix identidade 2x2", resultado, 2.0)
    
    # Teste 2: Matriz arbitrária 3x3
    matrix = Matrix.from_list([
        [2.0, -5.0, 0.0],
        [4.0, 3.0, 7.0],
        [-2.0, 3.0, 4.0]
    ])
    resultado = matrix.trace()
    testes.verificar_quase_igual("Traço de uma matrix arbitrária 3x3", resultado, 9.0)
    
    # Teste 3: Matriz com valores negativos na diagonal
    matrix = Matrix.from_list([
        [-2.0, -8.0, 4.0],
        [1.0, -23.0, 4.0],
        [0.0, 6.0, 4.0]
    ])
    resultado = matrix.trace()
    testes.verificar_quase_igual("Traço de uma matrix com valores negativos", resultado, -21.0)
    
    testes.finalizar_grupo()
    testes.mostrar_resultados()    


def test_exercise_09():
    """Testa o Exercise 09: Transpose."""
    testes = Testes()
    
    testes.iniciar_grupo("Matrix Transpose")
    
    # Teste 1: Matriz identidade (transposta deve ser igual à original)
    matrix = Matrix.from_list([
        [1.0, 0.0],
        [0.0, 1.0]
    ])
    resultado = matrix.transpose()
    esperado = Matrix.from_list([
        [1.0, 0.0],
        [0.0, 1.0]
    ])
    testes.verificar_matrizes("Transposta de uma matrix identidade", resultado, esperado)
    
    # Teste 2: Matriz retangular
    matrix = Matrix.from_list([
        [1.0, 2.0, 3.0],
        [4.0, 5.0, 6.0]
    ])
    resultado = matrix.transpose()
    esperado = Matrix.from_list([
        [1.0, 4.0],
        [2.0, 5.0],
        [3.0, 6.0]
    ])
    testes.verificar_matrizes("Transposta de uma matrix retangular 2x3", resultado, esperado)
    
    # Teste 3: Matriz não simétrica
    matrix = Matrix.from_list([
        [1.0, 2.0],
        [3.0, 4.0],
        [5.0, 6.0]
    ])
    resultado = matrix.transpose()
    esperado = Matrix.from_list([
        [1.0, 3.0, 5.0],
        [2.0, 4.0, 6.0]
    ])
    testes.verificar_matrizes("Transposta de uma matrix não simétrica 3x2", resultado, esperado)
    
    # Teste 4: Dupla transposta deve retornar a matrix original
    matrix = Matrix.from_list([
        [1.0, 2.0, 3.0],
        [4.0, 5.0, 6.0]
    ])
    resultado = matrix.transpose().transpose()
    esperado = matrix
    testes.verificar_matrizes("Dupla transposta deve retornar a matrix original", resultado, esperado)
    
    testes.finalizar_grupo()
    testes.mostrar_resultados()


def test_exercise_10():
    testes = Testes()
    
    testes.iniciar_grupo("Matrix Row-Echelon Form")
    
    # Teste 1: Matriz identidade  
    u = Matrix.from_list([
        [1., 0., 0.],
        [0., 1., 0.],
        [0., 0., 1.],
    ])
    resultado = u.row_echelon()
    esperado = Matrix.from_list([
        [1., 0., 0.],
        [0., 1., 0.],
        [0., 0., 1.],
    ])
    testes.verificar_matrizes("Forma escalonada de uma matrix identidade", resultado, esperado)
    
    # Teste 2: Matriz 2x2 com posto completo
    u = Matrix.from_list([
        [1., 2.],
        [3., 4.],
    ])
    resultado = u.row_echelon()
    esperado = Matrix.from_list([
        [1., 0.],
        [0., 1.],
    ])
    testes.verificar_matrizes("Forma escalonada de uma matrix 2x2 com posto completo", resultado, esperado)
    
    # Teste 3: Matriz com posto incompleto
    u = Matrix.from_list([
        [1., 2.],
        [2., 4.],
    ])
    resultado = u.row_echelon()
    esperado = Matrix.from_list([
        [1., 2.],
        [0., 0.],
    ])
    testes.verificar_matrizes("Forma escalonada de uma matrix com posto incompleto", resultado, esperado)
    
    # Teste 4: Matriz mais complexa
    u = Matrix.from_list([
        [8., 5., -2., 4., 28.],
        [4., 2.5, 20., 4., -4.],
        [8., 5., 1., 4., 17.],
    ])
    resultado = u.row_echelon()
    # O resultado esperado é aproximado devido a erros de ponto flutuante
    esperado = Matrix.from_list([
        [1., 0.625, 0., 0., -12.1666667],
        [0., 0., 1., 0., -3.6666667],
        [0., 0., 0., 1., 29.5],
    ])
    
    # Verifica com tolerância para erros de ponto flutuante
    correto = True
    for i in range(resultado.rows):
        for j in range(resultado.cols):
            if abs(resultado.data[i][j] - esperado.data[i][j]) > 0.1:  # Tolerância maior para este teste
                correto = False
                break
    
    testes.verificar("Forma escalonada de uma matrix complexa", correto, True)
    
    testes.finalizar_grupo()
    testes.mostrar_resultados()

def test_exercise_11():
 
    testes = Testes()
    
    testes.iniciar_grupo("Matrix Determinant")
    
    # Teste 1: Matriz singular
    u = Matrix.from_list([
        [ 1., -1.],
        [-1.,  1.],
    ])
    resultado = u.determinant()
    testes.verificar_quase_igual("Determinante de uma matrix singular", resultado, 0.0)
    
    # Teste 2: Matriz diagonal
    u = Matrix.from_list([
        [2., 0., 0.],
        [0., 2., 0.],
        [0., 0., 2.],
    ])
    resultado = u.determinant()
    testes.verificar_quase_igual("Determinante de uma matrix diagonal", resultado, 8.0)
    
    # Teste 3: Matriz 3x3 geral
    u = Matrix.from_list([
        [8.,  5., -2.],
        [4.,  7., 20.],
        [7.,  6.,  1.],
    ])
    resultado = u.determinant()
    testes.verificar_quase_igual("Determinante de uma matrix 3x3 geral", resultado, -174.0)
    
    # Teste 4: Matriz 4x4
    u = Matrix.from_list([
        [ 8.,  5., -2.,  4.],
        [ 4., 2.5, 20.,  4.],
        [ 8.,  5.,  1.,  4.],
        [28., -4., 17.,  1.],
    ])
    resultado = u.determinant()
    testes.verificar_quase_igual("Determinante de uma matrix 4x4", resultado, 1032.0)
    
    testes.finalizar_grupo()
    testes.mostrar_resultados()    

def test_exercise_12():
    testes = Testes()
    
    testes.iniciar_grupo("Matrix Inverse")
    
    # Teste 1: Matriz identidade  
    u = Matrix.from_list([
        [1., 0., 0.],
        [0., 1., 0.],
        [0., 0., 1.],
    ])
    try:
        resultado = u.inverse()
        esperado = Matrix.from_list([
            [1., 0., 0.],
            [0., 1., 0.],
            [0., 0., 1.],
        ])
        testes.verificar_matrizes("Inversa da matrix identidade", resultado, esperado)
    except ValueError as e:
        testes.verificar("Inversa da matrix identidade deveria existir", False, True)
    
    # Teste 2: Matriz diagonal
    u = Matrix.from_list([
        [2., 0., 0.],
        [0., 2., 0.],
        [0., 0., 2.],
    ])
    try:
        resultado = u.inverse()
        esperado = Matrix.from_list([
            [0.5, 0., 0.],
            [0., 0.5, 0.],
            [0., 0., 0.5],
        ])
        testes.verificar_matrizes("Inversa de uma matrix diagonal", resultado, esperado)
    except ValueError as e:
        testes.verificar("Inversa da matrix diagonal deveria existir", False, True)
    
    # Teste 3: Matriz 3x3 geral
    u = Matrix.from_list([
        [8., 5., -2.],
        [4., 7., 20.],
        [7., 6., 1.],
    ])
    try:
        resultado = u.inverse()
 
        esperado = Matrix.from_list([
            [0.649425287, 0.097701149, -0.655172414],
            [-0.781609195, -0.126436782, 0.965517241],
            [0.143678161, 0.074712644, -0.206896552],
        ])
        testes.verificar_matrizes("Inversa de uma matrix 3x3 geral", resultado, esperado)
        # print("\n")
        # # Verifica com tolerância para erros de ponto flutuante
        # correto = True
        # for i in range(resultado.rows):
        #     for j in range(resultado.cols):
        #         if abs(resultado.data[i][j] - esperado.data[i][j]) > 0.01:
        #             correto = False
        #             break
        
        # testes.verificar("Inversa de uma matrix 3x3 geral", correto, True)
    except ValueError as e:
        testes.verificar("Inversa da matrix 3x3 deveria existir", False, True)
    
    # Teste 4: Matriz singular :não deve ter inversa
    u = Matrix.from_list([
        [1., 2.],
        [2., 4.],
    ])
    try:
        resultado = u.inverse()
        testes.verificar("Matriz singular não deveria ter inversa", False, True)
    except ValueError:
        testes.verificar("Matriz singular não tem inversa", True, True)
    
    testes.finalizar_grupo()
    testes.mostrar_resultados()    

def test_exercise_13():
 
    testes = Testes()
    
    testes.iniciar_grupo("Matrix Rank")
    
    # Teste 1: Matriz identidade (posto completo)
    u = Matrix.from_list([
        [1., 0., 0.],
        [0., 1., 0.],
        [0., 0., 1.],
    ])
    resultado = u.rank()
    testes.verificar("Posto de uma matrix identidade 3x3", resultado, 3)
    
    # Teste 2: Matriz com linhas linearmente dependentes
    u = Matrix.from_list([
        [ 1., 2., 0., 0.],
        [ 2., 4., 0., 0.],
        [-1., 2., 1., 1.],
    ])
    resultado = u.rank()
    testes.verificar("Posto de uma matrix com linhas dependentes", resultado, 2)
    
    # Teste 3: Matriz retangular com posto completo
    u = Matrix.from_list([
        [ 8., 5., -2.],
        [ 4., 7., 20.],
        [ 7., 6., 1.],
        [21., 18., 7.],
    ])
    resultado = u.rank()
    testes.verificar("Posto de uma matrix retangular com posto completo", resultado, 3)
    
    # Teste 4: Matriz nula (posto zero)
    u = Matrix.from_list([
        [0., 0., 0.],
        [0., 0., 0.],
    ])
    resultado = u.rank()
    testes.verificar("Posto de uma matrix nula", resultado, 0)
    
    testes.finalizar_grupo()
    testes.mostrar_resultados()

def main():
    print(f"{Cores.NEGRITO}{Cores.CIANO}MATRIX - TESTES DE ÁLGEBRA LINEAR{Cores.RESET}")
    print("Baseado no módulo 'Enter the Matrix - An introduction to Linear Algebra'\n")
    

    print(f"{Cores.AMARELO}Escolhe um exercício para testar:{Cores.RESET}")
    print("1 - Exercise 00: Add, Subtract e Scale")
    print("2 - Exercise 01: Linear Combination")
    print("3 - Exercise 02: Linear Interpolation")
    print("4 - Exercise 03: Dot Product")
    print("5 - Exercise 04: Norm")
    print("6 - Exercise 05: Cosine")
    print("7 - Exercise 06: Cross Product")
    print("8 - Exercise 07: Linear Map, Matrix Multiplication")
    print("9 - Exercise 08: Trace") 
    print("10 - Exercise 09: Transpose") 
    print("11 - Exercise 10: Row-Echelon Form")
    print("12 - Exercise 11: Determinant")
    print("13 - Exercise 12: Inverse")
    print("14 - Exercise 13: Rank")

    print("0 - Executar todos os testes")
    print("Q - Sair")
    
    try:
        escolha = input("\nValor: ")
        if escolha == "Q" or escolha == "q":
            print("\n",Cores.AMARELO,"BY! BY! :)" , "\n",Cores.RESET)
            exit()
        valor = int(escolha)
        
        if valor == 1:
            test_exercise_00()
        elif valor == 2:
            test_exercise_01()
        elif valor == 3:
            test_exercise_02()
        elif valor == 4:
            test_exercise_03()
        elif valor == 5:
            test_exercise_04()
        elif valor == 6:
            test_exercise_05()
        elif valor == 7:
            test_exercise_06()
        elif valor == 8:
            test_exercise_07()
        elif valor == 9:
            test_exercise_08()
        elif valor == 10:
            test_exercise_09()
        elif valor == 11:
            test_exercise_10()
        elif valor == 12:
            test_exercise_11()
        elif valor == 13:
            test_exercise_12()
        elif valor == 14:
            test_exercise_13()

        elif valor == 0:
            test_exercise_00()
            print("\n",Cores.AMARELO,"="*50 , "\n",Cores.RESET)
            test_exercise_01()
            print("\n",Cores.AMARELO,"="*50 , "\n",Cores.RESET)
            test_exercise_02()
            print("\n",Cores.AMARELO,"="*50 , "\n",Cores.RESET)
            test_exercise_03()
            print("\n",Cores.AMARELO,"="*50 , "\n",Cores.RESET)
            test_exercise_04()
            print("\n",Cores.AMARELO,"="*50 , "\n",Cores.RESET)
            test_exercise_05()
            print("\n",Cores.AMARELO,"="*50 , "\n",Cores.RESET)
            test_exercise_06()
            print("\n",Cores.AMARELO,"="*50 , "\n",Cores.RESET)
            test_exercise_07()
            print("\n",Cores.AMARELO,"="*50 , "\n",Cores.RESET)
            test_exercise_08()
            print("\n",Cores.AMARELO,"="*50 , "\n",Cores.RESET)
            test_exercise_09()
            print("\n",Cores.AMARELO,"="*50 , "\n",Cores.RESET)
            test_exercise_10()
            print("\n",Cores.AMARELO,"="*50 , "\n",Cores.RESET)
            test_exercise_11()
            print("\n",Cores.AMARELO,"="*50 , "\n",Cores.RESET)
            test_exercise_12()
            print("\n",Cores.AMARELO,"="*50 , "\n",Cores.RESET)
            test_exercise_13()
            print("\n",Cores.AMARELO,"="*50 , "\n",Cores.RESET)

        else:
            print(f"{Cores.VERMELHO}Valor inválida! :( {Cores.RESET}")
    except ValueError:
        print(f"{Cores.VERMELHO}Insere um número válido.{Cores.RESET}")

if __name__ == "__main__":
    main()

