import math 
from linear_algebra import Vector, Matrix
from testes import Cores

def linear_combination(vectors, coefficients):
    """
    Calcula a combinação linear de vetores com os coeficientes dados.
    
    Complexidade temporal: O(n), onde n é o tamanho total dos vetores
    Complexidade espacial: O(n), onde n é o tamanho de um vetor individual
    
    Args:
        vectors: Lista de objetos Vector que serão combinados
        coefficients: Lista de coeficientes escalares para cada vetor
    
    Returns:
        Um novo Vector resultante da combinação linear
    
    Raises:
        ValueError: Se o número de vetores e coeficientes for diferente,
                   ou se os vetores tiverem tamanhos diferentes
    """
    if len(vectors) != len(coefficients):
        raise ValueError("O número de vetores deve ser igual ao número de coeficientes")
    
    if not vectors:
        raise ValueError("É necessário pelo menos um vetor")
    
    # Verificar se todos os vetores têm o mesmo tamanho
    size = len(vectors[0])
    for v in vectors:
        if len(v) != size:
            raise ValueError("Todos os vetores devem ter o mesmo tamanho")
    
    # Inicializar o vetor resultado com zeros
    result = Vector([0.0] * size)
    
    # Calcular a combinação linear
    for i in range(len(vectors)):
        scaled_vector = Vector(vectors[i].data.copy())
        scaled_vector.scl(coefficients[i])
        result.add(scaled_vector)
    
    return result


def lerp(u, v, t):
    """
    Realiza interpolação linear entre dois escalares u e v.
    
    Complexidade temporal: O(1)
    Complexidade espacial: O(1)
    
    Args:
        u: Primeiro valor escalar
        v: Segundo valor escalar
        t: Parâmetro de interpolação, normalmente no intervalo [0, 1]
    
    Returns:
        O valor interpolado: u + t * (v - u)
    """
    return u + t * (v - u)

# Função de interpolação linear entre vetores
def vector_lerp(u, v, t):
    """
    Realiza interpolação linear entre dois vetores u e v.
    
    Complexidade temporal: O(n), onde n é o tamanho dos vetores
    Complexidade espacial: O(n), para armazenar o vetor resultante
    
    Args:
        u: Primeiro vetor
        v: Segundo vetor
        t: Parâmetro de interpolação, normalmente no intervalo [0, 1]
    
    Returns:
        Um novo vetor que é a interpolação linear entre u e v
        
    Raises:
        ValueError: Se os vetores tiverem tamanhos diferentes
    """
    if len(u) != len(v):
        raise ValueError("Os vetores devem ter o mesmo tamanho")
    
    result = Vector([0.0] * len(u))
    for i in range(len(u)):
        result.data[i] = lerp(u[i], v[i], t)
    
    return result


def matrix_lerp(u, v, t):
    """
    Realiza interpolação linear entre duas matrizes u e v.
    
    Complexidade temporal: O(n), onde n é o número total de elementos nas matrizes
    Complexidade espacial: O(n), para armazenar a matrix resultante
    
    Args:
        u: Primeira matrix
        v: Segunda matrix
        t: Parâmetro de interpolação, normalmente no intervalo [0, 1]
    
    Returns:
        Uma nova matrix que é a interpolação linear entre u e v
        
    Raises:
        ValueError: Se as matrizes tiverem dimensões diferentes
    """
    if u.rows != v.rows or u.cols != v.cols:
        raise ValueError("As matrizes devem ter as mesmas dimensões")
    
    result = Matrix([[0.0 for _ in range(u.cols)] for _ in range(u.rows)])
    for i in range(u.rows):
        for j in range(u.cols):
            result.data[i][j] = lerp(u.data[i][j], v.data[i][j], t)
    
    return result

# Exercise 05 -  Angle between vectors
def angle_cos(u, v):
    """
    Calcula o cosseno do ângulo entre dois vetores.
    
    Complexidade temporal: O(n), onde n é o tamanho dos vetores
    Complexidade espacial: O(1), apenas um valor escalar é calculado
    
    Args:
        u: Primeiro vetor
        v: Segundo vetor
        
    Returns:
        O cosseno do ângulo entre os vetores u e v
        
    Raises:
        ValueError: Se os vetores tiverem tamanhos diferentes ou se algum deles for o vetor nulo
    """
    if len(u) != len(v):
        raise ValueError("Os vetores devem ter o mesmo tamanho")
    
    u_norm = u.norm()
    v_norm = v.norm()
    
    if u_norm == 0 or v_norm == 0:
        raise ValueError("Não é possível calcular o ângulo quando um dos vetores é nulo")
    
    return u.dot(v) / (u_norm * v_norm)


# Exercise 06 -  Cross product
def cross_product(u, v):
    """
    Calcula o produto vetorial (cross product) entre dois vetores 3D.
    
    Complexidade temporal: O(1), pois são apenas operações com vetores 3D
    Complexidade espacial: O(1), cria apenas um novo vetor 3D
    
    Args:
        u: Primeiro vetor (3D)
        v: Segundo vetor (3D)
        
    Returns:
        Um novo vetor que é o produto vetorial de u e v
        
    Raises:
        ValueError: Se algum dos vetores não for 3D
    """
    if len(u) != 3 or len(v) != 3:
        raise ValueError("O produto vetorial só é definido para vetores 3D")
    
    # Calcula as componentes do produto vetorial
    x = u[1] * v[2] - u[2] * v[1]
    y = u[2] * v[0] - u[0] * v[2]
    z = u[0] * v[1] - u[1] * v[0]
    
    return Vector([x, y, z])



def projection(fov, ratio, near, far):
    """
    Cria uma matrix de projeção para renderização 3D.
    
    Args:
        fov: Campo de visão em radianos
        ratio: Proporção da tela (largura/altura)
        near: Distância do plano próximo
        far: Distância do plano distante
        
    Returns:
        Uma matrix de projeção 4x4
    
    Raises:
        ValueError: Se os parâmetros forem inválidos
    """
    # Validação de parâmetros
    if fov <= 0 or fov >= math.pi:
        raise ValueError("O campo de visão deve estar entre 0 e 180 graus (exclusivo)")
    if ratio <= 0:
        raise ValueError("A razão de aspecto deve ser positiva")
    if near <= 0:
        raise ValueError("A distância do plano próximo deve ser positiva")
    if far <= near:
        raise ValueError("A distância do plano distante deve ser maior que a do plano próximo")
    
    # Calcular a tangente da metade do ângulo do campo de visão
    tan_half_fov = math.tan(fov / 2)
    
 
    result = Matrix([[0.0 for _ in range(4)] for _ in range(4)])
    
 
    result.data[0][0] = 1.0 / (ratio * tan_half_fov)
    result.data[1][1] = 1.0 / tan_half_fov
    result.data[2][2] = far / (near - far)
    result.data[2][3] = (far * near) / (near - far)
    result.data[3][2] = -1.0
    
    return result

def create_projection_file(filename="proj", fov=60.0, ratio=1.0, near=0.1, far=100.0):
    """
    Cria um ficheiro com a matrix de projeção para teste com o software de exibição.
    
    Args:
        filename: Nome do ficheiro a ser criado
        fov: Campo de visão em graus
        ratio: Proporção da tela (largura/altura)
        near: Distância do plano próximo
        far: Distância do plano distante
    
    Returns:
        True se o ficheiro foi criado com sucesso, False caso contrário
    """
    try:
        # Convertemos FOV de graus para radianos
        fov_rad = math.radians(fov)
        
 
        proj_matrix = projection(fov_rad, ratio, near, far)
        
 
        with open(filename, 'w') as f:
            for i in range(4):
                for j in range(4):
                    f.write(f"{proj_matrix.data[j][i]}")  #   inversão de índices para formato column-major
                    if not (i == 3 and j == 3):
                        f.write(", ")
                f.write("\n")
        
        print(f"{Cores.VERDE}Ficheiro '{filename}' gravado.{Cores.RESET}")
        return True
    
    except ValueError as e:
        print(f"{Cores.VERMELHO}Erro: {str(e)}{Cores.RESET}")
        return False
    
    except IOError as e:
        print(f"{Cores.VERMELHO}Erro ao gravar o ficheiro: {str(e)}{Cores.RESET}")
        return False
    
    except Exception as e:
        print(f"{Cores.VERMELHO}Erro inesperado: {str(e)}{Cores.RESET}")
        return False