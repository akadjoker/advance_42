from linear_algebra import Vector, Matrix
from testes import Testes, Cores
from utils import projection, create_projection_file

 
import math
 

def main():
    print(f"{Cores.NEGRITO}{Cores.AZUL}=== Gerador de Matrix de Projeção ==={Cores.RESET}")
    print("Este programa cria um ficheiro 'proj' com uma matrix de projeção para o teste de visualização.")
    
    try:
 
        # while True:
        #     try:
        #         fov_input = input("Campo de visão (em graus, padrão 90): ")
        #         fov = float(fov_input) if fov_input.strip() else 90.0
        #         if fov <= 0 or fov >= 180:
        #             print(f"{Cores.AMARELO}Aviso: O campo de visão deve estar entre 0 e 180 graus (exclusivo).{Cores.RESET}")
        #             continue
                
        #         ratio_input = input("Razão de aspecto (largura/altura, padrão 1.2): ")
        #         ratio = float(ratio_input) if ratio_input.strip() else 1.2
        #         if ratio <= 0:
        #             print(f"{Cores.AMARELO}Aviso: A razão de aspecto deve ser positiva.{Cores.RESET}")
        #             continue
                
        #         near_input = input("Plano próximo (padrão 0.1): ")
        #         near = float(near_input) if near_input.strip() else 0.1
        #         if near <= 0:
        #             print(f"{Cores.AMARELO}Aviso: A distância do plano próximo deve ser positiva.{Cores.RESET}")
        #             continue
                
        #         far_input = input("Plano distante (padrão 1000.0): ")
        #         far = float(far_input) if far_input.strip() else 1000.0
        #         if far <= near:
        #             print(f"{Cores.AMARELO}Aviso: A distância do plano distante deve ser maior que a do plano próximo.{Cores.RESET}")
        #             continue
                
 
        #         break
                
        #     except ValueError:
        #         print(f"{Cores.VERMELHO}Erro: Por favor, insira um número válido.{Cores.RESET}")
        
 
        #success = create_projection_file("proj", fov, ratio, near, far)
        success = create_projection_file("proj", 90.0,800/1200,0.1,5000.0)
        
        if success:
            print(f"{Cores.VERDE}Processo concluído com sucesso!{Cores.RESET}")
        else:
            print(f"{Cores.VERMELHO}Falha ao criar o ficheiro de projeção.{Cores.RESET}")
    
    except KeyboardInterrupt:
        print(f"\n{Cores.AMARELO}Operação cancelada pelo utilizador.{Cores.RESET}")
    
    except Exception as e:
        print(f"{Cores.VERMELHO}Erro inesperado: {str(e)}{Cores.RESET}")

if __name__ == "__main__":
    main()