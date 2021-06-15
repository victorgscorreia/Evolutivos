# Evolutivos
O projeto consiste em um jogo de arco-e-flecha no qual um algoritmo evolutivo precisa aprender os parâmetros para acertar o alvo.
## Funcionamento do jogo
O jogo consiste em uma alvo no qual possui uma vida, ao acertar uma flecha no alvo ele perde uma parte desta vida. Quando o alvo chega em zero, é gerado um novo alvo com a vida cheia. O dano ao alvo depende do local onde foi acertado, sendo o dano maior que zero e podendo chegar até um se acertar no centro do alvo. A vida pode ser alterada no arquivo main.cpp:
```
double HP_ALVO = 20000;
```
As flechas que são lançadas possuem 2 parâmetros, a velocidade inicial (força) e o ângulo. Também existe um obstáculo no cenário que caso uma flecha se colida, faz 0 pontos e causa 0 de dano.
## Algoritmo evolutivo
O algoritmo consiste em gerar uma população nova a cada interação com o intuito de melhorá-la e com isso encontrar uma boa solução para o problema.
### Primeira geração
A primeira geração é gerada de forma aleatória, o seu tamanho pode variar e isso é definido no main.cpp:
```
#define TAM_GERACAO 50
```
### Gerações
#### Classificação
Para gerar uma nova geração, primeiramente cada indivíduo recebe uma nota de acordo com sua pontuação feita, sendo ela entre 0 e 1. Vale ressaltar que caso erre o alvo a nota é 0 independente se ficou perto ou não do alvo, caso contrário ele recebe uma pontuação de acordo da proximidade com o centro.
#### Gerando novos indivíduos
Tendo esta nota, classificamos os indivíduos do melhor para o pior. Tendo isso, a metade pior da geração é eliminada. Por exemplo, caso tenhamos 100 indivíduos, os 50 piores deixam de existir. Após isso, os que sobraram são cruzados com o melhor gerando novos indivíduos. Estes novos indivíduos substituem os seus pais, ficando somente o melhor. Por exemplo: caso tenhamos 100 indivíduos, 50 foram eliminados na etapa anterior, ficando agora com apenas 50. Ao cruzar com o melhor de todos, temos 49 novos indivíduos que substituem seus pais mas deixam o melhor de todos, ficando assim com 50 indivíduos.   
Após os processos anteriores, falta metade da população para ser gerada. Ela é criada a partir de mutações em todos os indivíduos gerados no processo de cruzamento, ficando assim com os mesmos número de indivíduos originais.
##### Cruzamento
O cruzamento é feito com uma média ponderada entre os 2 indivíduos nos 2 genes (velocidade inicial e ângulo). Os pesos da média são: 1 para o melhor de todos e 4 para outro indivíduo. Essa forma foi escolhida para manter a diversidade. Isso ajuda a encontrar outro caminho caso seja necessário.
#### Mutação
A mutação possui uma taxa variável e funciona da seguinte forma: Um indivíduo pode não sofrer mutação em nenhum gene, sofrer apenas na velocidade, ou somente no ângulo. Isso é decidido de forma aleatória. Após decidir se deve ou não sobre a mutação, ele sofre uma mutação com valor aleatório com base na mutação. OBS: esse valor não leva em conta os atributos do indivíduo.
##### Taxa de mutação
A taxa de mutação é um valor que pode variar de 0 até 1 dependendo da circunstância da população. Caso ela esteja convergindo para um ponto, é utilizado o quão bem o melhor de todos está indo, sendo T(x) a taxa de mutação, ela pode ser dada por: T(x) = 1 - x^5. Vale lembrar que x é a pontuação, e ela só pode ir de 0 a 1.   
Entretanto pode ocorrer uma situação em que a população não consiga melhorar e atingir o máximo global que é 1, precisando assim procurar outro caminho. Para isso ocorrer, caso o melhor de todos não consiga melhorar durante 5 gerações seguidas além de não estar no centro do alvo, a mutação é mudada para 1 para procurar um outro caminho até o alvo pelos outros indivíduos.
##### Cálculo do valor a ser mudado no indivíduo
Tendo o indivíduo que deve sofrer mutação e a taxa, o cálculo é feito pegando um número aleatório entre 0.5 e -0.5 e multiplicando pela taxa de mutação. Então esse valor é somado ao gene do indivíduo.
##### Localização no código fonte
Para localizar o local onde é realizado a mudança de taxa, olhar função change_mutation_tax no arquivo main.cpp
```
void change_mutation_tax( std::vector<double> &bests){
 
    double best_at = bests.back();
 
    //compara o melhor de todos com o melhor de todos de 5 geracoes atras
    
    //se nao teve ainda 5 geracoes, pega a geracao mais antiga(de indice 0 no vetor)
    double best_anterior = bests[0];
    if( int(bests.size()) > 5 ){
        best_anterior = bests[  int(bests.size()) -6 ];
    }
    double melhora = best_at - best_anterior;
 
    //se o melhor ja alcancou o maximo, faz a formula padrao
    if(best_at >= 1 - 0.01){
        //mutacao = 1 - x^5
        mutation_tax = 1.0 - pow(best_at,5);
    }else{
        //se nao melhorou nas ultimas 5 geracoes, aumenta ao maximo a mutacao
        if(melhora <= 0.001){
            mutation_tax = 1.0;
        //se melhorou, utiliza a formula padrao
        }else{
            //mutacao = 1 - x^5
            mutation_tax = 1.0 - pow(best_at,5);
        }
    }
    mutation_tax *= 3;
}

```
Para localizar o local onde é realizado a mutação, olhar função mutacao
no arquivo main.cpp
```
individuo mutacao( individuo ind ){
 
    int moeda = rand()%3;
 
    individuo mutado;
    //se nao muta
    if(moeda == 0){
        mutado.theta = ind.theta;
        mutado.velocity = ind.velocity;
    //se muta a velocidade
    }else if(moeda == 1){
        mutado.theta = ind.theta;
        double mutation_velocity = get_mutation();
        mutado.velocity = ind.velocity + mutation_velocity;
 
        mutado.velocity = std::min(mutado.velocity, 3.0);
        mutado.velocity = std::max(mutado.velocity, 0.1);
    //se muta o angulo
    }else{
        mutado.velocity = ind.velocity;
 
        double mutation_theta = get_mutation();
 
        mutado.theta = ind.theta + mutation_theta;
 
        mutado.theta = std::min(mutado.theta, (M_PI/2));
        mutado.theta = std::max(mutado.theta, 0.0);
    }
 
    return mutado; 
}

```
Para localizar o local onde é realizado o cruzamento, olhar função cruzamento
no arquivo main.cpp
```
individuo cruzamento(individuo mom, individuo dad){
    individuo child;
    //faz a media pondera, com a mae tendo peso 1 e o pai peso 4
    child.velocity = (mom.velocity + 4*dad.velocity)/5;
    child.theta = (mom.theta + 4*dad.theta)/5;
 
    return child;
}
```
## Membros
- Luan Icaro Pinto Arcanjo.
- Rodrigo Cesar Arboleda.
- Victor Graciano de Souza Correia.
