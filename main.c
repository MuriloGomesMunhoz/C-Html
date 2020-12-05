#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<stdlib.h>
#include <unistd.h>
#define MAX_REG 100
#define MAX_CAT 10

//structs para desenvolvimento do código.
//struct para o menu.
struct menu{
  char novaCategoria[100];
  char verificação[100];
};
//struct para criar novos registro.
struct registro{
  int  ano, dia, mes;
  char descricao[100];
  float valores;
  int tipoGasto;
  char cat[200][40];

};
//struct para trabalhar com ponteiro .
struct ponteiro{
  struct registro Ctg[MAX_REG];
  char categorias[MAX_CAT][40];
  int totalRegistro;
  int totalCategorias;
};
void apresentacao(){
  puts("Bem vindo ao gerenciador finaceiro, esse gerenciador foi feito na forma mais dinâmica, sempre pensando em uma fácil navegação.");
  puts("Nele há um diferencial de poder remover e buscar registros através de descrição, data e até valor, nele também vem uma funcionalidade premium na qual é possível adicionar categorias novas, fora as fixas e por fim um relatório com um design atrativo e simples, pois eu acho que o mais simples, mas com todas as informações pedidas, é mais fácil a vizualização e mais dinâmico.");
  puts("Esse trabalho foi feito pelo Murilo Gomes Munhoz, foi feito com bastante dedicação e bastante estudo, com uso conhecimentos adquiridos em todo o semestre e pesquisas por fora.");
  puts("Como tudo acredito que há erros nesse gerenciador, mas tudo foi muito bem pensado e foi feito da melhor forma possível, espero que goste e ficarei no aguarde de um retorno.");

}
int Menu()
{
  int op = 0;


  puts("=======================================================");
  puts("0 - Encerrar tarefas.\n");
  puts("1 - Gasto novo.\n");
  puts("2 - Exibir registros de gastos.\n");
  puts("3 - Remover gasto.\n");
  puts("4 - Buscar gasto.\n");
  puts("5 - Gerar relatório de gastos.\n");
  puts("6 - Adicionar categoria nova.\n");
  puts("7 - Ver categoria adicionadas.\n");
  puts("8 - Criador do gerenciador finaceiro.\n");
  puts("=======================================================\n");
  printf("Digite a opção desejada: ");
  scanf("%d", &op);
  return op;
  
}
//encerrar tarefas.
void encerrar(){
  printf("\n TAREFAS ENCERRADAS!!! \n\n");

}
//inicializar o valor x com 3 pois as categorias já viram com 4 categorias fixas.
void inicializar(struct ponteiro* pont){
  pont->totalCategorias = 3;
  // categorias fixas.
  strcpy(pont->categorias[0], "casa");
  strcpy(pont->categorias[1], "mercado");
  strcpy(pont->categorias[2], "pessoal");
  strcpy(pont->categorias[3], "contas");
}

//função que se relaciona com categoria.
void TodasCategorias(struct ponteiro* pont, int k){
  int i;

  //mostrar todas as categorias.
  if(k == -1){
  puts("~~~~Categorias~~~~");
  for(i =0;i<10;i++){
    printf("%d - %s\n", i, pont->categorias[i]);
    if(i == pont->totalCategorias){
      return;
    }
  }
  //adicionar categoria.
  }else if(k == -2){
    printf ("Digite a categoria que deseja adicionar: \n");
    fgets(pont->categorias[pont->totalCategorias+1],40, stdin);
    pont->totalCategorias++;
  }
  //imprime as categoria que aparecerá no registro.
  else{
    printf("%s\n",pont->categorias[k]);
  }

}
//adicionar gasto novo.
// COLOCAR A OPÇÃO DELE VER AS CATEGORIAS ANTES DE COLOCA-LAS 
void gastoNovo(struct ponteiro* pont){
  struct registro cG;
  struct menu gN[100];
  char verificar[] = "SIM";
  pont->totalRegistro = 0;
  int retorno;
  int n = 0, i = 0, j = 0, k = 0;

  do
  {
    puts("\n=======================================================\n");


    do{
      puts("Qual a posição da categoria do seu gasto?(-1 para listar todas)");
      printf("DIGITE AQUI -> ");
      scanf("%d", &cG.tipoGasto);
      TodasCategorias(pont, cG.tipoGasto);
    }while(cG.tipoGasto == -1);

    puts("\nQual o valor gasto?");
      printf("DIGITE AQUI -> R$");
      scanf("%f%*c", &(cG.valores));

    puts("\nQual a dia/mês/ano?");
      printf("DIGITE AQUI -> ");
      scanf("%d/%d/%d%*c", &cG.dia, &cG.mes, &cG.ano);

    puts("\nQual a descrição do gasto?");
      printf("DIGITE AQUI -> ");
        fgets(cG.descricao,100,stdin);

    puts("\nDeseja adicionar novo gasto?");
      printf("DIGITE AQUI -> sim ou não: ");
      scanf("%s", gN[n].verificação);
      puts("\n=======================================================\n");

    //vetor para salvar os gastos.
    pont->Ctg[pont->totalRegistro++]=cG;

    //colocar todas as letras em maiúsculas.
    for(i = 0; i<3;i++){
      gN[0].verificação[i] =  toupper( gN[0].verificação[i]);
    }

    //comaparar a resposta do cliente.
    retorno = strcmp(gN[0].verificação, verificar);

    }while(retorno == 0);
      printf("NOVO GASTO ADICIONADO COM SUCESSO!!!\n");

}

//adicionar nova cateogria.
void categoriaNova(struct ponteiro* pont){
  int x = 0;
  do{
  puts("------------------ADICIONAR CATEGORIA------------");
  puts("(-1) - listar todas as categorias");
  puts("(-2) - adicionar nova categoria");
  printf("DIGITE AQUI -> ");
  scanf("%d%*c", &x);
  printf("------------------------------------\n");
  TodasCategorias(pont,x);
  }while(x == -1);
}

//mostrar os registros.
void registro(struct ponteiro* pont){
  printf("================ TODOS OS GASTOS ==============\n\n");
  int i;
  for(i = 0; i < pont->totalRegistro; i++){
  printf("================ Gasto: %d ==============\n\n", i);
  printf("Data: %d/%d/%d\n", pont->Ctg[i].dia, pont->Ctg[i].mes, pont->Ctg[i].ano);
  printf("valor: R$ %.2lf\n", pont->Ctg[i].valores);
  printf("Descrição: %s", pont->Ctg[i].descricao);
  printf("Categoria: ");
  TodasCategorias(pont,pont->Ctg[i].tipoGasto);
  }
}

//Remove registros.
void removerRegistro(struct ponteiro *pont){
  int i,op = 0, posi = 0, dia1=0,mes1=0,ano1=0, categorias = 0;
  float valor= 0;
  char descricao[100];
  struct registro cG;

  puts("~~~~~~~~~~~~~~~~~~~~~REMOVER REGISTRO ~~~~~~~~~~~~~~~~~~~~~~~\n");
  puts("Digite a opção por qual caracteristica deseja remover o gasto: \n");
  puts("0 - Voltar ao menu.\n");
  puts("1 - Remover pela posição de gasto adicionado.\n");
  puts("2 - Remover pelo valor.\n");
  puts("3 - Remover pela descrição.\n");
  puts("4 - Remover pela data.\n");
  puts("5 - Remover pela categorias.\n");

  puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

  printf("Digite a opção desejada: ");

  scanf("%d", &op);
  if(op==0){
    Menu();
  }
  pont->totalRegistro--;
  if(op == 1){
    puts("Digite a posição do gasto: \n");
    scanf("%d", &posi);
    for(i = posi; i < pont->totalRegistro; i++){
      pont->Ctg[i] = pont->Ctg[i+1];
    }
  }
  else if(op == 2){
    puts("Digite o valor do gasto: \n");
    scanf("%f", &valor);
    for(i = 0; i < pont->totalRegistro; i++){
      if(pont->Ctg[i].valores == valor){
        pont->Ctg[i] = pont->Ctg[i+1];
      }
    }
  }
  else if(op == 3){
    puts("Digite a descrição do gasto: \n");
    scanf("%c", descricao);
    fgets(descricao, 100, stdin);
    for(i = 0; i<pont->totalRegistro; i++){
      if(strstr(pont->Ctg[i].descricao,descricao) != NULL){
          pont->Ctg[i] = pont->Ctg[i+1];
      }
    }
  }
  else if(op ==4){
    puts("Digite a data do gasto: dia/mes/ano\n");
    scanf("%d/%d/%d", &dia1, &mes1, &ano1);
    for(i = 0; i < pont->totalRegistro; i++){
      if(pont->Ctg[i].dia == dia1 && pont->Ctg[i].mes == mes1 && pont->Ctg[i].ano == ano1){
        pont->Ctg[i] = pont->Ctg[i+1];
      }
    }
  }  
  else if(op == 5){
    do{
    puts("Digite a posição da gasto: (digite -1 para listar todas categorias)\n");
    scanf("%d", &categorias);
    TodasCategorias(pont, cG.tipoGasto);
    }while(categorias == -1);
    for(i = 0; i<pont->totalCategorias;i++){
      if(i == categorias){
        pont->Ctg[i] = pont->Ctg[i+1];

      }
    }

  }
}

//imprime registro.
void registroImpirme(struct ponteiro* pont, int i){
  printf("================ Gasto: %d ==============\n\n", i);
  printf("Data: %d/%d/%d\n", pont->Ctg[i].dia, pont->Ctg[i].mes, pont->Ctg[i].ano);
  printf("valor: R$ %.2lf\n", pont->Ctg[i].valores);
  printf("Descrição: %s", pont->Ctg[i].descricao);
  printf("Categoria: ");
  TodasCategorias(pont,pont->Ctg[i].tipoGasto);
}

// busaca gastos.
void buscarGasto(struct ponteiro* pont){
  int cont,op = 0, posi = 0, dia1=0,mes1=0,ano1=0, categorias =0;
  float valor= 0;
  char descricao[100];
  struct registro cG;

  puts("---------------------- BUSCAR REGISTRO ----------------------------\n");
  puts("Digite a opção por qual caracteristica deseja buscar o gasto: \n");
  puts("0 - Voltar ao menu.\n");
  puts("1 - Buscar pela posição de gasto adicionado.\n");
  puts("2 - Buscar pelo valor.\n");
  puts("3 - Buscar pela descrição.\n");
  puts("4 - Buscar pela data.\n");
  puts("5 - Buscar pela categoria.\n");
  puts("--------------------------------------------------------\n");

  printf("Digite a opção desejada: ");

  scanf("%d", &op);
  if(op==0){
    Menu();
  }
  if(op == 1){
    puts("Digite a posição do gasto: \n");
    scanf("%d", &posi);
    for(cont = posi; cont < pont->totalRegistro; cont++){
      registroImpirme(pont, cont);
    }
  }
  else if(op == 2){
    puts("Digite o valor do gasto: \n");
    scanf("%f", &valor);
    for(cont = 0; cont < pont->totalRegistro; cont++){
      if(pont->Ctg[cont].valores == valor){
        registroImpirme( pont, cont);
      }
    }
  }
  else if(op == 3){
    puts("Digite a descrição do gasto: \n");
    scanf("%c", descricao);
    fgets(descricao, 100, stdin);
    for(cont = 0; cont<pont->totalRegistro; cont++){
      if(strstr(pont->Ctg[cont].descricao,descricao) != NULL){
        registroImpirme( pont, cont);
      }
    }
  }
  else if(op ==4){
    puts("Digite a data do gasto: dia/mes/ano\n");
    scanf("%d/%d/%d", &dia1, &mes1, &ano1);
    for(cont = 0; cont < pont->totalRegistro; cont++){
      if(pont->Ctg[cont].dia == dia1 && pont->Ctg[cont].mes == mes1 && pont->Ctg[cont].ano == ano1){
        registroImpirme( pont, cont);
      }
    }
  }
  else if(op == 5){
    do{
    puts("Digite a posição da gasto: (digite -1 para listar todas categorias)\n");
    scanf("%d", &categorias);
    TodasCategorias(pont, cG.tipoGasto);
    }while(categorias == -1);
    for(cont = 0; cont<pont->totalCategorias;cont++){
      if(cont == categorias){
        registroImpirme( pont, cont);

      }
    }

  }
}
// cria arquivo com os registros.
void gravaFunção(struct ponteiro* pont){
  FILE* f = fopen("guardar.bin", "wb");
  fwrite(&pont->totalCategorias, sizeof(int),1,f);
  fwrite(&pont->totalRegistro, sizeof(int),1,f);
  fwrite(&pont->categorias, 40,pont->totalCategorias,f);
  fwrite(&pont->Ctg, sizeof(struct registro),pont->totalRegistro,f);
  fclose(f);
}

void lerFunção(struct ponteiro* pont){
  FILE* f = fopen("guardar.bin", "rb");
  if(f!= NULL){
  fread(&pont->totalCategorias, sizeof(int),1,f);
  fread(&pont->totalRegistro, sizeof(int),1,f);
  fread(&pont->categorias, 40,pont->totalCategorias,f);
  fread(&pont->Ctg, sizeof(struct registro),pont->totalRegistro,f);
  fclose(f);
  }
}

void relatorioMes(struct ponteiro* pont, int mes, int ano){
  int i = -1;
  FILE* f = fopen("relatorio.html", "w");
  fprintf(f, "<!DOCTYPE html>"); 
  fprintf(f, "<html>"); 
  fprintf(f, "<head>"); 
  fprintf(f, "<meta charset=\"utf-8\">"); 
  fprintf(f, "<meta name=\"viewport\" content=\"width=device-width\">"); 
  fprintf(f, "<title>gerenciador financeiro</title>"); 
  fprintf(f, "<link href=\"aplication.css\" rel=\"stylesheet\" type=\"text/css\" />");
  fprintf(f, "</head>"); 
  fprintf(f, "<body background=\"fundoFinanceiro.jpg\">"); 
  fprintf(f, "<center>");
  fprintf(f, "<h1> Ultimo mês </h1>");
  fprintf(f, "<h3> Gasto do mês: %d </h3>", mes);
  fprintf(f, "<table border = \"1\" bordercolor= \"white\">");
  fprintf(f, "<th> Data do gasto </th> ");
  fprintf(f, "<th> Categoria </th>");
  fprintf(f, "<th> Valor gasto </th>");
  fprintf(f, "<th> Descrição </th>");



  for(i = 0; i < pont->totalRegistro; i++){
    if( pont->Ctg[i].mes == mes && pont->Ctg[i].ano == ano){
        fprintf(f, "<tr>");
        fprintf(f, "<th> %d/%d/%d </th>", pont->Ctg[i].dia, pont->Ctg[i].mes, pont->Ctg[i].ano);
        fprintf(f, "<th> %s </th>", pont->categorias[i]);
        fprintf(f, "<th> R$%.2f </th>", pont->Ctg[i].valores);
        fprintf(f, "<th> %s </th>",pont->Ctg[i].descricao);
        fprintf(f, "</tr>");
    }
  }
    fprintf(f, "</table>");


  fprintf(f, "</center>");

  fprintf(f, "</body>");
  fprintf(f, "</html>");
  fclose(f);
}
void relatorioAno(struct ponteiro* pont, int ano){
  int i = -1, j = 12, organizaTabrla[40][200];
  FILE* f = fopen("relatorioAno.html", "w");
  fprintf(f, "<!DOCTYPE html>"); 
  fprintf(f, "<html>"); 
  fprintf(f, "<head>"); 
  fprintf(f, "<meta charset=\"utf-8\">"); 
  fprintf(f, "<meta name=\"viewport\" content=\"width=device-width\">"); 
  fprintf(f, "<title>gerenciador financeiro</title>"); 
  fprintf(f, "<link href=\"aplication.css\" rel=\"stylesheet\" type=\"text/css\" />");
  fprintf(f, "</head>"); 
  fprintf(f, "<body background=\"fundoFinanceiro.jpg\">"); 
  fprintf(f, "<center>");
  fprintf(f, "<h1> Ultimo 12 meses </h1>");
  fprintf(f, "<table border = \"1\" bordercolor= \"white\">");
  fprintf(f, "<th> Data do gasto </th> ");
  fprintf(f, "<th> Categoria </th>");
  fprintf(f, "<th> Valor gasto </th>");
  fprintf(f, "<th> Descrição </th>");




  for(i = 0; i < pont->totalRegistro; i++){
    if(pont->Ctg[i].ano == ano){
      fprintf(f, "<tr>");
      fprintf(f, "<th> %d/%d/%d </th>", pont->Ctg[i].dia, pont->Ctg[i].mes, pont->Ctg[i].ano);
      fprintf(f, "<th> %s </th>", pont->categorias[i]);
      fprintf(f, "<th> R$%.2f </th>", pont->Ctg[i].valores);
      fprintf(f, "<th> %s </th>",pont->Ctg[i].descricao);
      fprintf(f, "</tr>");
      }
    }
    fprintf(f, "</table>");


  fprintf(f, "<center>");
  fprintf(f, "<canvas class=\"line-chart\"></canvas>");

  fprintf(f, "</body>");
  fprintf(f, "</html>");
  fclose(f);
}
void menuRelatorio(struct ponteiro* pont){
  int op = 0, mes = 0, ano = 0, mes1 = 0, ano1=0;
  puts("------------ RELATÓRIO DE GASTOS ------------");
  puts("1 - abrir relatório do ultimo mês.");
  puts("2 - abrir relatório do ultimo ano.");
  printf("Digite aqui a opção -> ");
  scanf("%d", &op);
  if(op == 1){
  printf("Digite aqui o mês -> ");
  scanf("%d", &mes);
  printf("Digite aqui o ano -> ");
  scanf("%d", &ano);
    relatorioMes(pont, mes, ano);
  }
  else if(op == 2){
    printf("Digite aqui o ano -> ");
    scanf("%d", &ano1);
      relatorioAno(pont, ano1);

  }
}


/*void estiloRelatorio(struct base* b){
  FILE* f = fopen("aplication.css", "w");
  fprintf(f, "body{");
  fprintf(f, "margin: auto");
  fprintf(f, "}");



}*/
int main(void) {
  struct ponteiro pont;
  int i;
  inicializar(&pont);
  int op;
  do{
  op = Menu();

  if(op == 0){
    encerrar();
    break;
  }

  else if(op == 1){
    gastoNovo(&pont);
  }

  else if(op == 2){
    registro(&pont);
  }

  else if(op == 3){
    removerRegistro(&pont);
  }

  else if(op == 4){
      buscarGasto(&pont);
  }

  else if(op==5){
    menuRelatorio(&pont);
  }
  else if(op==6){
    categoriaNova(&pont);

  }
  else if(op ==7){
      TodasCategorias(&pont, -1);
  }
  else if(op == 8){
    apresentacao();
  }
  }while(op <= 6 && op >= 0);
  gravaFunção(&pont);
  lerFunção(&pont);
  //estiloRelatorio(&b);
  return 0;
}