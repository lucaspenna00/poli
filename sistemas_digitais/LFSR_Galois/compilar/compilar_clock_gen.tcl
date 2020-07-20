# Rodar isso em cada pasta p cada simulação

vlib work

vmap work work

# Nome do arquivo vhd
vcom -reportprogress 300 -work work C:/Users/lucas/Desktop/LSFR/clock_generator.vhd

# Nome da architectureentity
vsim -gui -voptargs=+acc work.clock_generator

# Nome da architecture
add wave sim:/clock_generator/*