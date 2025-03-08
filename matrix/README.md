# MATRIX - Uma Introdução à Álgebra Linear

Este projeto implementa uma biblioteca de álgebra linear em Python, seguindo as diretrizes do módulo "Enter the Matrix" - uma introdução à álgebra linear. A biblioteca fornece diversas operações fundamentais com vetores e matrixes, permitindo explorar os conceitos essenciais da álgebra linear de forma prática.

## Estrutura do Projeto

- **linear_algebra.py**: Classes principais `Vector` e `Matrix` com as operações básicas
- **utils.py**: Funções auxiliares e operações adicionais
- **testes.py**: Framework para testar as implementações
- **main.py**: Interface de linha de comando para executar testes

## Funcionalidades Implementadas

### Operações Básicas

- **Exercise 00**:
        Implementa operações de adição, subtração e multiplicação por escalar para vetores e matrizes.
        Permite combinar vetores e matrizes de forma linear.
- **Exercise 01**:
        Permite calcular combinações lineares de vetores, demonstrando o conceito de espaço vetorial.
- **Exercise 02**:
        Implementa a interpolação linear entre vetores e matrizes, útil para animações e transições suaves.
- **Exercise 03**:
        Calcula o produto escalar (dot product) entre vetores, uma operação fundamental para medir ângulos e projeções.
- **Exercise 04**:
        Calcula as normas L1, L2 e L∞ de vetores, usadas para medir o comprimento e a magnitude de vetores.
- **Exercise 05**:
        Calcula o cosseno do ângulo entre vetores, permitindo medir a semelhança entre vetores.
- **Exercise 06**:
        Implementa o produto vetorial (cross product) para vetores 3D, útil para calcular áreas e normais em geometria 3D.
- **Exercise 08**:
        Implementa a multiplicação matriz-vetor e matriz-matriz, operações essenciais para transformações lineares.

### Propriedades e Transformações de Matrizes

- **Exercise 08**:
        Calcula o traço de uma matriz, a soma dos elementos da diagonal principal.
- **Exercise 09**:
        Calcula a transposta de uma matriz, trocando linhas por colunas.
- **Exercise 10**:
        Transforma uma matriz para a forma escalonada (row-echelon form) usando eliminação gaussiana.
- **Exercise 11**:
        Calcula o determinante de uma matriz, um valor escalar que indica a escala e orientação da transformação linear.
- **Exercise 12**:
        Calcula a matriz inversa, se existir, usando eliminação gaussiana ou decomposição LU.
- **Exercise 13**:
        Calcula o posto (rank) de uma matriz, o número de linhas ou colunas linearmente independentes.
- **Exercise 04** (Bónus):
        Gera uma matriz de projeção para gráficos 3D, transformando coordenadas 3D em coordenadas 2D para renderização.

## Detalhes de Implementação

### Classe Vector
A classe `Vector` representa vetores n-dimensionais e suporta:
- Acesso e modificação de elementos por índice
- Operações básicas: adição, subtração, multiplicação por escalar
- Produto escalar e vetorial
- Cálculo de diferentes normas
- Comparação entre vetores

### Classe Matrix
A classe `Matrix` representa matrixes m×n e suporta:
- Acesso e modificação de elementos por índice
- Operações básicas: adição, subtração, multiplicação por escalar
- Multiplicação matrix-vetor e matrix-matrix
- Cálculo do traço, determinante, posto e inversa
- Transformação para forma escalonada
- Comparação entre matrixes

## Funções Avançadas de Álgebra Linear

### Traço (Exercise 08)
O traço de uma matrix é a soma dos elementos da diagonal principal. Embora conceitualmente simples, o traço tem propriedades matemáticas profundas:

- **Interpretação geométrica**: Representa a soma dos autovalores da matrix
- **Invariância**: O traço é invariante sob transformações de similaridade (A → P⁻¹AP)
- **Aplicações**: Usado em física quântica (operadores de traço), em estatística (traço da matrix de covariância) e no cálculo de determinantes

### Transposta (Exercise 09)
A transposta de uma matrix A é obtida trocando suas linhas por colunas, resultando em uma nova matrix A^T:

- **Propriedades fundamentais**: (A^T)^T = A, (A+B)^T = A^T + B^T, (AB)^T = B^T A^T
- **Aplicações**: Sistemas de equações normais, cálculo de matrixes simétricas, decomposições matriciais
- **Em espaços vetoriais**: Representa o operador adjunto em espaços com produto interno

### Forma Escalonada (Exercise 10)
A forma escalonada (row-echelon form) é uma forma normalizada de matrix obtida através de operações elementares de linha:

- **Características**: Elementos não-nulos à esquerda de cada linha (pivôs) estão à direita do pivô da linha acima
- **Eliminação Gaussiana**: Algoritmo que transforma uma matrix em forma escalonada
- **Aplicações**: Resolver sistemas de equações lineares, calcular posto, determinante e inversa
- **Desafios computacionais**: Erros de arredondamento e estabilidade numérica

### Determinante (Exercise 11)
O determinante é um valor escalar associado a uma matrix quadrada com interpretações algébricas e geométricas:

- **Interpretação geométrica**: Representa a mudança de volume/área sob transformação linear
- **Propriedades**: det(AB) = det(A)det(B), det(A^T) = det(A), det(A⁻¹) = 1/det(A)
- **Singularidade**: Uma matrix é singular (não-inversível) se e somente se seu determinante for zero
- **Métodos de cálculo**: Regra de Sarrus (3x3), expansão de Laplace, decomposição LU

### Posto (Rank) (Exercise 13)
O posto de uma matrix é uma medida fundamental da "dimensionalidade efetiva" dos dados:

- **Definição**: Número de linhas ou colunas linearmente independentes
- **Interpretação geométrica**: Dimensão do espaço de imagem da transformação linear
- **Teorema do Posto-Nulidade**: rank(A) + nullity(A) = n para matrix A n×m
- **Aplicações**: Análise de sistemas de equações, compressão de dados, redução de dimensionalidade
- **Cálculo**: Através da forma escalonada, contando o número de pivôs não-nulos

### matrix de Projeção (Exercise 14)
A matrix de projeção é fundamental em computação gráfica 3D:

- **Função**: Transforma coordenadas 3D em coordenadas 2D para renderização no monitor
- **Parâmetros**: Campo de visão (FOV), razão de aspecto, planos próximo e distante
- **Espaço Normalizado**: Mapeia o volume de visualização para coordenadas normalizadas
- **Transformação perspectiva**: Responsável pelo efeito de objetos distantes parecerem menores

## Estabilidade Numérica

As implementações incluem considerações para estabilidade numérica:
- Uso de tolerância para comparações de valores de ponto flutuante
- Estratégias de pivoteamento parcial para o escalonamento
- Tratamento especial para casos degenerados (ex: matrixes singulares)

## Sistema de Teste

Implementamos um sistema de teste abrangente que:
- Executa verificações para cada funcionalidade
- Compara resultados com valores esperados
- Calcula estatísticas de sucesso dos testes
 

## Complexidade Computacional

Analisamos cada operação em termos de complexidade temporal e espacial:
- Operações vetoriais básicas: O(n) tempo, O(n) espaço
- Multiplicação matrix-vetor: O(nm) tempo, O(n) espaço
- Multiplicação matrix-matrix: O(nmp) tempo, O(nm) espaço
- Cálculo do determinante: O(n³) tempo, O(n²) espaço
- Forma escalonada e inversão: O(n³) tempo, O(n²) espaço

## Aplicações Práticas

### Aplicação em Computação Gráfica
A implementação da matrix de projeção demonstra como a álgebra linear é fundamental para a renderização 3D:
- Transforma o "mundo 3D" em uma projeção 2D para exibição no monitor
- Cria o efeito de perspectiva (objetos distantes parecem menores)
- Permite definir o campo de visão da "câmera virtual"

### Aplicação em Física
As transformações lineares modelam diversos fenômenos físicos:
- Rotações e reflexões no espaço 3D
- Transformações de bases em mecânica quântica
- Análise de sistemas dinâmicos

### Aplicação em Ciência de Dados
Operações como a decomposição em valores singulares (baseada em conceitos implementados):
- Redução de dimensionalidade
- Análise de componentes principais (PCA)
- Sistemas de recomendação e processamento de imagens

## Considerações Finais

Este projeto oferece uma implementação educacional de álgebra linear, privilegiando a clareza conceitual sobre a eficiência extrema. Para aplicações de alto desempenho com matrixes e vetores muito grandes, bibliotecas especializadas como NumPy e SciPy seriam mais adequadas.

A compreensão dos conceitos fundamentais implementados aqui é essencial para diversos campos, incluindo ciência da computação, física, engenharia, e machine learning.
