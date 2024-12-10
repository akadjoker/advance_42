#!/bin/bash

# Cores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Contadores
TOTAL=0
PASSED=0

# Limpar arquivos temporários
rm -f test_output.txt nm_output.txt

# Compilar ft_nm
echo -e "${YELLOW}Compilando ft_nm...${NC}"
make
if [ $? -ne 0 ]; then
    echo -e "${RED}Erro na compilação${NC}"
    exit 1
fi

# Função de teste
test_binary() {
    local binary=$1
    local test_name=$2
    ((TOTAL++))
    
    echo -e "\n${YELLOW}Testando: ${test_name}${NC}"
    
    # Executar ambos os comandos
    ./ft_nm "$binary" > test_output.txt 2>/dev/null
    nm "$binary" > nm_output.txt 2>/dev/null
    
    # Comparar saídas
    if diff test_output.txt nm_output.txt >/dev/null; then
        echo -e "${GREEN}✅ Teste passou${NC}"
        ((PASSED++))
    else
        echo -e "${RED}❌ Teste falhou${NC}"
        echo "Primeiras diferenças:"
        diff test_output.txt nm_output.txt | head -n 5
    fi
}

# Testes com binários do sistema
test_binary "/bin/ls" "ls binary"
test_binary "/bin/bash" "bash binary"
test_binary "./ft_nm" "ft_nm binary"

# Teste com biblioteca
if [ -f "/usr/lib/libc.so" ]; then
    test_binary "/usr/lib/libc.so" "libc library"
fi

# Teste de arquivo inexistente
((TOTAL++))
echo -e "\n${YELLOW}Testando arquivo inexistente${NC}"
./ft_nm nao_existe >/dev/null 2>&1
if [ $? -ne 0 ]; then
    echo -e "${GREEN}✅ Erro tratado corretamente${NC}"
    ((PASSED++))
else
    echo -e "${RED}❌ Erro não tratado corretamente${NC}"
fi

# Criar e testar arquivo não-ELF
echo "not an elf" > not_elf
((TOTAL++))
echo -e "\n${YELLOW}Testando arquivo não-ELF${NC}"
./ft_nm not_elf >/dev/null 2>&1
if [ $? -ne 0 ]; then
    echo -e "${GREEN}✅ Erro tratado corretamente${NC}"
    ((PASSED++))
else
    echo -e "${RED}❌ Erro não tratado corretamente${NC}"
fi

# Resumo
echo -e "\n${YELLOW}Resumo dos Testes:${NC}"
echo "Total de testes: $TOTAL"
echo -e "Passou: ${GREEN}$PASSED${NC}"
echo -e "Falhou: ${RED}$((TOTAL - PASSED))${NC}"

# Limpar
rm -f test_output.txt nm_output.txt not_elf

# Status de saída
[ $PASSED -eq $TOTAL ]
