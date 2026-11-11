#### Problema

Implemente a função int busca(int cod\_cli, char \*nome\_arquivo\_hash, char \*nome\_arquivo\_dados, int m), que realiza a busca de clientes em uma Tabela Hash armazenada em disco que usa tratamento de colisão por Encadeamento Exterior. A função recebe o código do cliente a ser buscado, os nomes dos dois arquivos que armazenam a tabela hash e o tamanho m da tabela. O arquivo de hash contém os compartimentos da tabela, e o arquivo de dados contém as listas encadeadas. A função de hash a ser usada é h(x) = x mod m.

Veja o slide 15 da aula de [Tratamento de Colisões por Encadeamento Exterior](http://www.ic.uff.br/~vanessa/material/ed/13-TabelasHash-Encadeamento-Exterior.pdf) para entender a estrutura dos arquivos utilizados.

**É OBRIGATÓRIO** usar o conhecimento da estrutura do arquivo hash para implementar a solução. Soluções que leiam registros desnecessários terão nota modificada para **ZERO**.

A tabela é armazenada em dois arquivos:

- **Arquivo de hash** (tabHash.dat): contém os m compartimentos da tabela. Cada compartimento guarda apenas um ponteiro para o primeiro registro da sua lista encadeada no arquivo de dados. Sua estrutura e funções auxiliares estão nos arquivos compartimento\_hash.h e compartimento\_hash.c
- **Arquivo de dados** (clientes.dat): contém os registros de clientes. Cada registro guarda o código e o nome do cliente, o ponteiro prox para o próximo registro da mesma lista e um flag que indica se o registro está OCUPADO ou LIBERADO. Sua estrutura e funções auxiliares estão nos arquivos cliente.h e cliente.c

Os ponteiros são **endereços lógicos**: o valor 4 indica o registro de número 4 do arquivo (contando a partir de 0), e não o byte 4. Para calcular o deslocamento usado no fseek, multiplique o ponteiro pelo tamanho do registro (tamanho\_compartimento() no arquivo de hash e tamanho\_cliente() no arquivo de dados). Ponteiros para NULL valem -1. A busca **não altera** nenhum dos dois arquivos.

Considere os arquivos abaixo, que usam h(x) = x mod 7. Eles estão no formato impresso pela função imprime\_arquivos, e os valores entre colchetes são os endereços lógicos de cada compartimento e de cada registro.

```
TABELA HASH:
[0]   0
[1]  -1
[2]   4
[3]   1
[4]  -1
[5]   2
[6]  -1

DADOS:
[  0]  49,         Joao,  -1,  OCUPADO
[  1]  59,        Maria,   3,  OCUPADO
[  2] 103,        Pedro,  -1,  OCUPADO
[  3]   3,        Janio,   5, LIBERADO
[  4]  51,          Ana,  -1,  OCUPADO
[  5]  87,     Mauricio,  -1,  OCUPADO
```

O compartimento [2] da tabela hash aponta para o endereço 4 do arquivo de dados. Nesse endereço está o cliente de chave 51 e nome Ana, e 51 mod 7 = 2. Já o compartimento [3] aponta para o endereço 1, onde começa a lista 1 -> 3 -> 5, com os clientes 59, 3 e 87. Todos eles têm hash 3.

#### Entrada

- Código do cliente a ser buscado
- Os arquivos tabHash.dat e clientes.dat com a tabela, que devem estar no diretório onde o programa é executado (eles não são lidos do teclado). Cada caso de teste fornece esses dois arquivos

O tamanho da tabela é m = 7 em todos os casos de teste. Ele é definido pela constante M do arquivo encadeamento\_exterior.c.

#### Saída

- A linha "REGISTROS ACESSADOS:", impressa pelo main
- Todos os registros lidos do arquivo de dados ao longo da busca, na ordem em que foram lidos, impressos com a função imprime\_cliente
- A linha "RESULTADO: " seguida do valor retornado pela função, que é o endereço lógico onde o registro foi encontrado, ou -1 caso não exista registro com aquela chave na tabela. A linha "RESULTADO: " também é impressa pelo main

## Exemplos

Os exemplos abaixo usam os arquivos mostrados acima, que são os da [tabela A](#tabela-a-arquivos-do-enunciado).

#### Exemplo 1

Na busca pela chave **8**, seu programa deve retornar -1, pois o registro não existe na tabela. Nenhum registro é impresso, pois nenhum registro é acessado: 8 mod 7 = 1, e o compartimento 1 tem ponteiro -1, ou seja, a lista encadeada associada a esse compartimento está vazia. Esse é o [caso de teste 1](casos-teste/1).

```
REGISTROS ACESSADOS:
RESULTADO: -1
```

#### Exemplo 2

Caso o registro buscado esteja marcado como LIBERADO, ele não conta como encontrado, e a busca continua pela lista. Por exemplo, a busca pela chave **3** gera o resultado abaixo. Esse é o [caso de teste 5](casos-teste/5).

```
REGISTROS ACESSADOS:
 59,        Maria,   3,  OCUPADO
  3,        Janio,   5, LIBERADO
 87,     Mauricio,  -1,  OCUPADO
RESULTADO: -1
```

#### Exemplo 3

A busca pela chave **103** gera o resultado abaixo. Esse é o [caso de teste 2](casos-teste/2).

```
REGISTROS ACESSADOS:
103,        Pedro,  -1,  OCUPADO
RESULTADO: 2
```

#### Função imprime\_arquivos

Use essa função caso você queira ver o conteúdo dos dois arquivos de entrada. Para isso, descomente a chamada dela no main. Não esqueça de comentá-la de novo antes de entregar a versão final do seu código, caso contrário isso afetará a saída gerada pelo seu programa, e os casos de teste irão falhar.

## Tabelas usadas nos casos de teste

Todas as tabelas têm m = 7 compartimentos. Cada compartimento ocupa 4 bytes no arquivo de hash, e cada registro de cliente ocupa 112 bytes no arquivo de dados. Os conteúdos dos arquivos estão no formato impresso pela função imprime\_arquivos.

### Tabela A: arquivos do enunciado

Listas: compartimento 0: 0 (49). Compartimento 2: 4 (51). Compartimento 3: 1 (59) -> 3 (3, LIBERADO) -> 5 (87). Compartimento 5: 2 (103).

```
TABELA HASH:
[0]   0
[1]  -1
[2]   4
[3]   1
[4]  -1
[5]   2
[6]  -1

DADOS:
[  0]  49,         Joao,  -1,  OCUPADO
[  1]  59,        Maria,   3,  OCUPADO
[  2] 103,        Pedro,  -1,  OCUPADO
[  3]   3,        Janio,   5, LIBERADO
[  4]  51,          Ana,  -1,  OCUPADO
[  5]  87,     Mauricio,  -1,  OCUPADO
```

### Tabela B: registro de Pedro liberado

Igual à tabela A, exceto pelo registro de Pedro (endereço 2), que está LIBERADO.

```
TABELA HASH:
[0]   0
[1]  -1
[2]   4
[3]   1
[4]  -1
[5]   2
[6]  -1

DADOS:
[  0]  49,         Joao,  -1,  OCUPADO
[  1]  59,        Maria,   3,  OCUPADO
[  2] 103,        Pedro,  -1, LIBERADO
[  3]   3,        Janio,   5, LIBERADO
[  4]  51,          Ana,  -1,  OCUPADO
[  5]  87,     Mauricio,  -1,  OCUPADO
```

### Tabela C: lista com cinco registros

Listas: compartimento 0: 0 (49). Compartimento 2: 4 (51). Compartimento 3: 1 (59) -> 3 (17) -> 5 (87) -> 6 (10) -> 7 (24). Compartimento 5: 2 (5).

```
TABELA HASH:
[0]   0
[1]  -1
[2]   4
[3]   1
[4]  -1
[5]   2
[6]  -1

DADOS:
[  0]  49,         Joao,  -1,  OCUPADO
[  1]  59,        Maria,   3,  OCUPADO
[  2]   5,       Carlos,  -1,  OCUPADO
[  3]  17,      Vanessa,   5,  OCUPADO
[  4]  51,          Ana,  -1,  OCUPADO
[  5]  87,     Mauricio,   6,  OCUPADO
[  6]  10,      Gabriel,   7,  OCUPADO
[  7]  24,         Lara,  -1,  OCUPADO
```

### Tabela D: tabela vazia

Todos os compartimentos valem -1, e o arquivo de dados não tem nenhum registro.

```
TABELA HASH:
[0]  -1
[1]  -1
[2]  -1
[3]  -1
[4]  -1
[5]  -1
[6]  -1

DADOS:
```

### Tabela E: um único registro

Listas: compartimento 3: 0 (10).

```
TABELA HASH:
[0]  -1
[1]  -1
[2]  -1
[3]   0
[4]  -1
[5]  -1
[6]  -1

DADOS:
[  0]  10,      Gabriel,  -1,  OCUPADO
```

### Tabela F: ponteiros para endereços anteriores

Nesta tabela, o próximo registro de uma lista está num endereço **anterior** do arquivo de dados. Por isso, ler o arquivo de dados em sequência não dá a ordem da lista.

Listas: compartimento 0: 4 (7, LIBERADO) -> 1 (14). Compartimento 1: 5 (1) -> 3 (8) -> 0 (15). Compartimento 6: 2 (13).

```
TABELA HASH:
[0]   4
[1]   5
[2]  -1
[3]  -1
[4]  -1
[5]  -1
[6]   2

DADOS:
[  0]  15,        Fabio,  -1,  OCUPADO
[  1]  14,          Bia,  -1,  OCUPADO
[  2]  13,         Hugo,  -1,  OCUPADO
[  3]   8,          Eva,   0,  OCUPADO
[  4]   7,         Gina,   1, LIBERADO
[  5]   1,         Davi,   3,  OCUPADO
```

## Casos de teste:

Os casos de teste estão na pasta [casos-teste](casos-teste). Cada caso tem 4 arquivos:

- entrada.txt: o que deve ser digitado no teclado (a chave a ser buscada)
- tabHash.dat e clientes.dat: a tabela onde a busca é feita (arquivos binários)
- saida.txt: a saída esperada do programa

|Caso|Tabela|Chave|Descrição|Arquivos|
|---|---|---|---|---|
|[1](casos-teste/1)|[A](#tabela-a-arquivos-do-enunciado)|8|Compartimento vazio: nenhum registro é lido (exemplo 1)|[entrada.txt](casos-teste/1/entrada.txt) [tabHash.dat](casos-teste/1/tabHash.dat) [clientes.dat](casos-teste/1/clientes.dat) [saida.txt](casos-teste/1/saida.txt)|
|[2](casos-teste/2)|[A](#tabela-a-arquivos-do-enunciado)|103|Chave no único registro da lista (exemplo 3)|[entrada.txt](casos-teste/2/entrada.txt) [tabHash.dat](casos-teste/2/tabHash.dat) [clientes.dat](casos-teste/2/clientes.dat) [saida.txt](casos-teste/2/saida.txt)|
|[3](casos-teste/3)|[A](#tabela-a-arquivos-do-enunciado)|49|Chave no endereço 0 do arquivo de dados|[entrada.txt](casos-teste/3/entrada.txt) [tabHash.dat](casos-teste/3/tabHash.dat) [clientes.dat](casos-teste/3/clientes.dat) [saida.txt](casos-teste/3/saida.txt)|
|[4](casos-teste/4)|[A](#tabela-a-arquivos-do-enunciado)|59|Chave no primeiro registro de uma lista com três registros: a busca para nele|[entrada.txt](casos-teste/4/entrada.txt) [tabHash.dat](casos-teste/4/tabHash.dat) [clientes.dat](casos-teste/4/clientes.dat) [saida.txt](casos-teste/4/saida.txt)|
|[5](casos-teste/5)|[A](#tabela-a-arquivos-do-enunciado)|3|Chave num registro LIBERADO: a lista é percorrida até o fim (exemplo 2)|[entrada.txt](casos-teste/5/entrada.txt) [tabHash.dat](casos-teste/5/tabHash.dat) [clientes.dat](casos-teste/5/clientes.dat) [saida.txt](casos-teste/5/saida.txt)|
|[6](casos-teste/6)|[A](#tabela-a-arquivos-do-enunciado)|87|Chave no último registro da lista, depois de um registro LIBERADO|[entrada.txt](casos-teste/6/entrada.txt) [tabHash.dat](casos-teste/6/tabHash.dat) [clientes.dat](casos-teste/6/clientes.dat) [saida.txt](casos-teste/6/saida.txt)|
|[7](casos-teste/7)|[A](#tabela-a-arquivos-do-enunciado)|10|Chave não existe: a lista do compartimento é percorrida até o fim|[entrada.txt](casos-teste/7/entrada.txt) [tabHash.dat](casos-teste/7/tabHash.dat) [clientes.dat](casos-teste/7/clientes.dat) [saida.txt](casos-teste/7/saida.txt)|
|[8](casos-teste/8)|[A](#tabela-a-arquivos-do-enunciado)|5|Chave não existe numa lista com um único registro|[entrada.txt](casos-teste/8/entrada.txt) [tabHash.dat](casos-teste/8/tabHash.dat) [clientes.dat](casos-teste/8/clientes.dat) [saida.txt](casos-teste/8/saida.txt)|
|[9](casos-teste/9)|[B](#tabela-b-registro-de-pedro-liberado)|103|A única ocorrência da chave está num registro LIBERADO|[entrada.txt](casos-teste/9/entrada.txt) [tabHash.dat](casos-teste/9/tabHash.dat) [clientes.dat](casos-teste/9/clientes.dat) [saida.txt](casos-teste/9/saida.txt)|
|[10](casos-teste/10)|[C](#tabela-c-lista-com-cinco-registros)|38|Chave não existe numa lista com cinco registros|[entrada.txt](casos-teste/10/entrada.txt) [tabHash.dat](casos-teste/10/tabHash.dat) [clientes.dat](casos-teste/10/clientes.dat) [saida.txt](casos-teste/10/saida.txt)|
|[11](casos-teste/11)|[C](#tabela-c-lista-com-cinco-registros)|24|Chave no último registro de uma lista com cinco registros|[entrada.txt](casos-teste/11/entrada.txt) [tabHash.dat](casos-teste/11/tabHash.dat) [clientes.dat](casos-teste/11/clientes.dat) [saida.txt](casos-teste/11/saida.txt)|
|[12](casos-teste/12)|[C](#tabela-c-lista-com-cinco-registros)|17|Chave no meio da lista: os registros seguintes não são lidos|[entrada.txt](casos-teste/12/entrada.txt) [tabHash.dat](casos-teste/12/tabHash.dat) [clientes.dat](casos-teste/12/clientes.dat) [saida.txt](casos-teste/12/saida.txt)|
|[13](casos-teste/13)|[C](#tabela-c-lista-com-cinco-registros)|5|Chave em outro compartimento da tabela que tem a lista longa|[entrada.txt](casos-teste/13/entrada.txt) [tabHash.dat](casos-teste/13/tabHash.dat) [clientes.dat](casos-teste/13/clientes.dat) [saida.txt](casos-teste/13/saida.txt)|
|[14](casos-teste/14)|[D](#tabela-d-tabela-vazia)|10|Tabela vazia, com arquivo de dados vazio|[entrada.txt](casos-teste/14/entrada.txt) [tabHash.dat](casos-teste/14/tabHash.dat) [clientes.dat](casos-teste/14/clientes.dat) [saida.txt](casos-teste/14/saida.txt)|
|[15](casos-teste/15)|[E](#tabela-e-um-único-registro)|10|Chave no único registro da tabela|[entrada.txt](casos-teste/15/entrada.txt) [tabHash.dat](casos-teste/15/tabHash.dat) [clientes.dat](casos-teste/15/clientes.dat) [saida.txt](casos-teste/15/saida.txt)|
|[16](casos-teste/16)|[E](#tabela-e-um-único-registro)|17|Chave não existe, mas cai no mesmo compartimento do único registro|[entrada.txt](casos-teste/16/entrada.txt) [tabHash.dat](casos-teste/16/tabHash.dat) [clientes.dat](casos-teste/16/clientes.dat) [saida.txt](casos-teste/16/saida.txt)|
|[17](casos-teste/17)|[F](#tabela-f-ponteiros-para-endereços-anteriores)|15|Chave no fim da lista 5 -> 3 -> 0, que aponta para endereços anteriores|[entrada.txt](casos-teste/17/entrada.txt) [tabHash.dat](casos-teste/17/tabHash.dat) [clientes.dat](casos-teste/17/clientes.dat) [saida.txt](casos-teste/17/saida.txt)|
|[18](casos-teste/18)|[F](#tabela-f-ponteiros-para-endereços-anteriores)|7|Chave no primeiro registro da lista, que está LIBERADO|[entrada.txt](casos-teste/18/entrada.txt) [tabHash.dat](casos-teste/18/tabHash.dat) [clientes.dat](casos-teste/18/clientes.dat) [saida.txt](casos-teste/18/saida.txt)|
|[19](casos-teste/19)|[F](#tabela-f-ponteiros-para-endereços-anteriores)|14|Chave depois de um registro LIBERADO|[entrada.txt](casos-teste/19/entrada.txt) [tabHash.dat](casos-teste/19/tabHash.dat) [clientes.dat](casos-teste/19/clientes.dat) [saida.txt](casos-teste/19/saida.txt)|
|[20](casos-teste/20)|[F](#tabela-f-ponteiros-para-endereços-anteriores)|22|Chave não existe: a lista 5 -> 3 -> 0 é percorrida até o fim|[entrada.txt](casos-teste/20/entrada.txt) [tabHash.dat](casos-teste/20/tabHash.dat) [clientes.dat](casos-teste/20/clientes.dat) [saida.txt](casos-teste/20/saida.txt)|

### Como compilar e rodar os testes

O projeto tem um Makefile. Abra a pasta do projeto no VSCode e use o terminal integrado (menu Terminal > New Terminal). Os comandos abaixo devem ser executados na pasta do projeto:

|Comando|O que faz|
|---|---|
|`make`|Compila o programa, gerando o executável encadeamento\_exterior|
|`make test`|Roda todos os casos de teste e mostra quais passaram e quais falharam|
|`make caso N=4`|Roda apenas o caso 4 e mostra as diferenças entre a sua saída e a saída esperada|
|`make clean`|Apaga o executável e a pasta execucao|

No `make caso`, as linhas marcadas com < são da sua saída e as linhas marcadas com > são da saída esperada. A saída do seu programa fica gravada em execucao/saida\_obtida.txt.

Para usar o make é preciso ter o gcc e o make instalados. No Linux e no macOS eles normalmente já estão disponíveis (no macOS, instale as ferramentas de linha de comando com `xcode-select --install`, se necessário). No Windows, use o WSL ou o MSYS2.

Os comandos `make test` e `make caso` copiam os arquivos .dat do caso para a pasta execucao antes de rodar o programa. Se for rodar o programa manualmente (por exemplo, `./encadeamento_exterior` e digitar a chave), copie antes os arquivos tabHash.dat e clientes.dat do caso para o diretório de execução, senão o programa não vai encontrar a tabela.

#### Arquivos a modificar

Modifique apenas o arquivo **encadeamento\_exterior.c**, com sua função de busca implementada.

## Dicas Importantes:

- A entrada e a saída já são tratadas no arquivo fornecido para ler e imprimir os dados no formato esperado pela questão. Vocês devem APENAS implementar a função solicitada no problema
- Os arquivos cliente.c e compartimento\_hash.c (e seus respectivos .h) já contêm as funções para ler compartimentos e clientes. Não é preciso alterá-los. As funções de encadeamento\_exterior.c estão declaradas em encadeamento\_exterior.h
- Leia apenas o compartimento h(cod\_cli) do arquivo de hash, posicionando o cursor com fseek. Não é preciso ler a tabela inteira
- Siga os ponteiros prox para percorrer a lista. O próximo registro da lista não é necessariamente o seguinte no arquivo de dados (veja a [tabela F](#tabela-f-ponteiros-para-endereços-anteriores)). Ler o arquivo de dados em sequência acessa registros que não pertencem à lista, ou acessa os registros da lista na ordem errada
- O endereço 0 é um endereço válido. Apenas o valor -1 representa NULL
- Se o compartimento valer -1, a lista está vazia, e nenhum registro deve ser lido do arquivo de dados
- Um registro LIBERADO não conta como encontrado, mesmo que tenha a chave buscada. Nesse caso, a busca continua pela lista
- Ao encontrar a chave num registro OCUPADO, pare a busca. Os registros seguintes da lista não devem ser lidos
- Imprima cada registro com imprime\_cliente assim que ele for lido, e leia cada registro uma única vez: se o mesmo registro for impresso duas vezes, a saída vai ficar diferente da esperada
