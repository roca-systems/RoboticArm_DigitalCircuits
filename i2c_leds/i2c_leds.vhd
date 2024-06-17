library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity i2c_leds is 
 port(
	scl   : inout std_logic;
	sda   : inout std_logic;
	clk   : in   std_logic;
	rst   : in   std_logic;
	Displays : out std_logic_vector(3 downto 0);
	Segmentos : out std_logic_vector(6 downto 0)
 );
end entity;

architecture RTL of i2c_leds is

signal read_req         : std_logic;
signal data_to_master   : std_logic_vector(7 downto 0);
signal data_valid       : std_logic;
signal data_from_master : std_logic_vector(7 downto 0);

signal data_reg         : std_logic_vector(7 downto 0);

-- Señales del multiplexor
signal Cuenta : integer range 0 to 100000;
signal Seleccion : std_logic_vector(1 downto 0) :="00";
signal Mostrar : std_logic_vector(3 downto 0):= "0000";
signal Num1, Num2, Num3, Num4 : std_logic_vector(6 downto 0);

begin

i2c_slave0: entity work.I2C_slave(arch) 
    port map (
        scl => scl, 
        sda => sda, 
        clk => clk, 
        rst => rst, 
        read_req => read_req, 
        data_to_master => data_to_master, 
        data_valid => data_valid, 
        data_from_master => data_from_master
    );

data_to_master <= data_reg;

process(clk)
begin
    if rising_edge(clk) then 
        if data_valid = '1' then 
            data_reg <= data_from_master;
        end if;
    end if;
end process;

-- Multiplexor
Conteo_clk:  Process(clk)
begin
    if rising_edge(clk) then 
        if Cuenta < 100000 then
            Cuenta <= Cuenta + 1;
        else
            Seleccion <= Seleccion + 1;
            Cuenta <= 0;
        end if;
    end if;
end process;
	
Mostrar_Displays: process(Seleccion)
begin
    case Seleccion is
        when "00" => Mostrar <= "1110";
        when "01" => Mostrar <= "1101";
        when "10" => Mostrar <= "1011";
        when "11" => Mostrar <= "0111";
        when others => Mostrar <= "1111";
    end case;

    case Mostrar is 
        when "1110" => Segmentos <= Num4;
        when "1101" => Segmentos <= Num3;
        when "1011" => Segmentos <= Num2;
        when "0111" => Segmentos <= Num1;
        when others => Segmentos <= "1111111";
    end case;
end process;

Displays <= Mostrar;

process(data_reg)
begin
    case data_reg is
        when "00000001" => -- Caso 1
            Num1 <= "1001111";
            Num2 <= "1000110";
            Num3 <= "0000110";
            Num4 <= "0010010";
        when "00000010" => -- Caso 2
            Num1 <= "0100100";
            Num2 <= "1000110";
            Num3 <= "0000110";
            Num4 <= "0010010";
        when "00000011" => -- Caso 3
            Num1 <= "0110000";
            Num2 <= "1000110";
            Num3 <= "0000110";
            Num4 <= "0010010";
        when "00000100" => -- Caso 4
            Num1 <= "0011001";
            Num2 <= "1000110";
            Num3 <= "0000110";
            Num4 <= "0010010";
        when "00000101" => -- Caso 5
            Num1 <= "0010010";
            Num2 <= "1000110";
            Num3 <= "0000110";
            Num4 <= "0010010";
        when others =>
            Num1 <= "1111111";
            Num2 <= "1111111";
            Num3 <= "1111111";
            Num4 <= "1111111";
    end case;
end process;

end architecture;