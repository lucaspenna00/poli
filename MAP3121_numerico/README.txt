Exercicio Programa 1 - Métodos Numéricos e Aplicações

Esse exercício foi desenvolvido no ambiente CMake (versão mínima 2.8), no sistema operacional Linux Ubuntu 16.04.
Dessa forma, sugerimos rodar fortemente esse exercício programa num sistema operacional Linux, com o ambiente CMake.
O CMake está configurado para compilar utilizando o compilador gcc 5.4.

Instruções:

1. Descomprimir a pasta no diretório home;
Antes de compilar o projeto, será necessário alterar os trechos do código que contém funções cujos argumentos são os diretórios dos arquivos  utilizados no nosso computador.
Dessa forma, será necessário modificar os argumentos de forma a tornar os diretórios compatíveis com seu computador, a fim de compilar corretamente.

2. Abra o terminal e rode os seguintes comandos para compilar o projeto:

$ cd ~/Numerical_Methods/build
$ cmake .
$ make

3. Para rodar o arquivo executável gerado, sugerimos que rode os seguintes comandos no mesmo diretório anterior (~/Numerical_Methods/build):

$ ulimit -s unlimited
$ ./ep1 -j4

4. O programa apresenta uma interface que permite o usuário escolher qual tarefa quer executar. Atente-se às instruções na tela.

Se houver algum problema na execução e precisar entrar em contato para eventuais dúvidas, deixo o meu contato:
lucas.saraiva@usp.br
