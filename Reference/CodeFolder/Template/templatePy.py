import sys

def main():
    data = sys.stdin.read().strip().split()
    numbers = list(map(int, data))
    
    output = []
    for num in numbers:
        output.append(f"Número leído: {num}")
    
    sys.stdout.write("\n".join(output))

if __name__ == '__main__':
    main()
