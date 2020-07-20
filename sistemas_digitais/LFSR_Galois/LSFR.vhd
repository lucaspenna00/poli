-----------------------------------------------------------------------------
-- Escola Politécnica da Universidade de São Paulo
-- Dpto. Eng. Sistemas Eletrônicos
-- Autor: Lucas Penna Saraiva
-- LFSR configuração Galois
-- Descrição HDL de um gerador de números pseudo-aleatórios
-- Prof. Wang Jiang Chau, Projeto de Circuitos Lógicos Integrados (PSI 3451)
------------------------------------------------------------------------------

Library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity LSFR is

	port
	(
	Q_lsfr		    :	out STD_LOGIC_VECTOR (11 downto 0);
	clk_in, res_in			:	in STD_LOGIC
	);

end LSFR;


architecture structural of LSFR is

	-- 1. DECLARANDO COMPONENTS

	-- 1.1 FLIP FLOP COMPONENT
	COMPONENT d_reg

				generic (t_ff: time := 2 ns);

				port
				(
				clk  : in  STD_LOGIC;
				load : in  STD_LOGIC;
				d    : in  STD_LOGIC;
				q	 : out STD_LOGIC
				);

	END COMPONENT;

	-- 1.2 XOR2 Componnt

	COMPONENT xor2

		GENERIC(t_xor : time := 4 ns);

		PORT( x, y: IN STD_LOGIC;
			    z: OUT STD_LOGIC);

	END COMPONENT;

	--1.3 OR2 Component

	COMPONENT or2

		GENERIC(t_or : time := 4 ns);

		PORT( x, y: IN STD_LOGIC;
			    z: OUT STD_LOGIC);

	END COMPONENT;

	-- 2. DECLARANDO SINAIS INTERNOS

	-- Sinais auxiliares entre os FF's
	signal d_aux : STD_LOGIC_VECTOR(11 downto 0);
	signal or2_aux : STD_LOGIC_VECTOR(11 downto 0);
	signal q_aux : STD_LOGIC_VECTOR(11 downto 0);

	-- Sinais auxiliares para puxar da entity
	signal res : STD_LOGIC;
	signal clk : STD_LOGIC;

	begin

		res <= res_in;

		clk <= clk_in;

		-- NUSP = 9770566

		-- NUSP_bin = 11001000110

		--Casos em que FF_1: N=2, N=3, N=7, N=10, N=11

		LSFR : for N in 11 downto 0 generate

			-- Caso em que é o LSB, com realimentação para o primeiro flip flop da direita
			LSB_FF : if (N = 0) generate

				-- Or entre o bit mais significativo (que a gente puxou da realimentação)
				-- e o sinal da entrada do primeiro FF (referente ao Bit menos significativo)

				or_2 : or2 port map(res, q_aux(11), d_aux(N));

				-- Primeiro flip flop do LSFR

				ffD  : d_reg port map (clk, '1', d_aux(N), q_aux(N));

			end generate LSB_FF;

			-- Caso para o qual temos um XOR entre os Flip Flop's
			FF_1 : if (N = 2) or (N = 3) or (N = 7) or (N = 10) or (N = 11) generate

				-- Faremos um XOR entre o bit mais significativo e saída do FF anterior.
				--Sua saída irá para a entradad do OR2, conforme especificado na apostila.

				xor_2 : xor2 port map (q_aux(11), q_aux(N-1), or2_aux(N));

				-- Or entre o RES e a saída do xor. A saída desse OR estará conectado a entrada
				-- do Flip Flop D essa iteração. O Or existe para as condições iniciais do LSFR funcionarem!

				or_2_FF1 : or2 port map (res, or2_aux(N), d_aux(N));

				-- Conectando a saída do OR para o FF_1

				FF_1 : d_reg port map (clk, '1', d_aux(N), q_aux(N));

			end generate FF_1;

			-- Caso para os quais não há um xor entre os FF's (N != 0)
			FF_0 : if(N=1) or (N=4) or (N=5) or (N=6) or (N=8) or (N=9) generate

				-- Or entre o RES e a saída do Flip Flop anterior. A saída desse OR estará conectado a entrada
				-- do Flip Flop D essa iteração. O Or existe para as condições iniciais do LSFR funcionarem!

				or_2_FF0 : or2 port map (res, q_aux(N-1), d_aux(N));

				-- Conectando a saída do OR para o FF_0

				FF_0 : d_reg port map (clk, '1', d_aux(N), q_aux(N));

			end generate FF_0;

		end generate LSFR;

		-- Pegando  os primeiros dois bits menos signicativos como saída do gerador de números aleatórios
		-- conforme especificação de projeto.

		Q_lsfr <= q_aux;

end structural;
