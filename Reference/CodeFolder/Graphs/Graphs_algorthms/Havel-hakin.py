import sys

def todos_son_ceros(t):
    for d in t:
        if d != 0:
            return False
    return True

def esGrafica(grados):
    if sum(grados) % 2 != 0:
        return False
    
    grados = sorted(grados, reverse=True)    
    
    if todos_son_ceros(grados):
        return True

    d = grados[0]
    restantes = list(grados[1:])

    if d > len(restantes):
        return False
    
    for i in range(d):
        restantes[i] -= 1
        if restantes[i] < 0:
            return False
        
    return esGrafica(restantes)

def main():
    data = sys.stdin.read().strip().split()
    grad = list(map(int, data))
    print(esGrafica(grad))

if __name__ == "__main__":
    main()
