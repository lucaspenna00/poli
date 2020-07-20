# Rodar isso em cada pasta p cada simulação

vlib work

vmap work work

# Nome do arquivo vhd
vcom -reportprogress 300 -work work C:/Users/lucas/Desktop/LSFR/LSFR.vhd

# Nome da architectureentity
vsim -gui -voptargs=+acc work.LSFR
# Nome da architecture
add wave sim:/LSFR/*