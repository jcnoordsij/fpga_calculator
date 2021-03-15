----------------------------------------------------------------------------------
-- Company: Dartmouth College
-- Engineer: Carter Jacobsen and Carter Noordsij
-- 
-- Create Date: 03/26/2019 09:42:30 PM
-- Design Name: Module1Data
-- Module Name: 
-- Project Name: Engs 128 Lab1
-- Target Devices: 
-- Tool Versions: 
-- Description: Datapath for lab 1

----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity module1data is
  generic(DATA_WIDTH: integer := 32 );
  Port (clk: in std_logic;
        x: in std_logic_vector(DATA_WIDTH-1 downto 0);
        y: in std_logic_vector(DATA_WIDTH-1 downto 0);
        z_en: in std_logic;
        ctrl_reg: in std_logic_vector(DATA_WIDTH/2-1 downto 0);
        z: out std_logic_vector(DATA_WIDTH-1 downto 0));
end entity;

architecture behavior of module1data is

signal ux : signed(DATA_WIDTH/2-1 downto 0);
signal uy : signed(DATA_WIDTH/2-1 downto 0);
signal uz : signed(DATA_WIDTH-1 downto 0) := (others => '0');
signal op_code: std_logic_vector(2 downto 0);

constant add: std_logic_vector(2 downto 0) := "001";
constant sub: std_logic_vector(2 downto 0) := "010";
constant mult: std_logic_vector(2 downto 0) := "011";
constant reset: std_logic_vector(2 downto 0) := "000";
constant dot_prod_running: std_logic_vector(2 downto 0) := "100";
constant dot_prod_finished: std_logic_vector(2 downto 0) := "101";


begin
    ux <= signed(x(DATA_WIDTH/2-1 downto 0));
    uy <= signed(y(DATA_WIDTH/2-1 downto 0));
    z <= std_logic_vector(uz);
    op_code <= ctrl_reg(2 downto 0);
    
    process(clk, op_code, x, y)
    begin
        if rising_edge(clk) then
                if z_en = '1' then
                case op_code is
                    when reset =>
                        uz <= (others => '0');
                    when add =>
                        uz <= resize(ux+uy,DATA_WIDTH);
                    when sub =>
                        uz <= resize(ux - uy,DATA_WIDTH);
                    when mult =>
                        uz <= ux*uy;
                    when dot_prod_running =>
                        uz <= uz + ux*uy;
                    when dot_prod_finished =>
                        uz <= uz + ux*uy;
                    when others =>
                        uz <= (others => '0');
                    end case;
                end if;
            end if;
      end process;
      
                
end behavior;
