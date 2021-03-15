----------------------------------------------------------------------------------
-- Company: Dartmouth College
-- Engineer: Carter Jacobsen and Carter Noordsij
-- 
-- Create Date: 03/26/2019 09:42:30 PM
-- Design Name: Module1Top
-- Module Name: 
-- Project Name: Engs 128 Lab1
-- Target Devices: 
-- Tool Versions: 
-- Description: Top of logic IP for lab 1

----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity module1top is
    generic(DATA_WIDTH: integer := 32 );
  Port (clk: in std_logic;
        ctrl_reg: in std_logic_vector(DATA_WIDTH/2-1 downto 0);
        x_in,
        y_in: in std_logic_vector(DATA_WIDTH-1 downto 0);
        z_out: out std_logic_vector(DATA_WIDTH-1 downto 0);
        done: out std_logic;
        dot_red: out std_logic);
end entity;

architecture Behavioral of module1top is

component controller is port(
        clk: in std_logic;
        run: in std_logic;
        z_en: out std_logic;
        done: out std_logic;
        done_ack: in std_logic;
        dot_red: out std_logic;
        dot_ack: in std_logic;
        op_code: in std_logic_vector(2 downto 0));
end component;

component module1data is port(
        clk: in std_logic;
        x: in std_logic_vector(DATA_WIDTH-1 downto 0);
        y: in std_logic_vector(DATA_WIDTH-1 downto 0);
        z_en: in std_logic;
        ctrl_reg: in std_logic_vector(DATA_WIDTH/2-1 downto 0);
        z: out std_logic_vector(DATA_WIDTH-1 downto 0));
 end component;

signal reset : std_logic := '0';
signal z_en: std_logic := '0';

begin
    controller_mod: controller port map(clk=>clk, run => ctrl_reg(3), z_en => z_en, done => done, done_ack => ctrl_reg(4), dot_ack => ctrl_reg(5), dot_red => dot_red, op_code => ctrl_reg(2 downto 0));
    datapath: module1data port map(clk=>clk, x => x_in, y => y_in, z_en => z_en, ctrl_reg => ctrl_reg, z => z_out);

    
end Behavioral;
