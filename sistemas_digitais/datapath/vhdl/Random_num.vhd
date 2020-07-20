-----------------------------------------------------------------------------
-- Escola Politécnica da Universidade de São Paulo
-- Dpto. Eng. Sistemas Eletrônicos
-- Autor: Lucas Penna Saraiva
-- Random_num
-- Módulo gerador de dois bits pseudo-aleatórios
-- Prof. Wang Jiang Chau, Projeto de Circuitos Lógicos Integrados (PSI 3451)
------------------------------------------------------------------------------

Library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity Random_num is

	port
	(
	rand_num_out  :	out STD_LOGIC_VECTOR(7 downto 0);
	clk      :	in STD_LOGIC;
	res      : in STD_LOGIC
	);

end Random_num;


Architecture structural of Random_num is

	-- COMPONENT

	Component LSFR

		port
		(
		Q_lsfr		        :	out STD_LOGIC_VECTOR (11 downto 0);
		clk_in		:	in STD_LOGIC;
		res_in    : in STD_LOGIC
		);

	end Component;

	-- INTERNAL SIGNALS

	signal Q_lsfr_aux       : STD_LOGIC_VECTOR (11 DOWNTO 0);
	signal rand_num_out_aux : STD_LOGIC_VECTOR (7 DOWNTO 0);

	begin

		LSFR_l : LSFR port map(Q_lsfr_aux, clk, res);

		rand_num_out_aux(0) <= Q_lsfr_aux(0);
		rand_num_out_aux(1) <= Q_lsfr_aux(1);
		rand_num_out_aux(2) <= '1';
		rand_num_out_aux(3) <= '1';
		rand_num_out_aux(4) <= '1';
		rand_num_out_aux(5) <= '1';
		rand_num_out_aux(6) <= '0';
		rand_num_out_aux(7) <= '0';

		rand_num_out <= rand_num_out_aux;


End structural;
