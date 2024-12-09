# Algoritmo de Alocação de Memória

Este projeto implementa um algoritmo de alocação de memória que utiliza diferentes estratégias dependendo do tamanho da solicitação de memória. Ele é otimizado para lidar com solicitações grandes, pequenas e intermediárias de maneira eficiente.

## Propriedades do Algoritmo

O algoritmo de alocação de memória possui as seguintes características:

### 1. **Comportamento para Solicitações de Memória**

- **Solicitações grandes (>= 512 bytes):** O alocador usa uma estratégia **best-fit**, onde o bloco de memória que melhor se adapta ao tamanho solicitado é escolhido. Em caso de empate, a escolha é feita via **FIFO** (First In, First Out), ou seja, o bloco menos recentemente usado é selecionado.

- **Solicitações pequenas (<= 64 bytes):** Para essas solicitações, o alocador age como um **alocador de cache**, mantendo pools de blocos de memória que podem ser reciclados rapidamente, evitando a sobrecarga de alocação/desalocação frequente.

- **Solicitações intermediárias (entre 64 bytes e 512 bytes):** O alocador tenta equilibrar as estratégias para atender tanto a solicitações pequenas quanto grandes de maneira eficiente.

- **Solicitações muito grandes (>= 128KB):** Para esses casos, o alocador utiliza as **facilidades de mapeamento de memória** fornecidas pelo sistema operacional, se disponíveis, para realizar a alocação de memória.

### 2. **Alinhamento de Memória**

- O alinhamento padrão é **2 * sizeof(size_t)**, garantindo que a memória seja alinhada de acordo com a arquitetura da máquina.
- O valor padrão (8 bytes de alinhamento para um `size_t` de 4 bytes) é suficiente para a maioria das plataformas e compiladores atuais, mas pode ser configurado com a definição `MALLOC_ALIGNMENT` caso necessário.

### 3. **Sobrecarga Mínima por Bloco Alocado**

- Cada bloco de memória alocado possui uma sobrecarga mínima que armazena informações como o **tamanho do bloco** e o **status** (livre ou ocupado).
- Para sistemas com **ponteiros de 4 bytes**, a sobrecarga mínima é de **4 bytes**.
- Para sistemas com **ponteiros de 8 bytes**, a sobrecarga mínima pode ser de **8 bytes**.

### 4. **Tamanho Mínimo Alocável**

- Para sistemas de **32 bits** (ponteiros de 4 bytes), o tamanho mínimo alocável é de **16 bytes**.
- Para sistemas de **64 bits** (ponteiros de 8 bytes), o tamanho mínimo pode ser **24 ou 32 bytes**, dependendo da arquitetura e da sobrecarga.
- Mesmo quando uma solicitação for de **0 bytes** (por exemplo, `malloc(0)`), a função retorna um ponteiro para o mínimo alocável, que é de **16, 24 ou 32 bytes**.

### 5. **Sobrecarga Máxima de Alocação**

- A sobrecarga de memória alocada não será maior do que o tamanho mínimo alocável, exceto para solicitações muito grandes, que são atendidas com o uso de **mmap()**.
- Para solicitações muito grandes, a sobrecarga pode ser maior, resultando em desperdício de memória, que é de **2 * sizeof(size_t)** mais o restante da página de memória do sistema (tipicamente 4096 ou 8192 bytes).

### 6. **Tamanho Máximo Alocável**

- **Em sistemas de 32 bits** (onde `size_t` tem 4 bytes), o tamanho máximo alocável é de aproximadamente **2^32 bytes**, com uma sobrecarga de duas páginas de memória.
- **Em sistemas de 64 bits** (onde `size_t` tem 8 bytes), o tamanho máximo alocável é de **2^64 bytes**, com a mesma sobrecarga de duas páginas de memória.




- ** https://wiki-prog.infoprepa.epita.fr/images/0/04/Malloc_tutorial.pdf
- ** https://code.woboq.org/userspace/glibc/malloc/malloc.c.html
- ** https://www.gnu.org/software/libc/manual/html_node/Unconstrained-Allocation.html
