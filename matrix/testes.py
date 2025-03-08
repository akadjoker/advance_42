

class Cores:

    VERDE = '\033[32m'
    VERMELHO = '\033[31m'
    AMARELO = '\033[33m'
    AZUL = '\033[34m'
    MAGENTA = '\033[35m'
    CIANO = '\033[36m'
    NEGRITO = '\033[1m'
    RESET = '\033[0m'

class Testes:

    
    def __init__(self):
        self.testes_executados = 0
        self.testes_passados = 0
        self.testes_falhados = 0
    
    def iniciar_grupo(self, nome):
        print(f"\n{Cores.NEGRITO}{Cores.AZUL}=== TESTE: {nome} ==={Cores.RESET}")
        self.testes_grupo = 0
        self.acertos_grupo = 0
    
    def verificar(self, descricao, resultado, esperado):
        self.testes_executados += 1
        self.testes_grupo += 1
        
        if resultado == esperado:
            status = f"{Cores.VERDE}✓ PASSOU{Cores.RESET}"
            self.testes_passados += 1
            self.acertos_grupo += 1
        else:
            status = f"{Cores.VERMELHO}✗ FALHOU{Cores.RESET}"
            self.testes_falhados += 1
            
        print(f"{status} - {descricao}")
        if resultado != esperado:
            print(f"  {Cores.VERMELHO}Esperado:{Cores.RESET} {esperado}")
            print(f"  {Cores.VERMELHO}Obtido:{Cores.RESET} {resultado}")
        else:
            print(f"  {Cores.MAGENTA}   Resultado:{Cores.RESET}{resultado}")
        
        return resultado == esperado
    
    def verificar_quase_igual(self, descricao, resultado, esperado, tolerancia=1e-6):
        """Verifica se um resultado é aproximadamente igual ao esperado, com tolerância."""
        igual = abs(resultado - esperado) < tolerancia
        return self.verificar(descricao, resultado if not igual else esperado, esperado)
    
    def verificar_vetores(self, descricao, vetor_resultado, vetor_esperado):
        # Aproveita a implementação de __eq__ da classe Vector
        return self.verificar(descricao, vetor_resultado, vetor_esperado)
    
    def verificar_matrizes(self, descricao, matriz_resultado, matriz_esperada):
        # Aproveita a implementação de __eq__ da classe Matrix
        return self.verificar(descricao, matriz_resultado, matriz_esperada)
    
    def finalizar_grupo(self):
        print(f"\n{Cores.AMARELO}Resultados: {self.acertos_grupo}/{self.testes_grupo} testes passaram.{Cores.RESET}")
    
    def mostrar_resultados(self):

        print(f"\n{Cores.NEGRITO}{Cores.MAGENTA}=== RESULTADOS FINAIS ==={Cores.RESET}")
        print(f"{Cores.AMARELO}Total de testes: {self.testes_executados}{Cores.RESET}")
        print(f"{Cores.VERDE}Testes passados: {self.testes_passados}{Cores.RESET}")
        print(f"{Cores.VERMELHO}Testes falhados: {self.testes_falhados}{Cores.RESET}")
        
        percentagem = (self.testes_passados / self.testes_executados * 100) if self.testes_executados > 0 else 0
        print(f"{Cores.NEGRITO}Taxa de sucesso: {percentagem:.1f}%{Cores.RESET}")

