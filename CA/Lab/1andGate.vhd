library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
entity AND_GATE is
	Port
	(
		A : in STD_LOGIC; -- INPUT A
		B : in STD_LOGIC; -- INPUT B
		Y : out STD_LOGIC -- OUTPUT Y
	);
end AND_GATE;
architecture Behavior of AND_GATE is begin
	Y <= A AND B;
end Behavior;