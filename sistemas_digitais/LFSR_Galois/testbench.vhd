-----------------------------------------------------------------------------
-- Escola Politécnica da Universidade de São Paulo
-- Dpto. Eng. Sistemas Eletrônicos
-- Autor: Lucas Penna Saraiva
-- Random_num
-- Testbench circuito gerador de números aleatórios
-- Prof. Wang Jiang Chau, Projeto de Circuitos Lógicos Integrados (PSI 3451)
------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity testbench_Rand_num is
end;

architecture test of testbench_Rand_num is

	-- Components

	Component Random_num

		port
		(
		b_1, b_2      :	out STD_LOGIC;
		clk, res      :	in STD_LOGIC
		);

	end Component;

	component stimuli is

		generic
		(
		CLK_PERIOD		: TIME	:=  10ns
		);

		port
		(
		clk : out std_logic;
		res : out std_logic;
		Q : in std_logic_vector (1 downto 0)
		);

	end component;

	signal clk, res, b_1, b_2 : STD_LOGIC;
	signal Q : std_logic_vector(1 downto 0);

	begin

		Q(0) <= b_1;
		Q(1) <= b_2;

		-- Instantiate stimuli generation module
		SIMULATION : stimuli port map (clk, res, Q);

		-- Instantiate DUT
		RAND : Random_num port map (b_1, b_2, clk, res);

end architecture test;
