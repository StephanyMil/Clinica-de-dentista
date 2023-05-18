#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 100
#define H 10
#define enter_para_retornar() {printf("\nPressione ENTER para retornar."); getchar(); }
//Aline Ayumi e Stephnay Milhomem

typedef struct {
        int cod;
        char nome_paciente[40];
        char cpf[12];
        char tel_paciente[15];  //64 98442-4454
        char endereco_paciente[40];
        char email[40];
        char tratamento[100];
        } PACIENTE;

typedef struct {
        char nome_clinica[40];
        char cnpj[20];
        char nome_dentista[40];
        char cro_dentista[12];
        char tel_clinica[15];
        } CLINICA;

typedef struct {
        int hora; //hh:mm
        int dia;
        int mes;
        int cod_paciente;
        char status;
        } CONSULTAS;

typedef struct {
        CONSULTAS atend[H];
        int inicio, fim, n_consul;
        } AGENDA;

typedef struct {
        PACIENTE pacientes[N];
        AGENDA ag[31][12];
        CLINICA cl;
        int inic, fim, qtd;
        } LISTA;

    //INICIALIZACOES
    void inicializar_lista(LISTA *l) {
        l->qtd = 0;
        l->fim = 0;
        l->inic = 0;
    }

    void inicializar_agenda(LISTA *l) {
        int i, j, k;
        for(i=0; i<30; i++) {
            for(j=0; j<12; j++) {
                for(k=0; k<H; k++) {
                    l->ag[i][j].atend[k].status = 'L';
                }
            }
        }
    }

    void inicializar_clinica(LISTA *l) {
        printf("Entre com o nome da clínica\n");
        fgets(l->cl.nome_clinica, 40, stdin);
        getchar();
        printf("Entre com o CNPJ da clínica\n");
        fgets(l->cl.cnpj, 20, stdin);
        getchar();
        printf("Entre com o nome do dentista\n");
        fgets(l->cl.nome_dentista, 20, stdin);
        getchar();
        printf("Entre com o CRO do dentista\n");
        fgets(l->cl.cro_dentista, 12, stdin);
        getchar();
        printf("Entre com o telefone da clínica\n");
        fgets(l->cl.tel_clinica, 15, stdin);
        getchar();
    }

    //VERIFICACOES
    int Verifica_lista_vazia(LISTA l) {
        return(l.inic==l.fim);
    }

    int Verifica_lista_cheia(LISTA l) {
        return(l.fim==N);
    }

    //FUNCOES DO ARQUIVO
    void Carregar_Agenda(LISTA *L){
        FILE *fp;
        fp = fopen ("clinica.dat", "rb");
        if (fp == NULL) {
            inicializar_clinica(&(*L));
            inicializar_agenda(&(*L));
            inicializar_lista(&(*L));
    		return;
        }
        else {
            fread(&(*L),sizeof(LISTA),1,fp);
            fclose(fp);
        }
    }

    void Gerar_arquivo(LISTA L) {   // sem a struct...
        FILE *fp;
        fp = fopen ("clinica.dat", "wb"); //arquivo para escrita binária
        if (fp == NULL) {
           printf ("Erro ao abrir o arquivo.\n");
           return;
        }
        else {
            printf ("Arquivo Binario criado com sucesso.\n");
            fwrite(&L, sizeof(LISTA), 1, fp);
        }
          fclose (fp);
    }

    //FUNCOES DO PACIENTE

    //LER PACIENTE
    void ler_paciente(PACIENTE *p) {
        printf("Entre com o código do paciente\n");
        scanf("%d", &p->cod);
        getchar();
        printf("Entre com o nome do paciente\n");
        fgets(p->nome_paciente, 40, stdin);
        getchar();
        printf("Entre com o telefone do paciente\n");
        fgets(p->tel_paciente, 15, stdin);
        getchar();
        printf("Entre com o CPF do paciente\n");
        fgets(p->cpf, 12, stdin);
        getchar();
        printf("Entre com o email do paciente\n");
        fgets(p->email, 40, stdin);
        getchar();
        printf("Entre com o endereço do paciente\n");
        fgets(p->endereco_paciente, 40, stdin);
        getchar();
        printf("***MENU DE TRATAMENTOS***\n");
        printf("1 - Implante Dentário\n");
        printf("2 - Restauração\n");
        printf("3 - Limpeza\n");
        printf("Entre com o tratamento a ser feito\n");
        fgets(p->tratamento, 100, stdin);
        getchar();
    }

    //EXIBIR PACIENTE
    void Exibir_paciente(LISTA p, int i){
        printf("******************************\n");
        printf("Exibindo o paciente com o CPF: %s\n", p.pacientes[i].cpf);
        printf("O paciente possui o código: %d\n", p.pacientes[i].cod);
        printf("Nome do paciente: %s\n", p.pacientes[i].nome_paciente);
        printf("Telefone do paciente: %s\n", p.pacientes[i].tel_paciente);
        printf("Email do paciente: %s\n", p.pacientes[i].email);
        printf("Endereço do paciente: %s\n", p.pacientes[i].endereco_paciente);
        printf("Tratamento que irá realizar: %s\n", p.pacientes[i].tratamento);
        printf("******************************\n");

    }
    //CADASTRAR PACIENTE
    void Cadastrar_paciente(LISTA *l, PACIENTE *p) {

    if(Verifica_lista_cheia(*l)) {
        printf("A lista está cheia\n");
    }
    else {
        l->pacientes[l->fim] = *p;
        l->fim++;
        l->qtd++;
        printf("Cadastro realizado com sucesso\n");
       }
    }
    //BUSCAR PACIENTE
    int busca_paciente(LISTA l){
        int i, j;
        i=l.inic;
      //  PACIENTE p;

        printf("Digite o CÓDIGO do paciente que deseja buscar: \n");
        scanf("%d", &j);
        while((i<l.fim) && (j> l.pacientes[i].cod)) {
            i++;
        }
        if((i==l.fim) || (j!=l.pacientes[i].cod)) {
          printf("Cadastrar Paciente por não estar na lista de pacientes\n");
          return -1;
        }
        else {
            return i;
        }
    }

    //ALTERA PACIENTE
    PACIENTE altera_cadastro(LISTA *l, int j) {
        int opc;
        PACIENTE p;
           p = l->pacientes[j];
            do { printf("Paciente que deseja alterar\n");
                printf("Entre com a opção que deseja alterar\n");
                printf("1 - Nome\n");
                printf("2 - Telefone do paciente\n");
                printf("3 - Email do Paciente\n");
                printf("4 - Endereço\n");
                printf("5 - Sair\n");
                printf("Entre com a opção>\n");
                scanf("%d", &opc);
                getchar();
                switch(opc) {
                    case 1:
                        printf("Entre com o novo Nome\n");
                        fgets(p.nome_paciente, 40, stdin);
                        getchar();
                        printf("Nome alterado\n");
                        break;

                    case 2:
                        printf("Entre com o novo Telefone do paciente\n");
                        fgets(p.tel_paciente, 15, stdin);
                        getchar();
                        break;

                    case 3:
                        printf("Entre com o novo Email do paciente\n");
                        fgets(p.email, 40, stdin);
                        getchar();
                        break;

                    case 4:
                        printf("Entre com o novo Endereço\n");
                        fgets(p.endereco_paciente, 40, stdin);
                        getchar();
                        break;

                    case 5:
                        printf("Dados Alterados com sucesso\n");
                        break;
                    default:
                        printf("Entre com uma opção válida\n");
                        break;

                }
            } while(opc!=5);

            return(p);
    }

    //LISTA DE PACIENTE

    void Exibir_lista_pacientes(LISTA l){
        int i;
        FILE * fp;
        fp = fopen ("clinica.dat", "rb");
        if (fp == NULL) {
            printf ("Erro,  arquivo nao existe.\n");
            return;
        }
        if(Verifica_lista_vazia(l)){
            printf("A LISTA ESTA VAZIA - EXIBIR LISTA\n");
        }
        else {
            printf("***** Exibir a lista de pacientes *****\n");
            for(i=l.inic; i<l.fim; i++){
                Exibir_paciente(l, i);
            }
            printf("***** Fim da lista *****\n");
        }
        fclose(fp);
    }

    //FUNCOES DA CONSULTA

   //IMPRIME HORARIOS
   void imprime_horarios() {
       printf("Código dos horários\n");
       printf("nº 1 - 08:00 h\n");
       printf("nº 2 - 09:00 h\n");
       printf("nº 3 - 10:00 h\n");
       printf("nº 4 - 11:00 h\n");
       printf("nº 5 - 13:00 h\n");
       printf("nº 6 - 14:00 h\n");
       printf("nº 7 - 15:00 h\n");
       printf("nº 8 - 16:00 h\n");
       printf("nº 9 - 17:00 h\n");
   }

    //CONVERTE  HORARIOS
    void converte_horarios(int k) {
        switch (k) {
            case 1:
                printf("Horario %d - 08:00 h\n", k);
                break;
            case 2:
                printf("Horario %d - 09:00 h\n", k);
                break;
            case 3:
                printf("Horario %d - 10:00 h\n", k);
                break;
            case 4:
                printf("Horario %d - 11:00 h\n", k);
                break;
            case 5:
                printf("Horario %d - 13:00 h\n", k);
                    break;
            case 6:
                printf("Horario %d - 14:00 h\n", k);
                break;
            case 7:
                printf("Horario %d - 15:00 h\n", k);
                break;
            case 8:
                printf("Horario %d - 16:00 h\n", k);
                break;
            case 9:
                printf("Horario %d - 17:00 h\n", k);
                break;

            default:
                break;
            }
    }

    /*
    //VERIFICA HORARIOS
    int verifica_horario_livre(LISTA *l, int d, int m) {
        int flag = 0, k;
        printf("Pesquisa de horarios disponiveis nesse dia:\n");
        for(k=0; k<H; k++) {
            if(l->ag[d][m].atend[k].status == 'L') {
                converte_horarios(k);
                flag = 1;
            }
        }
        return flag;
    }
    */

    //MARCAR CONSULTA
    void Marcar_consulta(AGENDA *a, LISTA *l, int j){
        int m, d, h;

        printf("Entre com o dia que deseja marcar a consulta: \n");
        scanf("%d", &d);
        printf("Entre com o mes que deseja marcar a consulta: \n");
        scanf("%d", &m);
        imprime_horarios();
        printf("Entre com o codigo do horario que deseja marcar a consulta: \n");
        scanf("%d", &h);
        if(l->ag[d][m].atend[h].status == 'O') {
            printf("Esse horario nao esta disponivel\n");
            enter_para_retornar();
        }
        else {
            l->ag[d][m].atend[h].dia = d;
            l->ag[d][m].atend[h].mes = m;
            l->ag[d][m].atend[h].hora  = h;

            l->ag[d][m].atend[h].status = 'O';
            l->ag[d][m].atend[h].cod_paciente = l->pacientes[j].cod;
            //printf("%c\n",l->ag[d][m].atend[h].status);
            printf("Consulta marcada com sucesso\n");
        }
    }

    //EXIBIR CONSULTA
    void exibir_consulta (LISTA l, int dia, int mes, int i, int m) {
        printf("------CONSULTA------\n\n");
        printf("Dados do paciente\n");
        printf("Nome completo: %s\n", l.pacientes[m].nome_paciente);
        printf("CPF: %s\n", l.pacientes[m].cpf);
        if(dia>9) {
            printf("Data da consulta: %d/", dia);
        }
        else if (dia<=9) {
            printf("Data da consulta: 0%d/", dia);
        }
        if(mes>9) {
            printf("%d\n", mes);
        }
        else if (mes<=9) {
            printf("0%d\n", mes);
        }
        converte_horarios(l.ag[dia][mes].atend[i].hora);
        printf("Tratamento a ser feito: %s\n", l.pacientes[m].tratamento);
        printf("-----------------");
    }

    //BUSCAR CONSULTA
    void buscar_consulta(LISTA *l) {
        int i, k, flag = 0, m, mes;

        m = busca_paciente(*l);
        printf("Entre com o mês da consulta: \n");
        scanf("%d", &mes);
        for(i=0; i<32; i++) {
            for(k=0; k<H; k++) {
                if((l->ag[i][mes].atend[k].cod_paciente == l->pacientes[m].cod)&&(l->ag[i][mes].atend[k].status == 'O')) {
                    flag = 1;
                    exibir_consulta(*l, i, mes, k, m);
                }
            }
        }
        if(flag == 0) {
            printf("Não há consulta marcada para o paciente no mes pesquisado\n");
        }
    }

    //DESMARCAR consulta
    void desmarcar_consulta (LISTA *l, int j) {
        int dia, mes, hora, flag = 0;
        printf("Entre com o dia da consulta: \n");
        scanf("%d", &dia);
        printf("Entre com o mes da consulta: \n");
        scanf("%d", &mes);
        printf("Entre com o horario da consulta: \n");
        scanf("%d", &hora);
        if((l->ag[dia][mes].atend[hora].cod_paciente == l->pacientes[j].cod)&&(l->ag[dia][mes].atend[hora].status = 'O')) {
            l->ag[dia][mes].atend[hora].status = 'L';
            flag = 1;
            printf("Consulta desmarcada com sucesso\n");
            //printf("%c\n",l->ag[dia][mes].atend[i].status);
        }
        if(flag==0) {
            printf("Não há consultas marcadas para este paciente\n");
        }
    }

    //EXIBIR CLINICA
    void Exibir_clinica(LISTA *l){
        printf("******************************\n");
        printf("Nome da clínica: %s\n", l->cl.nome_clinica);
        printf("CNPJ da clínica: %s\n", l->cl.cnpj);
        printf("Telefone da clínica: %s\n", l->cl.tel_clinica);
        printf("Nome do dentista: %s\n", l->cl.nome_dentista);
        printf("CRO do dentista: %s\n", l->cl.cro_dentista);
        printf("******************************\n");
    }

    void menu() {
        printf("***MENU DA CLÍNICA***\n");
        printf("1 - Cadastrar Paciente\n");
        printf("2 - Marcar consulta\n");
        printf("3 - Desmarcar consulta\n");
        printf("4 - Buscar consulta\n");
        printf("5 - Alterar cadastro\n");
        printf("6 - Buscar paciente\n");
        printf("7 - Exibir Lista de Pacientes\n");
        printf("8 - Exibir dados da clínica\n");
        printf("9 - Sair\n");
        printf("Entre com a Opção>\n");
    }

    int main(){
        LISTA l;
        PACIENTE p;
  //      CLINICA c;
        AGENDA a;
        int op, i, j;
        Carregar_Agenda(&l);
        do{
            menu();
            scanf("%d",&op);
            switch(op){
                //cadastro
                case 1:
                    ler_paciente(&p);
                    Cadastrar_paciente(&l, &p);
                    enter_para_retornar();
                  break;

                 //marcar consulta
                case 2:
                    j = busca_paciente(l);
                    if(j>=0) {
                        Marcar_consulta(&a, &l, j);
                    }else {ler_paciente(&p);
                           Cadastrar_paciente(&l, &p);
                           Marcar_consulta(&a, &l, a.fim-1);
					   }
                    enter_para_retornar();
                  break;
                //desmarcar
                case 3:
                    j = busca_paciente(l);
                    if(j>=0) {
                        desmarcar_consulta(&l, j);
                    }
                    enter_para_retornar();
                  break;

                //buscar consulta
                case 4:
                    buscar_consulta(&l);
                    enter_para_retornar();
                  break;

                //alterar cadastro do paciente
                case 5:
                    j = busca_paciente(l);
                    if(j>=0) {
                        p = altera_cadastro(&l, j);
                        l.pacientes[j] = p;
                    }

                    enter_para_retornar();
                  break;

                //buscar dados do paciente
                case 6:
                    i = busca_paciente(l);
                    if(i>=0) {
                        Exibir_paciente(l, i);
                    }
                    enter_para_retornar();
                  break;

                //exibir lista dos pacientes
                case 7:
                    Exibir_lista_pacientes(l);
                    enter_para_retornar();
                  break;

                //exibir clinica
                case 8:
                    Exibir_clinica(&l);
                    enter_para_retornar();
                  break;

                //sair
                case 9:
                    Gerar_arquivo(l);
                    printf("OBRIGADO POR UTILIZAR NOSSO SISTEMA\n");
                  break;
                default:
                    printf("ENTRE COM O OPÇÃO CORRETA\n");
		          break;
            }
        } while(op!=9);

        return 0;
    }

