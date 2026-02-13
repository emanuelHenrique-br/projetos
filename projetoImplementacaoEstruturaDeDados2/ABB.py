import matplotlib.pyplot as plt
import networkx as nx

#UTILIZE O GOOGLE COLAB PARA RODAR!
#NESSA VERSÃO EM PYTHON, É POSSÍVEL VISUALIZAR GRAFICAMENTE A GERAÇÃO DA ARVORE.

class Nodo:
    def __init__(self, chave):
        self.chave = chave
        self.esquerda = None
        self.direita = None


def inserir_arvore(raiz, chave):
    if raiz is None:
        return Nodo(chave)
    if chave < raiz.chave:
        raiz.esquerda = inserir_arvore(raiz.esquerda, chave)
    elif chave > raiz.chave:
        raiz.direita = inserir_arvore(raiz.direita, chave)
    return raiz


def busca_nodo(raiz, chave):
    if raiz is None or raiz.chave == chave:
        return raiz
    if chave < raiz.chave:
        return busca_nodo(raiz.esquerda, chave)
    else:
        return busca_nodo(raiz.direita, chave)


def menor_no(no):
    atual = no
    while atual and atual.esquerda:
        atual = atual.esquerda
    return atual


def remove_no(raiz, chave):
    if raiz is None:
        return raiz
    if chave < raiz.chave:
        raiz.esquerda = remove_no(raiz.esquerda, chave)
    elif chave > raiz.chave:
        raiz.direita = remove_no(raiz.direita, chave)
    else:
        if raiz.esquerda is None:
            return raiz.direita
        elif raiz.direita is None:
            return raiz.esquerda
        temp = menor_no(raiz.direita)
        raiz.chave = temp.chave
        raiz.direita = remove_no(raiz.direita, temp.chave)
    return raiz


def em_ordem(raiz):
    if raiz:
        em_ordem(raiz.esquerda)
        print(raiz.chave, end=" ")
        em_ordem(raiz.direita)


# Visualização com networkx + matplotlib
def build_graph(g, node, pos={}, x=0, y=0, layer=1):
    if node is None:
        return pos
    pos[node.chave] = (x, y)
    if node.esquerda:
        g.add_edge(node.chave, node.esquerda.chave)
        pos = build_graph(g, node.esquerda, pos, x - 1 / (2 ** layer), y - 1, layer + 1)
    if node.direita:
        g.add_edge(node.chave, node.direita.chave)
        pos = build_graph(g, node.direita, pos, x + 1 / (2 ** layer), y - 1, layer + 1)
    return pos


def desenhar_arvore(raiz):
    if raiz is None:
        print("Árvore está vazia.")
        return

    g = nx.DiGraph()
    pos = build_graph(g, raiz)

    plt.figure(figsize=(10, 6))
    nx.draw(
        g,
        pos,
        with_labels=True,
        node_size=1500,
        node_color="white",
        edgecolors="black",
        font_size=14,
        font_weight="bold"
    )
    plt.axis("off")
    plt.show()


# Impressão textual no terminal
def print_arvore(raiz, prefix="", is_left=True):
    if raiz is not None:
        print_arvore(raiz.direita, prefix + ("│   " if is_left else "    "), False)
        print(prefix + ("└── " if is_left else "┌── ") + str(raiz.chave))
        print_arvore(raiz.esquerda, prefix + ("    " if is_left else "│   "), True)


def menu():
    raiz = None
    while True:
        print("\n(1) Inserir\n(2) Buscar\n(3) Remover\n(4) Em-ordem\n(5) Imprimir texto\n(6) Visualizar gráfica\n(7) Sair")
        op = input("Escolha uma opção: ")

        if op == '1':
            chave = int(input("Digite a chave a ser inserida: "))
            raiz = inserir_arvore(raiz, chave)
            print("Inserido com sucesso.")

        elif op == '2':
            chave = int(input("Digite a chave a ser buscada: "))
            nodo = busca_nodo(raiz, chave)
            print("Chave encontrada na árvore." if nodo else "Chave não encontrada.")

        elif op == '3':
            chave = int(input("Digite a chave a ser removida: "))
            raiz = remove_no(raiz, chave)
            print("Removido com sucesso.")

        elif op == '4':
            print("Em ordem:", end=" ")
            em_ordem(raiz)
            print()

        elif op == '5':
            print("\nÁrvore (modo texto):")
            print_arvore(raiz)

        elif op == '6':
            print("Gerando visualização gráfica...")
            desenhar_arvore(raiz)

        elif op == '7':
            print("Encerrando.")
            break

        else:
            print("Opção inválida.")


if __name__ == "__main__":
    menu()
