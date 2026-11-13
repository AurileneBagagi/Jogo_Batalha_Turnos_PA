# Jogo Batalha de Turnos

Projeto da disciplina de **Programação Avançada** (FACAPE – Ciência da Computação, 2026.2, Prof. Thierry Araujo).

## Objetivo do projeto e tema

O projeto sintetiza os conteúdos da disciplina (TAD, memória dinâmica, estruturas de dados, persistência em arquivos e tratamento de erros) em um jogo em linguagem C, executado no terminal.

Tema escolhido: **J3 — Batalha por turnos**. Dois personagens alternam ações até que a vida de um deles chegue a zero. O resultado de cada partida é registrado em arquivo e alimenta um ranking.

## Integrantes

- Aurilene Bagagi
- Eduardo Lustosa
- Carlos Miguel
- Gustavo Guedes

## Como compilar e executar

### Linux

O projeto usa GNU Make (`Makefile`).

**Pré-requisitos:** `make` e `gcc`.

Compilar e executar:

```
make run
```

Limpar arquivos compilados (opcional):

```
make clean
```

> **Importante:** execute sempre a partir da pasta raiz do projeto. O caminho do arquivo de dados é relativo (`data/jogador.csv`) e a pasta `data/` precisa existir.

## Como jogar

1. Ao iniciar, o programa exibe o **histórico** de jogadores (nome, vitórias e derrotas).
2. Digite o nome do **Jogador 1** e depois o do **Jogador 2**. Pode ser um nome já listado no histórico (as estatísticas dele serão atualizadas) ou um nome novo (ele passa a ser registrado ao final da partida). O Jogador 1 começa.
3. A cada turno, o jogador da vez escolhe uma ação digitando o número correspondente:

| Opção | Ação          | Efeito                                          |
| ----- | ------------- | ----------------------------------------------- |
| 1     | Atacar        | Dano aleatório de 10 a 17                       |
| 2     | Habilidade    | Dano aleatório de 20 a 25; custa 10 de estamina |
| 3     | Poção de cura | Recupera até 30 de vida                         |

4. A tela mostra as barras de vida e estamina dos dois jogadores a cada turno.
5. Quando a vida de um jogador chega a zero, o outro é declarado vencedor, o resultado é salvo e o **ranking** é exibido.

## Requisitos do sistema (tema J3)

- Criar/selecionar personagens (ver observação abaixo);
- Ações de combate por turno: atacar, usar habilidade e usar item (poção);
- Exibir o estado dos participantes;
- Finalizar a batalha e registrar o resultado;
- Persistir estatísticas/resultados;
- Inventário simples: cada jogador carrega poções de cura (2 por partida), controladas pelo próprio `Jogador`.

**Decisão de projeto — defesa substituída por habilidade.** O enunciado cita "atacar, defender ou usar item". A equipe optou por substituir a ação _defender_ por uma **habilidade especial** (dano maior, com custo de estamina). Isso mantém três ações por turno e dá sentido estratégico ao atributo de estamina, que gerencia o uso da habilidade.

**Criar/selecionar personagens.** O personagem é criado a cada partida a partir do nome digitado. "Selecionar" um personagem existente significa digitar um nome já presente no histórico, o que faz o jogo acumular as estatísticas daquele registro. Os atributos de combate (vida, estamina, poções) são sempre reiniciados no começo de cada partida.

## Estrutura do projeto

- `src/batalha.c`: contém a `main`; coordena o fluxo principal, a criação dos participantes, o laço de turnos, o registro do resultado e a exibição do ranking.
- `src/jogador.c`: implementa o TAD `Jogador` (nome, vida, estamina e poções) e suas operações, incluindo as barras de status.
- `src/interface.c`: telas, menu de ações, leitura de nomes e ações, histórico e ranking.
- `src/persistencia.c`: abre, lê e atualiza o arquivo de estatísticas (TAD `Arquivo`).
- `src/estatisticas.c`: implementa a lista dinâmica de estatísticas e sua ordenação para o ranking.
- `include/`: cabeçalhos (`.h`) com as interfaces dos módulos (`jogador.h`, `interface.h`, `persistencia.h`, `estatisticas.h`) e `cores.h` com as sequências ANSI de cor.
- `data/jogador.csv`: arquivo de texto onde as estatísticas são persistidas.
- `Makefile` / `Makefile.win`: automatizam a compilação e a execução.
- `scripts/teste_terminal.sh`: script que fornece entradas ao programa para testar uma partida no terminal.

## TAD(s) e estruturas de dados mais importantes

O projeto usa **tipos opacos**: o `.h` declara apenas `typedef struct X X;` e as funções públicas, enquanto os campos ficam no `.c`. Isso vale para:

- `Jogador` (`jogador.h`/`jogador.c`): acessado só por funções como `criar`, `receber_dano`, `alterar_estamina`, `usar_pocao`, `vida_rest`, `buscar_nome` e `destruir_jogador`. Alocado com `malloc` (com verificação de falha) e liberado com `free`.
- `ListaEstatisticas` (`estatisticas.h`/`.c`): **vetor dinâmico** de `EstatisticaJogador` (nome, vitórias, derrotas). Começa vazio, tem capacidade inicial de 4 e dobra quando enche. O `realloc` usa um **ponteiro temporário**, preservando o vetor original se falhar. A ordenação usa `qsort` com comparador próprio (mais vitórias primeiro; empate resolvido por ordem alfabética do nome). A lista e o vetor são liberados em `destruir_estatisticas`.
- `Arquivo` (`persistencia.h`/`.c`): encapsula o `FILE*` do arquivo de dados.

A estrutura central que cresce dinamicamente é o vetor de estatísticas: ele é carregado do arquivo, cresce conforme novos registros são lidos e é descartado ao fim do uso.

## Estratégia de persistência

As estatísticas ficam em texto no arquivo `data/jogador.csv`, um registro por linha, campos separados por ponto e vírgula:

```text
nome;vitorias;derrotas
```

Exemplo:

```text
Luna;3;1
Orion;1;3
```

Funcionamento:

- **Primeira execução:** se o arquivo não existe, o programa o cria vazio (a pasta `data/` precisa existir). Um arquivo vazio é tratado normalmente (histórico e ranking mostram que ainda não há jogadores).
- **Início:** o arquivo é lido para uma `ListaEstatisticas` e o histórico é exibido. Linhas mal formatadas são ignoradas.
- **Fim da partida:** para cada participante, `salvar_resultados` reescreve o arquivo em um arquivo temporário (`data/temp.csv`), incrementando vitórias ou derrotas do nome correspondente, e depois substitui o original. Se o nome ainda não existe, uma nova linha é acrescentada.
- **Tratamento de erros:** falhas de abertura, leitura e escrita são verificadas e geram mensagem de erro; o programa exibe a mensagem de erro e encerra.

## Principais regras do problema

- A batalha é entre **dois jogadores**. Cada um começa com **100 de vida**, **30 de estamina** e **2 poções de cura**.
- Os jogadores agem **alternadamente**; o primeiro nome informado começa.
- **Atacar:** dano aleatório entre 10 e 17.
- **Habilidade:** dano aleatório entre 20 e 25 e custo de 10 de estamina. Sem estamina suficiente, a ação não é executada e **o turno é perdido**.
- **Poção de cura:** recupera até 30 de vida, sem ultrapassar 100. Se a vida já estiver cheia, a poção **não é consumida** (mas o turno é gasto). Sem poções restantes, o turno é perdido.
- **Opção inválida ou entrada não numérica:** o jogador perde o turno e uma mensagem é exibida.
- A partida termina quando a vida de um personagem chega a zero. O outro é o vencedor e o resultado é registrado.
- O histórico é exibido antes da solicitação dos nomes. Informar um nome já listado atualiza o registro dele; nomes vazios ou com mais de 48 caracteres são rejeitados.

## Funcionalidade adicional

**Ranking de vitórias.** Ao fim de cada partida, o arquivo é relido, as estatísticas são ordenadas por número de vitórias (desempate alfabético pelo nome) e os **cinco primeiros** são exibidos (ou todos, se houver menos de cinco).

Justificativa: a funcionalidade acrescenta comportamento real ao sistema (leitura dos dados persistidos, ordenação com `qsort` e comparador próprio sobre o vetor dinâmico), não é apenas alteração visual e dá sentido ao registro acumulado de resultados entre execuções.

## Limitações conhecidas

- **Persistência de personagens:** só são persistidos nome, vitórias e derrotas. Atributos de combate e o estado de uma partida em andamento não são salvos; não é possível retomar uma partida interrompida.
- **Nomes:**
  - não há validação de nomes com `;` (o delimitador do arquivo). Nomes com esse caractere corrompem o registro, então **não devem ser usados**;
  - se os dois jogadores digitarem o mesmo nome, as estatísticas daquele registro ficam ambíguas (receberiam vitória e derrota na mesma partida). Evite nomes iguais;
  - a seleção é feita digitando o nome do histórico, sem menu numérico ou identificador.
- **Caminho relativo:** `data/jogador.csv` exige execução a partir da raiz do projeto e a pasta `data/` existente.
- **Portabilidade:** limpeza de tela e cores usam sequências ANSI, cujo suporte depende do terminal (em terminais sem esse suporte, a tela pode exibir caracteres estranhos). A compilação documentada é para Linux; o `Makefile.win` pode exigir ajustes em outros ambientes Windows.

## Uso de ferramentas de Inteligência Artificial

Ferramentas de IA generativa foram usadas **apenas como apoio**, e a equipe é responsável por compreender, revisar e testar todo o código entregue:

- **Gemini (versão para estudantes):** esclarecimento de dúvidas conceituais sobre C (strings, ponteiros, gerenciamento de memória, sintaxe e organização de projeto) e revisão textual da documentação.
- **Claude:** revisão do README em comparação com o código e com o enunciado do projeto, e ajuda na reescrita da documentação. Não foi usado para gerar o código-fonte.

O código-fonte foi escrito pelos integrantes da equipe.
