# Rodar isso em cada pasta p cada simulação

vlib work

vmap work work

# Nome do arquivo vhd
vcom -reportprogress 300 -work work C:/Users/lucas/Desktop/LSFR/d_reg.vhd

# Nome da architecture/entity
vsim -gui -voptargs=+acc work.d_reg

# Nome da architecture
add wave sim:/d_reg/*