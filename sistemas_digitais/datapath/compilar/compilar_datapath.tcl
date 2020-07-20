# Rodar isso em cada pasta p cada simulação

vlib work

vmap work work

# Nome do arquivo vhd
vcom -reportprogress 300 -work work C:/Users/lucas/Desktop/datapath/datapath.vhd

# Nome da architectureentity
vsim -gui -voptargs=+acc work.datapath

# Nome da architecture
add wave sim:/datapath/*