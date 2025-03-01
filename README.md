Gerenciador de Miniusinas e Consumidores de Energia
Este projeto é um sistema desenvolvido em C para gerenciar informações sobre miniusinas de energia e seus consumidores. Com uma interface baseada em menu, o programa permite consultas e listagens dos dados, utilizando arquivos de texto para armazenamento das informações.

Sumário
- Tecnologias Utilizadas
- Funcionalidades
- Estrutura do Projeto
- Como Compilar e Executar
- Detalhes do Código (main.c)
- Autor
- Licença
  
Tecnologias Utilizadas
Linguagem: C
Bibliotecas Padrão:
stdio.h
stdlib.h
stdbool.h
ctype.h
string.h
locale.h

O sistema oferece as seguintes funcionalidades:
- Consulta de Miniusinas e Consumidores.
- Permite buscar informações detalhadas sobre uma miniusina ou um consumidor específico.
- Listagem de Miniusinas:
- Listar todas as miniusinas cadastradas.
- Exibir apenas as miniusinas em operação.
- Ordenar e listar as miniusinas em ordem decrescente de acordo com critérios como:
- Número de contratos;
- Capacidade de geração;
- Percentual de energia disponível.
- Menu Interativo:
- Um menu intuitivo possibilita a navegação pelas opções disponíveis, facilitando o acesso às funcionalidades do sistema.

Estrutura do Projeto
O projeto está organizado nos seguintes arquivos:

main.c
Arquivo principal que contém toda a lógica do programa, incluindo a definição das estruturas, funções de manipulação dos dados e implementação do menu.

Arquivos de Dados:

consumidores.txt: Armazena os registros dos consumidores.
contratos.txt: Contém os dados dos contratos de energia.
miniusinas.txt: Guarda os registros das miniusinas.
ra.txt: Possivelmente utilizado para armazenar informações adicionais ou identificadores.

Como Compilar e Executar
Pré-requisitos
Um compilador C (como o GCC)
Ambiente compatível com C
Passos para Compilar
Abra o terminal na pasta raiz do projeto.
Compile o código com o comando:
gcc main.c -o gerenciador
Execute o programa:
./gerenciador
Detalhes do Código (main.c)
O arquivo main.c é o núcleo do sistema e possui os seguintes pontos-chave:

Definição de Estruturas:

struct usina: Representa uma miniusina, contendo campos para armazenar o CNPJ, nome da usina, capacidade de geração, um identificador (RA) e status da operação.
struct consumidor: Armazena dados do consumidor, como ID e nome.
Constantes e Configurações:
Foram utilizadas diversas diretivas #define para definir limites e opções do menu, por exemplo:

Opções de consulta e listagem (ex.: CONSULTAR_MINIUSINA, LISTAR_MINIUSINAS_CADASTRADAS, etc.);
Tamanhos máximos para strings e arrays (ex.: TAM_MAX_CNPJ, TAM_LINHA, etc.).
Implementação do Menu:
Um menu interativo permite ao usuário selecionar a operação desejada. Cada opção chama funções específicas para:

Realizar consultas de miniusinas ou consumidores.
Listar e ordenar as miniusinas conforme os critérios estabelecidos.
Manipulação de Arquivos:
O programa lê os dados dos arquivos de texto (miniusinas.txt, consumidores.txt, etc.), possibilitando que os registros sejam atualizados sem a necessidade de um banco de dados tradicional.

Lógica de Ordenação e Filtragem:
Foram implementadas funções que ordenam os registros das miniusinas com base em diferentes critérios (por exemplo, capacidade de geração, número de contratos e percentual de energia disponível), proporcionando flexibilidade na exibição dos dados.

Este design modular facilita a manutenção do código e a inclusão de novas funcionalidades no futuro.

Autor
Carlos Henrique de Paiva Munis

Licença
Este projeto foi desenvolvido para fins acadêmicos (Universidade de Brasília). Sinta-se à vontade para usá-lo e aprimorá-lo, desde que seja para fins educacionais e com a devida atribuição ao autor.
