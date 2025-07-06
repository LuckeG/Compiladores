
# Recursos da Linguagem

Este projeto implementa um interpretador de uma **linguagem de programação simples**, utilizando **Lex** (Flex) e **Yacc** (Bison), que simula uma linguagem com variáveis, expressões, controle de fluxo e vetores.

---

## 📜 Visão Geral

O código fornece um pequeno interpretador que:
- Permite **declarar variáveis** de tipos `INTEIRO`, `REAL` e `TEXTO` (strings).
- Permite declarar **vetores** (arrays).
- Permite realizar **operações aritméticas** e **comparações**.
- Suporta **comandos de controle de fluxo** como `SE`, `SENAO`, e `while`.
- Possui comandos de entrada e saída: `LEIA` e `print`.


## 🧠 Funcionalidades Suportadas

### Tipos
```txt
VAR INTEIRO x;
VAR REAL y;
VAR TEXTO msg;
VAR INTEIRO v[10];  // vetor de inteiros
```

### Atribuições e expressões
```txt
x = 5;
y = 3.14 + x;
msg = "Olá " + "Mundo!";
```

### Controle de fluxo
```txt
SE (x > 0) {
  print("Positivo");
} SENAO {
  print("Zero ou negativo");
}

while (x < 10) {
  x = x + 1;
}
```

### Entrada e saída
```txt
LEIA(x);
print(x);
```

---


## 📄 Exemplo de Código da Linguagem

```txt
INICIO
  VAR INTEIRO x;
  VAR TEXTO nome;
  LEIA(nome);
  x = 5;
  SE (x > 3) {
    print("Maior que 3");
  } SENAO {
    print("Menor ou igual a 3");
  }
FIM
```

---

## 🧱 Componentes Internos

- **Tabela de Símbolos**: Estrutura encadeada que armazena variáveis, tipos e valores.
- **Árvore de Sintaxe (AST)**: Representa comandos e expressões para posterior avaliação.
- **Função `eval`**: Interpreta a AST de forma recursiva, realizando cálculos, atribuições, controle de fluxo etc.
- **Funções `novo_no_*`**: Criam diferentes tipos de nós para representar elementos da linguagem.

---

## 📌 Observações

- A linguagem é case-sensitive.
- Vetores aceitam apenas índices inteiros e verificações de limite são realizadas.
- Operações com strings são suportadas apenas com `+` (concatenação).
