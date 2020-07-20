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
	b_1, b_2      :	out STD_LOGIC;
	clk, res      :	in STD_LOGIC
	);

end Random_num;


Architecture structural of Random_num is

	-- COMPONENT

	Component LSFR

		port
		(
		Q_lsfr		        :	out STD_LOGIC_VECTOR (11 downto 0);
		clk_in, res_in		:	in STD_LOGIC
		);

	end Component;

	-- INTERNAL SIGNALS

	signal Q_lsfr_aux : STD_LOGIC_VECTOR (11 DOWNTO 0);

	begin

		LSFR_l : LSFR port map(Q_lsfr_aux, clk, res);

		b_1 <= Q_lsfr_aux(0);
		b_2 <= Q_lsfr_aux(1);

End structural;
