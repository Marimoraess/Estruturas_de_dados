#### Problema

Implemente a função int busca(int chave, char *nome\_arquivo\_metadados, char *nome\_arquivo\_indice, char *nome\_arquivo\_dados) que recebe como parâmetro a chave a ser buscada e os nomes dos 3 arquivos que armazenam a árvore B+ e retorna o endereço do nó em que a chave está ou que deveria estar. A função deve imprimir os nós avaliados até que o nó onde a chave está ou deveria estar tenha sido encontrado (use as funções de impressão fornecidas). 

A árvore armazena registros de clientes, cuja estrutura e funções auxiliares estão nos arquivos cliente.h e cliente.c. Ela é armazenada em três arquivos:

- **Arquivo de metadados** (metadados.dat): contém a ordem d da árvore B+, o ponteiro para a raiz da árvore, e um flag que indica se a raiz é folha ou um nó interno. Sua estrutura e funções auxiliares estão nos arquivos metadados.h e metadados.c
- **Arquivo de índice** (indice.dat): contém os nós internos da árvore B+, e sua estrutura e funções auxiliares estão nos arquivos no\_interno.h e no\_interno.c
- **Arquivo de dados** (clientes.dat): contém os nós folha da árvore B+, e sua estrutura e funções auxiliares estão nos arquivos no\_folha.h e no\_folha.c

Todos os ponteiros são posições (em bytes) dentro do arquivo de índice ou do arquivo de dados. Ponteiros nulos valem -1. A busca **não altera** nenhum dos três arquivos.

#### Entrada

- Chave a ser buscada
- Os arquivos metadados.dat, indice.dat e clientes.dat com a árvore, que devem estar no diretório onde o programa é executado (eles não são lidos do teclado). Cada caso de teste fornece esses três arquivos

#### Saída 

- Todos os nós avaliados durante a busca, impressos com as funções imprime\_no\_interno e imprime\_no\_folha
- A linha "RESULTADO DA BUSCA: " seguida do endereço do nó folha onde a chave está ou deveria estar 

#### Exemplo 

Usando a [árvore D](#árvore-d-três-níveis), e assumindo que se deseja buscar a chave **20**, seu programa deve gerar a seguinte saída. 

```
NO INTERNO: (m = 1, pt pai = -1, aponta folha = 0)
	[48]  37 [96]  -1 [-1]  -1 [-1]  -1  [-1] 

NO INTERNO: (m = 2, pt pai = 0, aponta folha = 1)
	[0]  15 [428]  25 [856]  -1 [-1]  -1  [-1] 

NO FOLHA: (m = 2, pt pai = 48, pt prox = 856)
	15, Jose
	20, Mariana
		
RESULTADO DA BUSCA: 428
```

Uma busca pela chave **18** resultaria na mesma resposta acima, apesar dessa chave não existir no nó folha exibido na resposta. Se ela existisse, estaria nesse nó. 

#### Função imprime\_no\_interno

A função imprime um nó interno que foi lido do arquivo de índice (use a função le\_no\_interno para isso). Na primeira linha são impressos os metadados do nó. Na segunda linha, são impressos os ponteiros (entre colchetes) e as chaves do nó, conforme exemplo abaixo. Ponteiros para NULL são representados por -1. Chaves não existentes (ou seja, espaços vazios no nó) são representadas por -1. O exemplo abaixo mostra um nó raiz (pois pt pai = -1), que não aponta para uma folha (pois aponta folha = 0) que tem a chave 37. O ponteiro da esquerda dessa chave é o 48 e o da direita é o 96. Os valores dos ponteiros são absolutos, ou seja, não é necessário calcular nada para usar esse valor. Para acessar o nó apontado pelo ponteiro 48, basta fazer fseek (no arquivo de índice, pois esse nó aponta para um outro nó interno da árvore) usando 48 como valor do descolamento, e SEEK\_SET.


```
NO INTERNO: (m = 1, pt pai = -1, aponta folha = 0)
	[48]  37 [96]  -1 [-1]  -1 [-1]  -1  [-1] 
```

#### Função imprime\_no\_folha

A função imprime um nó folha que foi lido do arquivo de dados (use a função le\_no\_folha para isso). Na primeira linha são impressos os metadados do nó. Na segunda linha, são impressos os registros armazenados no nó (que nesse exemplo, são registros de clientes com código e nome), conforme exemplo abaixo. No exemplo abaixo, existem dois registros armazenados nessa folha (com chaves 15 e 20), o nó pai tem endereço 48 e o próximo nó folha tem endereço 856. 

```
NO FOLHA: (m = 2, pt pai = 48, pt prox = 856)
	15, Jose
	20, Mariana
```

#### Função imprime\_arquivos

Use essa função caso você queira ver o conteúdo dos três arquivos de entrada. Não esqueça de comentar o uso dela antes de entregar a versão final do seu código, caso contrário isso afetará a saída gerada pelo seu programa, e os casos de teste irão falhar. 

## Árvores usadas nos casos de teste

Em todas as árvores, d = 2 (cada nó tem no mínimo 2 e no máximo 4 chaves, exceto a raiz, que pode ter menos). Cada nó interno ocupa 48 bytes no arquivo de índice, e cada nó folha ocupa 428 bytes no arquivo de dados. Logo, os nós internos estão nas posições 0, 48, 96, ... do arquivo de índice, e os nós folha estão nas posições 0, 428, 856, 1284, ... do arquivo de dados. Note que a mesma posição pode existir nos dois arquivos: é o flag aponta folha do nó interno (ou o flag raiz folha dos metadados, no caso da raiz) que diz em qual arquivo o ponteiro deve ser usado.

Nos desenhos, a posição de cada nó aparece embaixo dele: "ind" indica uma posição no arquivo de índice, e "dad" indica uma posição no arquivo de dados. Os conteúdos dos arquivos estão no formato impresso pela função imprime\_arquivos.

### Árvore A: a raiz é uma folha

```
    [10, 13]
      dad 0
```

```
*** Arquivo de Metadados ***
d = 2, pt raiz = 0, raiz folha = 1
pt prox no interno livre = 0, pt prox no folha livre = 428


*** Arquivo de Indice ***

*** Arquivo de Dados ***
(((Endereco 0)))
NO FOLHA: (m = 2, pt pai = -1, pt prox = -1)
	10, Joao
	13, Ana Maria
		
```

### Árvore B: dois níveis

```
                      [15, 25]
                        ind 0
          /               |               \
    [10, 13]      [15, 20, 21, 23]    [25, 35, 37]
      dad 0            dad 428           dad 856
```

```
*** Arquivo de Metadados ***
d = 2, pt raiz = 0, raiz folha = 0
pt prox no interno livre = 48, pt prox no folha livre = 1284


*** Arquivo de Indice ***
(((Endereco 0)))
NO INTERNO: (m = 2, pt pai = -1, aponta folha = 1)
	[0]  15 [428]  25 [856]  -1 [-1]  -1  [-1] 


*** Arquivo de Dados ***
(((Endereco 0)))
NO FOLHA: (m = 2, pt pai = 0, pt prox = 428)
	10, Joao
	13, Ana Maria
		
(((Endereco 428)))
NO FOLHA: (m = 4, pt pai = 0, pt prox = 856)
	15, Jose
	20, Mariana
	21, Bruna
	23, Bruno

(((Endereco 856)))
NO FOLHA: (m = 3, pt pai = 0, pt prox = -1)
	25, Ronaldo
	35, Marcela
	37, Leonardo
	
```

### Árvore C: dois níveis, com a raiz cheia

```
                                 [15, 25, 40, 70]
                                       ind 0
       /                |                 |                \             \
 [10, 13]      [15, 20, 21, 23]     [25, 35, 37]       [40, 45]       [70, 77]
   dad 0            dad 428            dad 856         dad 1284       dad 1712
```

```
*** Arquivo de Metadados ***
d = 2, pt raiz = 0, raiz folha = 0
pt prox no interno livre = 48, pt prox no folha livre = 2140


*** Arquivo de Indice ***
(((Endereco 0)))
NO INTERNO: (m = 4, pt pai = -1, aponta folha = 1)
	[0]  15 [428]  25 [856]  40 [1284]  70  [1712] 


*** Arquivo de Dados ***
(((Endereco 0)))
NO FOLHA: (m = 2, pt pai = 0, pt prox = 428)
	10, Joao
	13, Ana Maria
		
(((Endereco 428)))
NO FOLHA: (m = 4, pt pai = 0, pt prox = 856)
	15, Jose
	20, Mariana
	21, Bruna
	23, Bruno

(((Endereco 856)))
NO FOLHA: (m = 3, pt pai = 0, pt prox = 1284)
	25, Ronaldo
	35, Marcela
	37, Leonardo
	
(((Endereco 1284)))
NO FOLHA: (m = 2, pt pai = 0, pt prox = 1712)
	40, Aline
	45, Juca
		
(((Endereco 1712)))
NO FOLHA: (m = 2, pt pai = 0, pt prox = -1)
	70, Nicolas
	77, Lina
		
```

### Árvore D: três níveis

```
                                      [37]
                                      ind 0
                    /                                   \
               [15, 25]                              [39, 55]
                ind 48                                ind 96
        /          |          \               /          |          \
 [10, 13]      [15, 20]      [25, 35]     [37, 38]    [39, 50]    [55, 60]
   dad 0       dad 428       dad 856      dad 1284    dad 1712    dad 2140
```

```
*** Arquivo de Metadados ***
d = 2, pt raiz = 0, raiz folha = 0
pt prox no interno livre = 144, pt prox no folha livre = 2568


*** Arquivo de Indice ***
(((Endereco 0)))
NO INTERNO: (m = 1, pt pai = -1, aponta folha = 0)
	[48]  37 [96]  -1 [-1]  -1 [-1]  -1  [-1] 

(((Endereco 48)))
NO INTERNO: (m = 2, pt pai = 0, aponta folha = 1)
	[0]  15 [428]  25 [856]  -1 [-1]  -1  [-1] 

(((Endereco 96)))
NO INTERNO: (m = 2, pt pai = 0, aponta folha = 1)
	[1284]  39 [1712]  55 [2140]  -1 [-1]  -1  [-1] 


*** Arquivo de Dados ***
(((Endereco 0)))
NO FOLHA: (m = 2, pt pai = 48, pt prox = 428)
	10, Joao
	13, Ana Maria
		
(((Endereco 428)))
NO FOLHA: (m = 2, pt pai = 48, pt prox = 856)
	15, Jose
	20, Mariana
		
(((Endereco 856)))
NO FOLHA: (m = 2, pt pai = 48, pt prox = 1284)
	25, Ronaldo
	35, Marcela
		
(((Endereco 1284)))
NO FOLHA: (m = 2, pt pai = 96, pt prox = 1712)
	37, Leonardo
	38, Karla
		
(((Endereco 1712)))
NO FOLHA: (m = 2, pt pai = 96, pt prox = 2140)
	39, Mario
	50, Ricardo
		
(((Endereco 2140)))
NO FOLHA: (m = 2, pt pai = 96, pt prox = -1)
	55, Rosa
	60, Michele
		
```

## Casos de teste:

Os casos de teste estão na pasta [casos-teste](casos-teste). Cada caso tem 5 arquivos:

- entrada.txt: o que deve ser digitado no teclado (a chave a ser buscada)
- metadados.dat, indice.dat e clientes.dat: a árvore onde a busca é feita (arquivos binários)
- saida.txt: a saída esperada do programa

|Caso|Árvore|Chave|Descrição|Arquivos|
|---|---|---|---|---|
|[1](casos-teste/1)|[A](#árvore-a-a-raiz-é-uma-folha)|10|Chave existe e a raiz é uma folha: nenhum nó interno é lido|[entrada.txt](casos-teste/1/entrada.txt) [metadados.dat](casos-teste/1/metadados.dat) [indice.dat](casos-teste/1/indice.dat) [clientes.dat](casos-teste/1/clientes.dat) [saida.txt](casos-teste/1/saida.txt)|
|[2](casos-teste/2)|[A](#árvore-a-a-raiz-é-uma-folha)|12|Chave não existe numa árvore com um único nó|[entrada.txt](casos-teste/2/entrada.txt) [metadados.dat](casos-teste/2/metadados.dat) [indice.dat](casos-teste/2/indice.dat) [clientes.dat](casos-teste/2/clientes.dat) [saida.txt](casos-teste/2/saida.txt)|
|[3](casos-teste/3)|[B](#árvore-b-dois-níveis)|13|Chave na folha mais à esquerda|[entrada.txt](casos-teste/3/entrada.txt) [metadados.dat](casos-teste/3/metadados.dat) [indice.dat](casos-teste/3/indice.dat) [clientes.dat](casos-teste/3/clientes.dat) [saida.txt](casos-teste/3/saida.txt)|
|[4](casos-teste/4)|[B](#árvore-b-dois-níveis)|15|Chave igual a uma chave da raiz: a busca segue pelo ponteiro da direita dessa chave|[entrada.txt](casos-teste/4/entrada.txt) [metadados.dat](casos-teste/4/metadados.dat) [indice.dat](casos-teste/4/indice.dat) [clientes.dat](casos-teste/4/clientes.dat) [saida.txt](casos-teste/4/saida.txt)|
|[5](casos-teste/5)|[B](#árvore-b-dois-níveis)|23|Última chave de uma folha cheia|[entrada.txt](casos-teste/5/entrada.txt) [metadados.dat](casos-teste/5/metadados.dat) [indice.dat](casos-teste/5/indice.dat) [clientes.dat](casos-teste/5/clientes.dat) [saida.txt](casos-teste/5/saida.txt)|
|[6](casos-teste/6)|[B](#árvore-b-dois-níveis)|37|Chave na folha mais à direita|[entrada.txt](casos-teste/6/entrada.txt) [metadados.dat](casos-teste/6/metadados.dat) [indice.dat](casos-teste/6/indice.dat) [clientes.dat](casos-teste/6/clientes.dat) [saida.txt](casos-teste/6/saida.txt)|
|[7](casos-teste/7)|[B](#árvore-b-dois-níveis)|5|Chave menor que todas as chaves da árvore|[entrada.txt](casos-teste/7/entrada.txt) [metadados.dat](casos-teste/7/metadados.dat) [indice.dat](casos-teste/7/indice.dat) [clientes.dat](casos-teste/7/clientes.dat) [saida.txt](casos-teste/7/saida.txt)|
|[8](casos-teste/8)|[B](#árvore-b-dois-níveis)|99|Chave maior que todas as chaves da árvore|[entrada.txt](casos-teste/8/entrada.txt) [metadados.dat](casos-teste/8/metadados.dat) [indice.dat](casos-teste/8/indice.dat) [clientes.dat](casos-teste/8/clientes.dat) [saida.txt](casos-teste/8/saida.txt)|
|[9](casos-teste/9)|[B](#árvore-b-dois-níveis)|24|Chave não existe: deveria estar na folha do meio|[entrada.txt](casos-teste/9/entrada.txt) [metadados.dat](casos-teste/9/metadados.dat) [indice.dat](casos-teste/9/indice.dat) [clientes.dat](casos-teste/9/clientes.dat) [saida.txt](casos-teste/9/saida.txt)|
|[10](casos-teste/10)|[C](#árvore-c-dois-níveis-com-a-raiz-cheia)|40|Chave igual a uma chave da raiz, que está cheia|[entrada.txt](casos-teste/10/entrada.txt) [metadados.dat](casos-teste/10/metadados.dat) [indice.dat](casos-teste/10/indice.dat) [clientes.dat](casos-teste/10/clientes.dat) [saida.txt](casos-teste/10/saida.txt)|
|[11](casos-teste/11)|[C](#árvore-c-dois-níveis-com-a-raiz-cheia)|30|Chave não existe: deveria estar numa folha do meio|[entrada.txt](casos-teste/11/entrada.txt) [metadados.dat](casos-teste/11/metadados.dat) [indice.dat](casos-teste/11/indice.dat) [clientes.dat](casos-teste/11/clientes.dat) [saida.txt](casos-teste/11/saida.txt)|
|[12](casos-teste/12)|[C](#árvore-c-dois-níveis-com-a-raiz-cheia)|77|Chave na folha apontada pelo último ponteiro de um nó interno cheio|[entrada.txt](casos-teste/12/entrada.txt) [metadados.dat](casos-teste/12/metadados.dat) [indice.dat](casos-teste/12/indice.dat) [clientes.dat](casos-teste/12/clientes.dat) [saida.txt](casos-teste/12/saida.txt)|
|[13](casos-teste/13)|[C](#árvore-c-dois-níveis-com-a-raiz-cheia)|50|Chave não existe: está entre duas chaves da raiz|[entrada.txt](casos-teste/13/entrada.txt) [metadados.dat](casos-teste/13/metadados.dat) [indice.dat](casos-teste/13/indice.dat) [clientes.dat](casos-teste/13/clientes.dat) [saida.txt](casos-teste/13/saida.txt)|
|[14](casos-teste/14)|[D](#árvore-d-três-níveis)|20|Chave numa folha do nível 3 (exemplo do enunciado)|[entrada.txt](casos-teste/14/entrada.txt) [metadados.dat](casos-teste/14/metadados.dat) [indice.dat](casos-teste/14/indice.dat) [clientes.dat](casos-teste/14/clientes.dat) [saida.txt](casos-teste/14/saida.txt)|
|[15](casos-teste/15)|[D](#árvore-d-três-níveis)|18|Chave não existe: a busca chega à mesma folha do caso anterior|[entrada.txt](casos-teste/15/entrada.txt) [metadados.dat](casos-teste/15/metadados.dat) [indice.dat](casos-teste/15/indice.dat) [clientes.dat](casos-teste/15/clientes.dat) [saida.txt](casos-teste/15/saida.txt)|
|[16](casos-teste/16)|[D](#árvore-d-três-níveis)|37|Chave igual à chave da raiz de uma árvore com 3 níveis|[entrada.txt](casos-teste/16/entrada.txt) [metadados.dat](casos-teste/16/metadados.dat) [indice.dat](casos-teste/16/indice.dat) [clientes.dat](casos-teste/16/clientes.dat) [saida.txt](casos-teste/16/saida.txt)|
|[17](casos-teste/17)|[D](#árvore-d-três-níveis)|55|Chave igual a uma chave de um nó interno do nível 2|[entrada.txt](casos-teste/17/entrada.txt) [metadados.dat](casos-teste/17/metadados.dat) [indice.dat](casos-teste/17/indice.dat) [clientes.dat](casos-teste/17/clientes.dat) [saida.txt](casos-teste/17/saida.txt)|
|[18](casos-teste/18)|[D](#árvore-d-três-níveis)|10|Menor chave da árvore|[entrada.txt](casos-teste/18/entrada.txt) [metadados.dat](casos-teste/18/metadados.dat) [indice.dat](casos-teste/18/indice.dat) [clientes.dat](casos-teste/18/clientes.dat) [saida.txt](casos-teste/18/saida.txt)|
|[19](casos-teste/19)|[D](#árvore-d-três-níveis)|60|Maior chave da árvore|[entrada.txt](casos-teste/19/entrada.txt) [metadados.dat](casos-teste/19/metadados.dat) [indice.dat](casos-teste/19/indice.dat) [clientes.dat](casos-teste/19/clientes.dat) [saida.txt](casos-teste/19/saida.txt)|
|[20](casos-teste/20)|[D](#árvore-d-três-níveis)|36|Chave não existe: deveria estar na última folha da subárvore esquerda|[entrada.txt](casos-teste/20/entrada.txt) [metadados.dat](casos-teste/20/metadados.dat) [indice.dat](casos-teste/20/indice.dat) [clientes.dat](casos-teste/20/clientes.dat) [saida.txt](casos-teste/20/saida.txt)|

### Como compilar e rodar os testes

O projeto tem um Makefile. Abra a pasta do projeto no VSCode e use o terminal integrado (menu Terminal > New Terminal). Os comandos abaixo devem ser executados na pasta do projeto:

|Comando|O que faz|
|---|---|
|`make`|Compila o programa, gerando o executável arvore\_b\_mais|
|`make test`|Roda todos os casos de teste e mostra quais passaram e quais falharam|
|`make caso N=4`|Roda apenas o caso 4 e mostra as diferenças entre a sua saída e a saída esperada|
|`make clean`|Apaga o executável e a pasta execucao|

No `make caso`, as linhas marcadas com < são da sua saída e as linhas marcadas com > são da saída esperada. A saída do seu programa fica gravada em execucao/saida\_obtida.txt.

Para usar o make é preciso ter o gcc e o make instalados. No Linux e no macOS eles normalmente já estão disponíveis (no macOS, instale as ferramentas de linha de comando com `xcode-select --install`, se necessário). No Windows, use o WSL ou o MSYS2.

Os comandos `make test` e `make caso` copiam os arquivos .dat do caso para a pasta execucao antes de rodar o programa. Se for rodar o programa manualmente (por exemplo, `./arvore_b_mais` e digitar a chave), copie antes os arquivos .dat do caso para o diretório de execução, senão o programa não vai encontrar a árvore.

#### Arquivos a modificar

Modifique apenas o arquivo **arvore\_b\_mais.c**, com sua função de busca implementada. 

## Dicas Importantes: 

- A entrada e a saída já são tratadas no arquivo fornecido para ler e imprimir os dados no formato esperado pela questão. Vocês devem APENAS implementar a função solicitada no problema
- Os arquivos metadados.c, no\_interno.c, no\_folha.c e cliente.c (e seus respectivos .h) já contêm as funções para ler metadados, nós e clientes. Não é preciso alterá-los. As funções de arvore\_b\_mais.c estão declaradas em arvore\_b\_mais.h
- Comece a busca pela posição indicada por pt raiz no arquivo de metadados. Se o flag raiz folha for 1, a raiz está no arquivo de dados; caso contrário, ela está no arquivo de índice
- Em um nó interno, se a chave buscada for igual a uma chave do nó, a busca continua pelo ponteiro da direita dessa chave (numa árvore B+, os registros estão sempre nas folhas)
- Imprima cada nó assim que ele for lido, e leia cada nó uma única vez: se o mesmo nó for impresso duas vezes, a saída vai ficar diferente da esperada
- Na saída, a função imprime\_no\_folha imprime um caractere de tabulação para cada posição do nó folha, mesmo as vazias, e uma linha em branco ao final. Por isso, use sempre as funções de impressão fornecidas, em vez de imprimir os nós por conta própria
