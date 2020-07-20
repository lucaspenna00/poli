-- Full subtractor of 1 bit
-- Projeto do Datapath - módulo subtrator de 1 bit

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity full_subtractor is

 Port ( A_i          : in STD_LOGIC;

        B_i          : in STD_LOGIC;

        borrow_in_i  : in STD_LOGIC;

        diff_i       : out STD_LOGIC;

        borrow_out_i : out STD_LOGIC);

end full_subtractor;

architecture dataflow of full_subtractor is

begin

 diff_i <= (A_i XOR B_i) XOR borrow_in_i;

 borrow_out_i <= (not(A_i) AND B_i) OR (borrow_in_i and NOT( A_i XOR B_i));

end dataflow;

-- Ref: https://basicenggknowledge.blogspot.com/2018/01/vhdl-code-and-circuit-diagram-for-full.html
