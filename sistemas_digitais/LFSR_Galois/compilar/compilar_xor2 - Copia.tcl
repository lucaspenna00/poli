# Rodar isso em cada pasta p cada simulação

vlib work

vmap work work

# Nome do arquivo vhd
vcom -reportprogress 300 -work work C:/Users/lucas/Desktop/LSFR/XOR2.vhd

# Nome da architectureentity
vsim -gui -voptargs=+acc work.xor2

# Nome da architecture
add wave sim:/xor2/*