# Projeto do Circuito Datapath
Documentação

Para rodar:
- Crie uma pasta no desktop chamada datapath
- Extraia o conteudo de vhd e compilar no diretorio datapath criado
- Substitua com um editor de texto o nome lucas por bia (ou seu user) nos arquivos de compilação
- rode o comando

$ do compilar_TUDO.tcl

no modelsim terminal


## 1. Overview dapath
<img src=datapath.png>

Sinais:

- alu_ctrl: indica se a ALU vai fazer a conta ou não
- ng_cte_sub: indica qual eh o endereço atual do discipulo, o que vem do rand_num ou da ALU após subtração?
- rb_DISC_en: indica se o registrador da posição do discipulo está habilitado
- rb_PRE_DISC_en: indica se o registrador da posição anterior do discipulo está enabled
- rb_out_sel: seleciona qual registrador cuspirá o endereço de saída: o previous ou atual?
- cg_sel: indica o código a ser escrito na memória

## 2. Módulo subtrator
<img src=fullsub.jpg>
<img src=full_subtractor.jpg>
