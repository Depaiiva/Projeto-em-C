/******************************************************************************************************************************************
Aluno: Carlos Henrique de Paiva Munis
Matrícula: 221022480

Declaro que eu sou o autor deste trabalho e que o codigo não foi copiado
de outra pessoa nem repassado para alguém. Estou ciente de que poderei sofrer
penalizações na avaliação em caso de detecção de plágio.


****************************************************************************************************************************************/
//declaração das bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>

// declaração dos defines com os limites
#define CONSULTAR_MINIUSINA 1
#define CONSULTAR_CONSUMIDOR 2
#define LISTAR_MINIUSINAS_CADASTRADAS 3
#define LISTAR_MINIUSINAS_OPERACAO 4
#define LISTAR_MINIUSINAS_ORDEM_DECRESCENTE 5
#define LISTAR_MINIUSINAS_ORDEM_NUMERO_CONTRATOS 6
#define LISTAR_MINIUSINAS_ORDEM_CAPACIDADE_GERACAO 7
#define LISTAR_MINIUSINAS_PERCENTUAL_ENERGIA_DISPONIVEL 8
#define SAIR 9
#define TAM_MAX_CNPJ 18
#define TAM_LINHA 1000
#define MAX_RA 33
#define MAX_SIZE 100
#define MAX_LENGTH 100
#define MAX_CARACTERES 100
#define MAX_CONSUMIDORES 100


//definição da struct (registro) para representar uma usina no sistema
struct usina {
    char cnpj[20];
    char nome_usina[100];
    double capacidade;
    int ra;
    char status[10];
};

//definição da struct (registro) para representar um consumidor no sistema
struct consumidor {
    char id_consumidor[100];
    char nome_consumidor[100];
    int ra_consumidor;
};

//definição da struct (registro) para representar uma região administrativa no sistema
struct regiao_administrativa {
    int id_ra;
    char nome_ra[100];
    int quantidade_miniusinas;
    double soma_capacidade_total;


};

//definição da struct (registro) para representar um contrato no sistema
struct contratos {
    int id_contratos;
    char id_consumidor[100];
    char cnpj_miniusina[100];
    char data_inicio[100];
    char data_termino[100];
    double energia_contratada;
};

// função para limpar a tela do compilador do programa
void limpar_buffer(){
    char ch;
    while((ch = getchar()) != '\n' && ch != EOF);
}

// função que faz com que após cada operação feita pelo programa ele da uma pausa mostrando uma frase
//juntamente com a função limpar_buffer ajuda o usuario a entender melhor o programa
void pause(){
    printf("Pressione qualquer tecla para continuar no programa...");
    getc(stdin);
}

// função para limpar a tela do compilador
void limpar_tela(){
    #if defined(linux) || defined(unix) || defined(APPLE)
    system("clear");
    #endif

    #if defined(_WIN32) || defined(_win64)
    system("cls");
    #endif
}



// selection sort
void ordem_decrescente(struct usina ordem[], int tamanho){
    int i, j, posicao_maior;
    struct usina temp;

    for(i = 0; i < tamanho - 1; i++){
        posicao_maior = i;

        for (j = i + 1; j < tamanho; j++){
        if( ordem[j].capacidade > ordem[posicao_maior].capacidade){
            posicao_maior = j;
        }
    }
    if(posicao_maior != i){
    temp = ordem[i];
    ordem[i] = ordem[posicao_maior];
    ordem[posicao_maior] = temp;
    }

}
}


// procedimento para o usuario fazer a consulta das miniusinas 1
void consultar_miniusinas() {
    //declaração de variaveis
    FILE *arquivo_usina;
    struct usina usina_consultada;
    char cnpj_consulta[200];
    int encontrou_usina = 0;
    char linha[200];



    // 1) pedir ao usuario que digite pelo cnpj a ser consultado
    printf("Digite o CNPJ no formato (XX.XXX.XXX/XXXX-XX): ");
    scanf(" %[^\n]", cnpj_consulta);
    cnpj_consulta[strcspn(cnpj_consulta, "\n")] = '\0'; // remover quebra de linha

    // 2) validar o cnpj
int cnpj_valido = 1; // variavel para indicar se o CNPJ é válido

// Removendo ponto, barra e hífen do CNPJ
char cnpj_clean[15];
int j = 0;
for (int i = 0; i < strlen(cnpj_consulta); i++) {
    if (cnpj_consulta[i] >= '0' && cnpj_consulta[i] <= '9') {
        cnpj_clean[j] = cnpj_consulta[i];
        j++;
    }
}
cnpj_clean[j] = '\0';

// Verificando o tamanho e formato do CNPJ
if (strlen(cnpj_clean) != 14) {
    printf("CNPJ incorreto.\n");
    cnpj_valido = 0;
} else {
    for (int i = 0; i < 14; i++) {
        if (cnpj_clean[i] < '0' || cnpj_clean[i] > '9') {
            printf("CNPJ incorreto.\n");
            cnpj_valido = 0;
            break;
        }
    }
}

if (!cnpj_valido) {
// CNPJ está incorreto, então encerre a função
return;
}


    // 3) abrir o arquivo
    arquivo_usina = fopen("miniusinas.txt", "r");

    // 4) verificar se conseguiu abrir o arquivo
    if (arquivo_usina == NULL){
        printf("Nâo foi possivel abrir o arquivo\n");
        }

        // fazer a busca do cnpj consultado por todo o arquivo
        while (fgets(linha, 200, arquivo_usina) !=NULL ){
            //ler uma linha do arquivo, colocando os dados na struct
            sscanf(linha, "%[^;];%[^;];%lf;%d;%s",     usina_consultada.cnpj,
                                                       usina_consultada.nome_usina,
                                                       &usina_consultada.capacidade,
                                                       &usina_consultada.ra,
                                                       usina_consultada.status);
            //verificar se o cnpj a ser consulta é igual ao cnpj da usina que foi lida do arquivo
            if (strcmp(usina_consultada.cnpj, cnpj_consulta) == 0 ) {
                encontrou_usina = 1;
                break;
            }
        }
            if (encontrou_usina){
                printf("-----------------------------\n");
                printf("CNPJ: %s\n", usina_consultada.cnpj);
                printf("Nome da Usina: %s\n", usina_consultada.nome_usina);
                printf("Capacidade: %lf\n", usina_consultada.capacidade);
                printf("Região Administrativa: %d\n", usina_consultada.ra);
                printf("Status: %s\n", usina_consultada.status);
                printf("-----------------------------\n\n");
            }
            // caso não tenha encontrado a usina, vai mostrar na tela que não foi encontrado
           else{
                printf("Não foi encontrado nenhuma usina com o CNPJ %s\n\n\n", cnpj_consulta);
            }

// fechar o arquivo
fclose(arquivo_usina);
}




// procedimento para o usuario consultar os consumidores cadastrados 2
void consultar_consumidor(){
    struct consumidor consumidores[MAX_CONSUMIDORES];
    int numConsumidores = 0;

    // Ler os dados do arquivo e preencher o array de consumidores
    FILE *arquivo = fopen("consumidores.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[MAX_CARACTERES];
    fgets(linha, sizeof(linha), arquivo); // Descarta a primeira linha

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "%[^;];%[^;];%d", consumidores[numConsumidores].id_consumidor, consumidores[numConsumidores].nome_consumidor, &consumidores[numConsumidores].ra_consumidor);
        numConsumidores++;
    }

    fclose(arquivo);

    // Pedir ao usuário para escolher a pesquisa por CPF ou CNPJ
    int opcao;
    printf("Escolha uma opção:\n");
    printf("1. Pesquisar por CPF\n");
    printf("2. Pesquisar por CNPJ\n");
    scanf("%d", &opcao);

    char id[MAX_CARACTERES];
    printf("Digite o ID do consumidor: ");
    scanf(" %[^\n]", id);

    int encontrado = 0;
    for (int i = 0; i < numConsumidores; i++) {
        if (opcao == 1 && strcmp(consumidores[i].id_consumidor, id) == 0) {
            printf("ID do consumidor: %s\n", consumidores[i].id_consumidor);
            printf("Nome: %s\n", consumidores[i].nome_consumidor);
            printf("ID do RA: %d\n", consumidores[i].ra_consumidor);
            encontrado = 1;
            break;
        } else if (opcao == 2 && strcmp(consumidores[i].id_consumidor, id) == 0) {
            printf("ID do consumidor: %s\n", consumidores[i].id_consumidor);
            printf("Nome: %s\n", consumidores[i].nome_consumidor);
            printf("ID do RA: %d\n", consumidores[i].ra_consumidor);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Consumidor não encontrado.\n");
    }
}

// procedimento para lista todas miniusinas cadastradas 3
void listar_miniusinas(){

    //declaração de variaveis
    FILE *arquivo_usinas_lista;
    struct usina list_usinas;
    char o[TAM_LINHA];
    char p[1000];

    // 1) abrir arquivo
        arquivo_usinas_lista = fopen("miniusinas.txt", "r");

    // 2) verificar se conseguiu abrir o arquivo
    if (arquivo_usinas_lista == NULL){
        printf("Arquivo não encontrado");
        getchar();
        exit(0);
}
        // ler a primeira linha do arquivo
        fscanf(arquivo_usinas_lista, "%[^\n]", o);

    // ler as linhas do arquivo e imprimir depois
        while (fgets(p, 1000, arquivo_usinas_lista)!=NULL){
                // mostrar na tela o que foi lido
                printf("%s\n ", p);
        }
        // fechar o arquivo
        fclose(arquivo_usinas_lista);
    }

// procedimento para listar as miniusinas em operação por ordem decresecente 4
void miniusinas_operacao_decrescente() {
    FILE *arquivo_capacidade_decrescente;
    arquivo_capacidade_decrescente = fopen("miniusinas.txt", "r");

    if (arquivo_capacidade_decrescente == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[200];
    struct usina miniusinas[100];
    int i = 0;
    char o[TAM_LINHA];

    // ler a primeira linha do arquivo
    fscanf(arquivo_capacidade_decrescente, "%[^\n]", o);


    while (fgets(linha, sizeof(linha), arquivo_capacidade_decrescente)) {
        sscanf(linha, "%[^;];%[^;];%lf;%d;%s",
               miniusinas[i].cnpj,
               miniusinas[i].nome_usina,
               &miniusinas[i].capacidade,
               &miniusinas[i].ra,
               miniusinas[i].status);

        i++;
    }

    int n = i;
    fclose(arquivo_capacidade_decrescente);

    ordem_decrescente(miniusinas, n);

    printf("----------------------------------------------------------\n");
    for (i = 0; i < n - 1; i++) {
        printf("%s - %s: %.2f\n", miniusinas[i].cnpj, miniusinas[i].nome_usina, miniusinas[i].capacidade);
        printf("----------------------------------------------------------\n");
    }
}

// procedimento para listar as RAs por ordem decrescente da quantidade de miniusina 5
void listar_RAs_ordem_decrescente_quantidade_miniusina(){
   FILE *arquivo_ra = fopen("ra.txt", "r");
    FILE *arquivo_miniusina = fopen("miniusinas.txt", "r");

    if (arquivo_ra == NULL || arquivo_miniusina == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    struct regiao_administrativa ra[MAX_SIZE];
    struct usina miniusina;
    int cont_ra[MAX_SIZE] = {0};
    int i, j, num_ra = 0;

    // Lendo e armazenando as RAs do arquivo ra.txt
    char linha[MAX_SIZE];
    fgets(linha, sizeof(linha), arquivo_ra); // Ignorando o cabeçalho
    while (fgets(linha, sizeof(linha), arquivo_ra) != NULL) {
        sscanf(linha, "%d;%[^\n]", &ra[num_ra].id_ra, ra[num_ra].nome_ra);
        num_ra++;
    }

    // Contando a quantidade de miniusinas por RA
    fgets(linha, sizeof(linha), arquivo_miniusina); // Ignorando o cabeçalho
    while (fgets(linha, sizeof(linha), arquivo_miniusina) != NULL) {
        sscanf(linha, "%[^;];%*[^;];%*[^;];%d;", miniusina.cnpj, &miniusina.ra);
        cont_ra[miniusina.ra - 1]++;
    }

    fclose(arquivo_miniusina);

    // Associando a quantidade de miniusinas a cada RA
    for (i = 0; i < num_ra; i++) {
        ra[i].quantidade_miniusinas = cont_ra[ra[i].id_ra - 1];
    }

    // Ordenando as RAs por quantidade de miniusinas em ordem decrescente
    for (i = 0; i < num_ra - 1; i++) {
        for (j = i + 1; j < num_ra; j++) {
            if (ra[i].quantidade_miniusinas < ra[j].quantidade_miniusinas) {
                struct regiao_administrativa temp = ra[i];
                ra[i] = ra[j];
                ra[j] = temp;
            }
        }
    }

    // Imprimindo as RAs e a quantidade de miniusinas
    for (i = 0; i < num_ra; i++) {
        printf("RA: %s\n", ra[i].nome_ra);
        printf("Quantidade de Miniusinas: %d\n\n", ra[i].quantidade_miniusinas);
    }

    fclose(arquivo_ra);

}

// procedimento para Listar as RAs por ordem crescente de número de contratos 6
void listar_RAs_ordem_crescente_numero_contratos(){
    struct usina miniusinas[10];
    struct regiao_administrativa ras[33];
    struct contratos contratos[10];

    FILE* file;
    char buffer[256];
    int i = 0;

    // Lendo miniusinas.txt
    file = fopen("miniusinas.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo miniusinas.txt\n");
        return;
    }

    fgets(buffer, sizeof(buffer), file); // Ignora o cabeçalho
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%[^;];%[^;];%lf;%d;%s",
            miniusinas[i].cnpj,
            miniusinas[i].nome_usina,
            &miniusinas[i].capacidade,
            &miniusinas[i].ra,
            miniusinas[i].status);
        i++;
    }

    fclose(file);

    // Lendo ra.txt
    file = fopen("ra.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    i = 0;
    fgets(buffer, sizeof(buffer), file); // Ignora o cabeçalho
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%d;%[^\n]",
            &ras[i].id_ra,
            ras[i].nome_ra);
        i++;
    }

    fclose(file);

    // Lendo contratos.txt
    file = fopen("contratos.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    i = 0;
    fgets(buffer, sizeof(buffer), file); // Ignora o cabeçalho
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%d;%[^;];%[^;];%[^;];%[^;];%lf",
            &contratos[i].id_contratos,
            contratos[i].id_consumidor,
            contratos[i].cnpj_miniusina,
            contratos[i].data_inicio,
            contratos[i].data_termino,
            &contratos[i].energia_contratada);
        i++;
    }

    fclose(file);

    int j, count;
    int quantidade_por_ra[33] = {0};

    // Contando a quantidade de miniusinas por RA
    for (i = 0; i < 10; i++) {
        quantidade_por_ra[miniusinas[i].ra]++;
    }

    // Ordenando as RAs por ordem crescente de número de contratos
    for (i = 0; i < 32; i++) {
        for (j = 0; j < 32 - i; j++) {
            if (quantidade_por_ra[j] > quantidade_por_ra[j + 1]) {
                int temp = quantidade_por_ra[j];
                quantidade_por_ra[j] = quantidade_por_ra[j + 1];
                quantidade_por_ra[j + 1] = temp;

                struct regiao_administrativa temp_ra = ras[j];
                ras[j] = ras[j + 1];
                ras[j + 1] = temp_ra;
            }
        }
    }

    // Exibindo as RAs na tela com a quantidade de miniusinas em cada uma
    printf("RAs por ordem crescente de número de contratos:\n");
    for (i = 0; i < 33; i++) {
        count = quantidade_por_ra[i];
        printf("RA: %d - %s: %d\n", ras[i].id_ra, ras[i].nome_ra, count);
        printf("----------------------------------------------------------\n");

    }
}


void listar_RAs_ordem_decrescente_capacidade_geracao(){ // 7

    FILE *arquivo_miniusina = fopen("miniusinas.txt", "r");
    FILE *arquivo_ra = fopen("ra.txt", "r");

    if (arquivo_miniusina == NULL || arquivo_ra == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    // Contar o número de miniusinas
    int num_miniusinas = 0;
    char line[MAX_LENGTH];
    fgets(line, sizeof(line), arquivo_miniusina); // Ignorar a primeira linha (cabeçalho)
    while (fgets(line, sizeof(line), arquivo_miniusina) != NULL) {
        num_miniusinas++;
    }
    rewind(arquivo_miniusina);

    // Ler as miniusinas
    struct usina miniusinas[num_miniusinas];
    fgets(line, sizeof(line), arquivo_miniusina); // Ignorar a primeira linha (cabeçalho)
    for (int i = 0; i < num_miniusinas; i++) {
        fgets(line, sizeof(line), arquivo_miniusina);
        sscanf(line, "%*[^;];%*[^;];%lf;%d;%*[^\n]\n", &miniusinas[i].capacidade, &miniusinas[i].ra);
    }
    fclose(arquivo_miniusina);

    // Contar o número de regiões administrativas
    int num_regioes = 0;
    fgets(line, sizeof(line), arquivo_ra); // Ignorar a primeira linha (cabeçalho)
    while (fgets(line, sizeof(line), arquivo_ra) != NULL) {
        num_regioes++;
    }
    rewind(arquivo_ra);

    // Ler as regiões administrativas
    struct regiao_administrativa regioes[num_regioes];
    fgets(line, sizeof(line), arquivo_ra); // Ignorar a primeira linha (cabeçalho)
    for (int i = 0; i < num_regioes; i++) {
        fgets(line, sizeof(line), arquivo_ra);
        sscanf(line, "%d;%[^;\n]%*[^\n]\n", &regioes[i].id_ra, regioes[i].nome_ra);
        regioes[i].quantidade_miniusinas = 0;
        regioes[i].soma_capacidade_total = 0.0;
    }
    fclose(arquivo_ra);

    // Associar as miniusinas às regiões administrativas
    for (int i = 0; i < num_miniusinas; i++) {
        int id_ra = miniusinas[i].ra;
        for (int j = 0; j < num_regioes; j++) {
            if (regioes[j].id_ra == id_ra) {
                regioes[j].quantidade_miniusinas++;
                regioes[j].soma_capacidade_total += miniusinas[i].capacidade;
                break;
            }
        }
    }

    // Ordenar as regiões administrativas por ordem decrescente de capacidade de geração
    for (int i = 0; i < num_regioes - 1; i++) {
        for (int j = 0; j < num_regioes - i - 1; j++) {
            if (regioes[j].soma_capacidade_total < regioes[j + 1].soma_capacidade_total) {
                struct regiao_administrativa temp = regioes[j];
                regioes[j] = regioes[j + 1];
                regioes[j + 1] = temp;
            }
        }
    }

    // Exibir as regiões administrativas por ordem decrescente de capacidade de geração
    for (int i = 0; i < num_regioes; i++) {
        printf("Região: %s\n", regioes[i].nome_ra);
        printf("Quantidade de miniusinas: %d\n", regioes[i].quantidade_miniusinas);
        printf("Soma da capacidade total: %.2lf\n", regioes[i].soma_capacidade_total);
        printf("----------------------------------------------------------\n\n");
    }
}

// procedimento do acesso ao menu de opções
void menu(){
    //menu de opções
    printf("----------------------------------------- MENU DE OPÇÕES ------------------------------------------\n");
    printf("1) Consultar miniusina cadastrada:\n");
    printf("2) Consultar consumidor cadastrado:\n");
    printf("3) Listar as miniusinas cadastradas:\n");
    printf("4) Listar as miniusinas em operação por ordem decrescente de capacidade de geração de energia:\n");
    printf("5) Listar as RAs por ordem decrescente da quantidade de miniusina:\n");
    printf("6) Listar as RAs por ordem crescente de número de contratos:\n");
    printf("7) Listar as RAs por ordem decrescente de capacidade de geração:\n");
    //printf("8) Listar as RAs por ordem decrescente de percentual de energia disponível:\n");
    printf("9) Sair do programa\n");
    printf("---------------------------------------------------------------------------------------------------\n");
}


//função principal do programa
int main()
{
    setlocale(LC_ALL,"portuguese");
    //declaração de variáveis
    int opcao;//armazena a opção escolhida pelo usuário

    do{

        menu(); //mostrar o menu na tela
        scanf("%d", &opcao);

        switch (opcao){
            case CONSULTAR_MINIUSINA: // 1
            // o objetivo desta opção é receber o cnpj de uma usina
            // buscar os dados dela no arquivo miniusinas.txt
            // o codigo que faz isso está dentro de um procedimento
            consultar_miniusinas();
            limpar_buffer();
            pause();
            limpar_tela();
            break;

            case CONSULTAR_CONSUMIDOR: // 2
            //
            consultar_consumidor();
            limpar_buffer();
            pause();
            limpar_tela();
            break;

            case LISTAR_MINIUSINAS_CADASTRADAS: // 3
            listar_miniusinas();
            limpar_buffer();
            pause();
            limpar_tela();
            break;

            case LISTAR_MINIUSINAS_OPERACAO: // 4
            miniusinas_operacao_decrescente();
            limpar_buffer();
            pause();
            limpar_tela();
            break;

            case LISTAR_MINIUSINAS_ORDEM_DECRESCENTE: // 5
            listar_RAs_ordem_decrescente_quantidade_miniusina();
            limpar_buffer();
            pause();
            limpar_tela();
            break;

            case LISTAR_MINIUSINAS_ORDEM_NUMERO_CONTRATOS: // 6
            listar_RAs_ordem_crescente_numero_contratos();
            limpar_buffer();
            pause();
            limpar_tela();
            break;

            case LISTAR_MINIUSINAS_ORDEM_CAPACIDADE_GERACAO: // 7
            listar_RAs_ordem_decrescente_capacidade_geracao();
            limpar_buffer();
            pause();
            limpar_tela();
            break;

            case SAIR: // 9
            printf("Encerrando o sistema...\n\n");
            break;

            default:
            printf("opção invalida.\n\n");
            limpar_buffer();
            pause();
            limpar_tela();
        }

    } while(opcao != SAIR);

    return 1;
}


