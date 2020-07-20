-----------------------------------
-- Projeto do Datapath Top Level
-- Lucas Penna Saraiva e Beatriz Soares Passanezzi
-- Escola Politécnica da USP
------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use work.wisdom_package.all;

entity datapath is

  generic (N: natural := 7); --! Tamanho do subtrator N+1 bits

  port (

  alu_ctr           : in STD_LOGIC;
  ng_cte_sub        : in STD_LOGIC;
  cg_sel            : in CODE;
  rb_disc_en        : in STD_LOGIC;
  rb_pre_disc_en    : in STD_LOGIC;
  rb_out_sel        : in STD_LOGIC;
  res               : in STD_LOGIC;

  mem_code_w        : out STD_LOGIC_VECTOR(N downto 0);
  ctrl_flags        : out disc_2_base_flags;
  reg_disc_out      : out STD_LOGIC_VECTOR(N downto 0)

  );

end datapath;

architecture dataflow of datapath is

  -- Declaração dos Componentes

  ---- SUBTRATOR ----

  Component full_subtractor_Nbits

    generic (N_bits: natural := 7); --! Tamanho do subtrator N+1 bits

    Port ( A          : in STD_LOGIC_VECTOR (N_bits downto 0);

           B          : in STD_LOGIC_VECTOR (N_bits downto 0);

           borrow_in  : in STD_LOGIC;

           diff       : out STD_LOGIC_VECTOR (N_bits downto 0);

           borrow_out : out STD_LOGIC);

  end component;

  ---- NUM_GEN ---------

  Component num_gen

    port (

    num_gen_in  : in STD_LOGIC_VECTOR(7 downto 0);

    clk         : in STD_LOGIC;

    res         : in STD_LOGIC;

    ng_cte_sub  : in STD_LOGIC;

    num_gen_out : out STD_LOGIC_VECTOR (7 downto 0)

    );

  end component;

  ---- REG_BANK ---------

  Component reg_bank

  generic (N: natural := 7); --! Tamanho do registrador N+1 bits

  port (

       clk : in STD_LOGIC;
       res : in STD_LOGIC;

       rb_pre_disc_en : in STD_LOGIC;
       rb_out_sel     : in STD_LOGIC;
       rb_disc_en     : in STD_LOGIC;

       address_in  : in STD_LOGIC_VECTOR (N downto 0);

       address_out : out STD_LOGIC_VECTOR (N downto 0);

       reg_disc_out : out STD_LOGIC_VECTOR (N downto 0)

       );

  end component;

  --- COLL_OVF ---

  Component coll_ovf

    port
    (
    clk			      : in  STD_LOGIC;											--from system
    res				    : in  STD_LOGIC;										   --from system
    disc_addr     : in  STD_LOGIC_VECTOR(7 downto 0);
    ctrl_flags		: out disc_2_base_flags					     	--to control unit
    );

  end component;

  -- Code Generator ----

  Component code_gen

    port
    (
    ctrl_code_sel	: in CODE;
    mem_code_w		: out STD_LOGIC_VECTOR(7 downto 0)
    );

  end component;

  -- Clock Generator ----

  Component clock_generator

    generic( CLK_PERIOD		: TIME	:= 200ns);

    port
    (
    clk		: out STD_LOGIC
    );

  end component;

  -- sinais internos

  signal address_out_aux  : STD_LOGIC_VECTOR(N downto 0);
  signal SUB_CTE          : STD_LOGIC_VECTOR(N downto 0);
  signal num_gen_in_aux   : STD_LOGIC_VECTOR(N downto 0);
  signal num_gen_out_aux  : STD_LOGIC_VECTOR(N downto 0);
  signal address_in_aux   : STD_LOGIC_VECTOR(N downto 0);
  signal reg_disc_out_aux : STD_LOGIC_VECTOR(N downto 0);
  signal mem_code_w_aux   : STD_LOGIC_VECTOR(N downto 0);
  signal borrow_out_aux   : STD_LOGIC;
  signal ctrl_flags_aux   : disc_2_base_flags;
  signal clk              : STD_LOGIC;

  begin

    SUB_CTE <= "00001000";

    clock_gen        : clock_generator port map (clk);

    alu_subtractor   : full_subtractor_Nbits port map(address_out_aux, SUB_CTE, '0', num_gen_in_aux, borrow_out_aux);

    num_gen_1        : num_gen port map (num_gen_in_aux, clk, res, ng_cte_sub, num_gen_out_aux);

    address_in_aux <= num_gen_out_aux;

    reg_bank_1       : reg_bank port map(clk, res, rb_pre_disc_en, rb_out_sel, rb_disc_en, address_in_aux, address_out_aux, reg_disc_out_aux);

    coll_ovf_1       : coll_ovf port map(clk, res, address_out_aux, ctrl_flags_aux);

    code_gen_1       : code_gen port map(cg_sel, mem_code_w_aux);

    reg_disc_out <= reg_disc_out_aux;
    ctrl_flags <= ctrl_flags_aux;
    mem_code_w <= mem_code_w_aux;

end dataflow;
