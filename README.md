
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

## ✅ Exemplo Completo

```plaintext
INICIO
    VAR TEXTO nome;
    VAR INTEIRO idade;
    
    LEIA(nome);
    LEIA(idade);

    SE (idade >= 18) {
        print(nome + " é maior de idade.");
    } SENAO {
        print(nome + " é menor de idade.");
    }
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
