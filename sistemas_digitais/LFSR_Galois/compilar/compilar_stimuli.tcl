# Rodar isso em cada pasta p cada simulação

vlib work

vmap work work

# Nome do arquivo vhd
vcom -reportprogress 300 -work work C:/Users/lucas/Desktop/LSFR/stimuli.vhd

# Nome da architectureentity
vsim -gui -voptargs=+acc work.stimuli

# Nome da architecture
add wave sim:/stimuli/*