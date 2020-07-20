----------------------------------------------------|
-- Circuito Multiplexador
-- Escola POlitécnica da USP
-- Projeto de Circuitos Lógicos Integrados
-- Prof. Dr. Wang Jiang Chau
-- Lucas Penna Saraiva e Beatriz Soares Passanezzi
---------------------------------------------------

-- Se sel=0, saída será input_1
-- Se sel=1, saída será input_2

library ieee;
use ieee.std_logic_1164.all;

entity mux is


  generic( N	: natural  := 7);

  port(

  input_1    : in STD_LOGIC_VECTOR(N downto 0);

  input_2    : in STD_LOGIC_VECTOR(N downto 0);

  sel        : in STD_LOGIC;

  mux_output : out STD_LOGIC_VECTOR(N downto 0)

  );

end mux;

architecture behavioural of mux is

  signal mux_output_aux : STD_LOGIC_VECTOR(N downto 0);

  begin

    mux_output_aux <= input_1 WHEN sel = '0'  else input_2;

    mux_output <= mux_output_aux;

end behavioural;
