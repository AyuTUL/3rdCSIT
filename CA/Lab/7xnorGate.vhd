library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
entity XNOR_GATE is
	Port
	(
		A : in STD_LOGIC; -- INPUT A
		B : in STD_LOGIC; -- INPUT B
		Y : out STD_LOGIC -- OUTPUT Y
	);
end XNOR_GATE;
architecture Behavior of XNOR_GATE is begin
	Y <= A XNOR B;
end Behavior;
