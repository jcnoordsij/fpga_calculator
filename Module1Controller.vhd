----------------------------------------------------------------------------------
-- Company: Dartmouth College
-- Engineer: Carter Jacobsen and Carter Noordsij
-- 
-- Create Date: 03/26/2019 09:42:30 PM
-- Design Name: Module1Controller
-- Module Name: 
-- Project Name: Engs 128 Lab1
-- Target Devices: 
-- Tool Versions: 
-- Description: FSM Controller for Lab 1

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

entity controller is
Port ( clk: in std_logic;
        run: in std_logic;
        z_en: out std_logic;
        done: out std_logic;
        done_ack: in std_logic;
        dot_red: out std_logic;
        dot_ack: in std_logic;
        op_code: in std_logic_vector(2 downto 0));
end entity;

architecture fsm of controller is
    type state_type is (waiting, running, done_wait, dot_running, dot_wait, dot_compute);
    signal curr_st, next_st: state_type;
    
    constant dot_prod_running: std_logic_vector(2 downto 0) := "100";
    constant dot_prod_finished: std_logic_vector(2 downto 0) := "101";

begin
    sync_proc: process(CLK,next_st)
    begin
      if (rising_edge(CLK)) then
         curr_st <= next_st;
      end if;
    end process sync_proc;
    
    comb_process: process(curr_st, clk, run, done_ack, op_code, dot_ack)
    
    begin
        z_en <= '0';
        done <= '0';
        dot_red <= '0';
        
        case curr_st is
            when waiting =>
                if run = '1' and op_code(2) = '0' then
                    next_st <= running;
                elsif (op_code = dot_prod_running) and run = '1' then
                    next_st <=  dot_running;
                else
                    next_st <= waiting;
                end if;
                
            when running =>
                z_en <= '1';
                next_st <= done_wait;
                
            when done_wait =>
                done <= '1';
               
                if done_ack = '1' then
                    next_st <= waiting;
                else
                    next_st <= done_wait;
                end if;
                
            when dot_running =>
                dot_red <= '0';
                
                if op_code = dot_prod_finished then
                    next_st <= running;
                elsif dot_ack = '0' then
                    next_st <= dot_compute;
                else
                    next_st <= dot_running;
                end if;
                
            when dot_compute =>
            
                z_en <= '1';
                next_st <= dot_wait;
                
            when dot_wait =>
                dot_red <= '1';
                
                if dot_ack = '1' then
                    next_st <= dot_running;
                    
                elsif op_code = dot_prod_finished then
                    next_st <= running;
                else
                    next_st <= dot_wait;
                end if;
                
            when others =>
                next_st <= waiting;
         end case;
      end process comb_process;
                
end fsm;
