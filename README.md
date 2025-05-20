# ♻️ Garbage Collector por Contagem de Referência em C

Este projeto implementa um **sistema de gerenciamento de memória por contagem de referência** em linguagem C, com suporte a objetos do tipo `int`, `float`, `string` e `array`. Ele também inclui uma **suíte de testes** utilizando a biblioteca [Unity](https://github.com/ThrowTheSwitch/Unity) para garantir o correto funcionamento das operações.

---

## 📌 Descrição

Entender como linguagens modernas como Python, JavaScript ou Swift gerenciam memória é essencial para quem busca se aprofundar em sistemas, performance e engenharia de linguagens. Este projeto fornece uma base sólida de como um **coletor de lixo por contagem de referência** pode ser implementado do zero — desde a alocação de objetos até a liberação segura da memória quando objetos não são mais utilizados.

Além disso, ele simula operações típicas entre tipos e manipulação de arrays, tornando o projeto útil tanto para aprendizado quanto como referência prática.

---

## 🧠 Como Funciona

A **contagem de referência** funciona da seguinte forma:

- Cada objeto possui um contador (`refcount`) indicando quantas referências apontam para ele.
- Quando um novo objeto é referenciado, seu contador é incrementado (`refcount_inc`).
- Quando uma referência é descartada, o contador é decrementado (`refcount_dec`).
- Quando `refcount == 0`, o objeto pode ser **liberado da memória** com segurança.

### 🔍 Arrays e Sub-Referências

Objetos do tipo `ARRAY` armazenam ponteiros para outros objetos. Quando adicionamos um valor ao array, o GC **incrementa** a referência do valor. Ao remover ou substituir um valor, a referência antiga é **decrementada**. Esse processo garante que os objetos aninhados também sejam gerenciados corretamente e só serão liberados quando não houver mais referências.

---

## ⚙️ Funcionalidades

- ✅ Criação de objetos: `int`, `float`, `string` e `array`
- ➕ Operações de adição compatíveis entre tipos
- 📚 Manipulação segura de arrays (`get`, `set`)
- 🔁 Contagem automática de referências
- 🧪 Suíte de testes automatizada com Unity
- 🚨 Liberação segura de memória

---

## 🧪 Como Rodar os Testes

### 1. Clone o repositório com submodules

```bash
git clone --recurse-submodules https://github.com/edu292/refcount.git
cd refcount
```
> Caso tenha esquecido o `--recurse-submodules`, rode:
```bash
git submodule update --init
```

### 2. Compile com CMake
```bash
mkdir build
cd build
cmake ..
make
./mas_gc
```

## 📁 Estrutura do Projeto

| Arquivo        | Função                                    |
|----------------|-------------------------------------------|
| object.h/.c    | Lógica do GC e operações de objetos       |
| tester.c       | Suíte de testes usando Unity              |
| unity/         | Submódulo com a framework de testes Unity |
| CMakeLists.txt | Configuração do build com CMake           |
|  README.md     | Este arquivo ✍️                           |

## 💡 Exemplos de Uso

```c
object_t *a = new_integer(10);
object_t *b = new_integer(32);
object_t *sum = add(a, b);  // a e b são liberados, sum permanece
refcount_dec(sum);          // sum também é liberado
```
```c
object_t *arr = new_array(2);
array_set(arr, 0, new_string("foo"));
array_set(arr, 1, new_string("bar"));
refcount_dec(arr);  // Array e seus elementos são liberados
```

## 🌍 Por que isso importa?
Linguagens modernas escondem os detalhes do gerenciamento de memória — mas por baixo dos panos, estruturas como contagem de referência e mark-and-sweep são amplamente utilizadas. Entender como isso funciona:
- 💪 Aumenta sua compreensão sobre performance e consumo de memória
- 🛠️ Melhora sua habilidade de debugar aplicações complexas
- 🧵 Abre portas para trabalhar com linguagens de baixo nível ou até criar sua própria linguagem!