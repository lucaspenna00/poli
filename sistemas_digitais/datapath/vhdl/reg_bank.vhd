----------------------------------------------
-- Escola Politécnica da USP
-- Projeto de Circuitos Lógicos Integrados
-- Prof. Dr. Wang Jiang Chau
-- Módulo Reg Bank
-- Lucas Penna Saraiva e Beatriz Soares Passanezzi
--------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

Entity reg_bank is

   generic (N: natural := 7); --! Tamanho do registrador N+1 bits

   port (

        clk : in STD_LOGIC;
        res : in STD_LOGIC;

        -- Sinais da Máquina de Estados
        rb_pre_disc_en : in STD_LOGIC;
        rb_out_sel     : in STD_LOGIC;
        rb_disc_en     : in STD_LOGIC;
        ------------------------------

        address_in  : in STD_LOGIC_VECTOR (N downto 0);

        address_out : out STD_LOGIC_VECTOR (N downto 0);

        reg_disc_out : out STD_LOGIC_VECTOR (N downto 0)

        );

End reg_bank;

architecture dataflow of reg_bank is

  -- REGISTRADOR

  COMPONENT reg

    generic
    (
    WIDTH	: natural  := 8
    );

    port
  	(
  	clk  : in  STD_LOGIC;
  	clr  : in  STD_LOGIC;
  	load : in  STD_LOGIC;
  	d    : in  STD_LOGIC_VECTOR(WIDTH-1 downto 0);
  	q	  : out STD_LOGIC_VECTOR(WIDTH-1 downto 0)
  	);

  end COMPONENT;

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

  signal address_out_aux   : STD_LOGIC_VECTOR (N downto 0);
  signal reg_disc_prev_out : STD_LOGIC_VECTOR (N downto 0);
  signal reg_disc_out_aux : STD_LOGIC_VECTOR (N downto 0);

begin

  reg_disc      : reg port map (clk, res, rb_disc_en, address_in, address_out_aux);

  reg_disc_prev : reg port map (clk, res, rb_pre_disc_en, address_out_aux, reg_disc_prev_out);

  mux_reg_bank  : mux port map (address_out_aux, reg_disc_prev_out, rb_out_sel, reg_disc_out_aux);

  reg_disc_out <= reg_disc_out_aux;

  address_out <= address_out_aux;

end dataflow;
