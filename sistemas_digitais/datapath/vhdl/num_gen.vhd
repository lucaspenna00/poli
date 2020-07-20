----------------------------------------------
-- Escola Politécnica da USP
-- Projeto de Circuitos Lógicos Integrados
-- Prof. Dr. Wang Jiang Chau
-- Módulo Num_Gen
-- Lucas Penna Saraiva e Beatriz Soares Passanezzi
--------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity num_gen is

  port (

  num_gen_in  : in STD_LOGIC_VECTOR(7 downto 0);

  clk         : in STD_LOGIC;

  res         : in STD_LOGIC;

  ng_cte_sub  : in STD_LOGIC;

  num_gen_out : out STD_LOGIC_VECTOR (7 downto 0)

  );

end num_gen;

Architecture dataflow of num_gen is

  -- RAND_NUM

  component Random_num

    port
    (
    rand_num_out  :	out STD_LOGIC_VECTOR(7 downto 0);
    clk     :	in STD_LOGIC;
    res     : in STD_LOGIC
    );

  end component;

  -- MULTIPLEXADOR

  COMPONENT mux

  generic( N	: natural  := 7);

  port(

    input_1    : in STD_LOGIC_VECTOR(N downto 0);

    input_2    : in STD_LOGIC_VECTOR(N downto 0);

    sel        : in STD_LOGIC;

    mux_output : out STD_LOGIC_VECTOR(N downto 0)

  );

  end COMPONENT;

  -- Sinais auxiliares internos

  signal num_gen_in_aux    : STD_LOGIC_VECTOR(7 downto 0);
  signal num_gen_out_aux   : STD_LOGIC_VECTOR(7 downto 0);
  signal rand_num_out_aux  : STD_LOGIC_VECTOR(7 downto 0);

  begin

    num_gen_in_aux <= num_gen_in;

    rand_num_gen : Random_num port map(rand_num_out_aux, clk, res);

    mux_gen : mux port map(rand_num_out_aux, num_gen_in_aux, ng_cte_sub, num_gen_out_aux);

    num_gen_out <= num_gen_out_aux;

  end dataflow;
