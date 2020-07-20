-----------------------------------------------------------------------------
-- Escola Politécnica da Universidade de São Paulo
-- Dpto. Eng. Sistemas Eletrônicos
-- Autor: Lucas Penna Saraiva
-- Stimuli
-- Módulo de descrição dos estímulos para Testbench do LFSR
-- Prof. Wang Jiang Chau, Projeto de Circuitos Lógicos Integrados (PSI 3451)
------------------------------------------------------------------------------


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.NUMERIC_STD.all;

entity stimuli is

	generic
	(
	CLK_PERIOD		: TIME	:=  200ns
	);

	port
	(
	clk : out std_logic;
	res : out std_logic;
	Q : in std_logic_vector (1 downto 0)
	);

end stimuli;

architecture test of stimuli is

	component clock_generator

			generic (
			CLK_PERIOD		: TIME	:= 10ns
			);

			port (
			clk		: out STD_LOGIC
			);

	end component;

	signal clk_aux : std_logic;

	begin

		clock: clock_generator port map (clk_aux);

		-- Algoritmo de simulação
		--
		-- run 1ns
		-- force res_in 1
		-- force -freeze clk_in 1 0, 0 {100ns} -r 200
		-- run 200ns
		-- force res_in 0
		-- run 2000ns

		-- 1. Necessário carregar a SEED='1111111111' no LFSR para que os números pseudo-aleatórios sejam gerados
		-- Para carregar a SEED com '1's', reset=1.
		-- Após o primeiro ciclo de clock, o Reset=0
		-- Então, os números pseudo-aleatórios continuarão a ser gerados...

		simulation : process

			begin

				res <= '1';

				wait for 1*CLK_PERIOD;

				res <= '0';

				wait for 10*CLK_PERIOD;

				res <= '1';

			end process;

		clk <= clk_aux;

end architecture test;
