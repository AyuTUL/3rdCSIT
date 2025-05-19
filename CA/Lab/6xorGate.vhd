library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
entity XOR_GATE is
	Port
	(
		A : in STD_LOGIC; -- INPUT A
		B : in STD_LOGIC; -- INPUT B
		Y : out STD_LOGIC -- OUTPUT Y
	);
end XOR_GATE;
architecture Behavior of XOR_GATE is begin
	Y <= A XOR B;
end Behavior;