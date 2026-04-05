### Useful scripts
Para generar los templates:

Para crear los archivos de C++ y Python:

```bash
#!/bin/bash
for letra in "$@"; do
  cp template.cpp "$letra.cpp"
  cp template.py "$letra.py"
  touch "$letra.in"
done
```

```bash
touch gen
chmod +x gen
./gen a b f 
```

version con seguridad para no reemplazar archivos:

```bash
#!/bin/bash
for letra in "$@"; do
  cpp="$letra.cpp"
  py="$letra.py"
  inp="$letra.in"

  [[ -e "$cpp" ]] || cp template.cpp "$cpp"
  [[ -e "$py"  ]] || cp template.py "$py"
  [[ -e "$inp" ]] || touch "$inp"
done
```


Para compilar en C++:

```bash
#!/bin/bash
filename=$(basename "$1" .cpp)
g++ -std=c++17 -g -Wall "$1" -o "$filename"
```

```bash
touch gg
chmod +x gg
./gg a.cpp
```

### Ejecutar el código
Para ejecutar el código de C++:

```bash
./a < a.in
```

Para ejecutar el código de Python:

```bash
python3 a.py < a.in
```