run 1ns
force res 1
force -freeze clk 1 0, 0 {100ns} -r 200
run 200ns
force res 0
run 4000ns