# Teste desenvolvedor 1

O programa foi escrito na linguagem **C**. Input e output são feitos via arquivo e podem ser especificados por linha de comando. Instruções que façam com que um rover saia da planície são ignoradas e uma mensagem de alerta é emitida pelo programa.


## Formas de uso

    moverover.exe C:\entrada.txt C:\saida.txt
Roda o programa utilizando `C:\entrada.txt` como arquivo de input e gera a saída em `C:\saida.txt`

---

    moverover.exe
Entende que o arquivo de entrada se chama `input.txt` e está localizado no mesmo diretório que o programa. 
Gera a saída em arquivo chamado `output.txt` no mesmo diretório do programa.

---

    moverover.exe C:\entrada
Utiliza `C:\entrada.txt` como arquivo de entrada, mas gera a saída como `output.txt` no mesmo diretório do programa

---

    moverover -t
Utiliza o arquivo de teste como entrada e efetua rotina de teste após a execução. 
Gera a saída em arquivo chamado `output.txt` no mesmo diretório do programa.

---

    moverover -t C:\saida.txt
Utiliza o arquivo de teste como entrada e efetua rotina de teste após a execução. Gera a saída em `C:\saida.txt`

## Compilando

Basta ter um compilador C, como o gcc. Ex: `gcc -o moverover.exe moverover.c`.
O arquivo `.exe` foi compilado em uma máquina Windows 10 x64 com MinGW
