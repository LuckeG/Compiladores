
# 🔵 Manual do Interpretador Flex/Bison

Este interpretador foi desenvolvido em C com as ferramentas **Flex** (scanner) e **Bison** (parser) para processar uma linguagem fictícia com variáveis, vetores, controle de fluxo, entrada e saída de dados.

---

## 🧱 Estrutura do Programa

O programa começa com `INICIO` e termina com `FIM`.

```plaintext
INICIO
    // comandos aqui
FIM
```

---

## 📦 Declaração de Variáveis

Tipos suportados:

- `INTEIRO`
- `REAL`
- `TEXTO`

### Exemplo:

```plaintext
VAR INTEIRO idade;
VAR REAL altura;
VAR TEXTO nome;
```

---

## 📝 Atribuição

Atribui valores às variáveis:

```plaintext
idade = 18;
altura = 1.75;
nome = "Lucas";
```

---

## 📥 Entrada e 📤 Saída

### Leitura com `LEIA`:

```plaintext
LEIA(idade);
LEIA(nome);
```

### Impressão com `print`:

```plaintext
print(idade);
print("Olá, " + nome);
```

---

## ➕ Expressões e Operadores

### Aritméticos

| Operador | Significado     |
|----------|-----------------|
| `+`      | Soma            |
| `-`      | Subtração       |
| `*`      | Multiplicação   |
| `/`      | Divisão         |

### Relacionais

| Operador | Significado     |
|----------|-----------------|
| `>`      | Maior que       |
| `<`      | Menor que       |
| `==`     | Igual           |
| `!=`     | Diferente       |
| `>=`     | Maior ou igual  |
| `<=`     | Menor ou igual  |

### Exemplo:

```plaintext
idade = 20 + 5;
x = (idade >= 18);
```

---

## 🔁 Controle de Fluxo

### Condicional: `SE` / `SENAO`

```plaintext
SE (idade >= 18) {
    ESCREVA("Maior de idade");
} SENAO {
    ESCREVA("Menor de idade");
}
```

### Repetição: `while`

```plaintext
while (x < 5) {
    x = x + 1;
}
```

---

## 📚 Vetores

### Declaração

```plaintext
VAR INTEIRO v[3];
```

### Atribuição e Acesso

```plaintext
v[0] = 10;
print(v[0]);
```

---

## 💬 Comentários

### Linha única

```plaintext
// Isso é um comentário
```

---

## ✅ Exemplo 1: Condicão

```plaintext
INICIO
// Declaracao de variaveis
VAR REAL salario;
VAR INTEIRO idade;
VAR TEXTO nome;
VAR TEXTO mensagem;

// Interacao com o usuario
print("Digite seu nome: ");
LEIA(nome);

print("Digite sua idade: ");
LEIA(idade);

// Estrutura condicional
SE (idade >= 18) {
    print("Voce é maior de idade.");
    salario = 2500.50;
} SENAO {
    print("Voce é menor de idade.");
    salario = 0.0;
}

// Concatenacao de texto e operacoes
print("Ola " + nome + " seu salario é de R$ " +salario);
print("Fim do programa.");
FIM
```

---

## ✅ Exemplo 2: Repetição

```plaintext
INICIO
VAR INTEIRO contador;
contador = 1;
print("Contando ate 10:");
while (contador <= 10) {
    print(contador);
    contador = contador + 1;
}
print("Fim do programa.");
FIM
```

---

## ✅ Exemplo 3: Vetores

```plaintext
INICIO
// Vetores (arrays)
VAR REAL notas[4];
print("Preenchendo vetor de notas...");
notas[0] = 7.5;
notas[1] = 9.0;
notas[2] = 5.5 + 1;
notas[3] = 8.0;

print("A segunda nota foi:");
print(notas[1]);

VAR REAL soma;
soma = notas[0] + notas[1] + notas[2] + notas[3];
print("A media das notas eh:");
print(soma / 4);

print("Fim do programa.");
FIM
```

---

## ✅ Problema: Fibonacci

```plaintext
INICIO
// Vetores (arrays)
VAR REAL notas[4];
print("Preenchendo vetor de notas...");
notas[0] = 7.5;
notas[1] = 9.0;
// O operador '++' nao foi implementado, usamos a soma.
notas[2] = 5.5 + 1;
notas[3] = 8.0;

print("A segunda nota foi:");
print(notas[1]);

VAR REAL soma;
soma = notas[0] + notas[1] + notas[2] + notas[3];
print("A media das notas eh:");
print(soma / 4);

print("Fim do programa.");
FIM
```

---

## ⚙️ Como Compilar e Executar

```bash
flex scanner.l
bison -d parser.y
gcc -o interpretador parser.tab.c lex.yy.c -lm
./interpretador entradas.txt
```
