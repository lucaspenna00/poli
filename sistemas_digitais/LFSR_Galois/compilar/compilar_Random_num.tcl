# Rodar isso em cada pasta p cada simulação

vlib work

vmap work work

# Nome do arquivo vhd
vcom -reportprogress 300 -work work C:/Users/lucas/Desktop/LSFR/Random_num.vhd

# Nome da architectureentity
vsim -gui -voptargs=+acc work.Random_num
# Nome da architecture
add wave sim:/Random_num/*