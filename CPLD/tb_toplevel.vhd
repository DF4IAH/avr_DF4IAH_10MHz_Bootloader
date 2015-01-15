
-- VHDL Test Bench Created from source file top_lev.vhd -- 01/15/15  22:42:36
--
-- Notes: 
-- 1) This testbench template has been automatically generated using types
-- std_logic and std_logic_vector for the ports of the unit under test.
-- Lattice recommends that these types always be used for the top-level
-- I/O of a design in order to guarantee that the testbench will bind
-- correctly to the timing (post-route) simulation model.
-- 2) To use this template as your testbench, change the filename to any
-- name of your choice with the extension .vhd, and use the "source->import"
-- menu in the ispLEVER Project Navigator to import the testbench.
-- Then edit the user defined section below, adding code to generate the 
-- stimulus for your design.
--
LIBRARY ieee;
LIBRARY generics;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
USE generics.components.ALL;

ENTITY testbench IS
END testbench;

ARCHITECTURE behavior OF testbench IS 

	COMPONENT top_lev
	PORT(
		RESET : IN std_logic;
		C_20MHZ : IN std_logic;
		C_10KHZ : IN std_logic;
		C_PPS : IN std_logic;
		PPS : IN std_logic;
		Sync : IN std_logic;
		Gate : IN std_logic;          
		C_10MHZ : OUT std_logic;
		C_2MHZ5 : OUT std_logic;
		GateTrig : OUT std_logic;
		Phase : OUT std_logic
		);
	END COMPONENT;

	SIGNAL RESET :  std_logic;
	SIGNAL C_20MHZ :  std_logic;
	SIGNAL C_10MHZ :  std_logic;
	SIGNAL C_10KHZ :  std_logic;
	SIGNAL C_PPS :  std_logic;
	SIGNAL C_2MHZ5 :  std_logic;
	SIGNAL PPS :  std_logic;
	SIGNAL Sync :  std_logic;
	SIGNAL GateTrig :  std_logic;
	SIGNAL Gate :  std_logic;
	SIGNAL Phase :  std_logic;

BEGIN

	uut: top_lev PORT MAP(
		RESET => RESET,
		C_20MHZ => C_20MHZ,
		C_10MHZ => C_10MHZ,
		C_10KHZ => C_10KHZ,
		C_PPS => C_PPS,
		C_2MHZ5 => C_2MHZ5,
		PPS => PPS,
		Sync => Sync,
		GateTrig => GateTrig,
		Gate => Gate,
		Phase => Phase
	);



-- *** Test Bench - User Defined Section ***

	tb_RESET : PROCESS
	BEGIN
		RESET <= '1'; WAIT FOR 250 NS;
		RESET <= '0';
	WAIT;  -- will wait forever
	END PROCESS;


	tb_C_20MHZ : PROCESS
	BEGIN
		FOR i20m IN 0 TO 199999999 LOOP
			C_20MHZ <= '1'; WAIT FOR 50 NS;
			C_20MHZ <= '0'; WAIT FOR 50 NS;
		END LOOP;
	WAIT;  -- will wait forever
	END PROCESS;


	tb_C_10KHZ : PROCESS
	BEGIN
		FOR i10k IN 0 TO 9999 LOOP
			C_10KHZ <= '1'; WAIT FOR 12800 NS;
			C_10KHZ <= '0'; WAIT FOR 87200 NS;
		END LOOP;
	WAIT;  -- will wait forever
	END PROCESS;

	tb_C_PPS : PROCESS
	BEGIN
		FOR ipps IN 0 TO 999 LOOP
			C_PPS <= '1'; WAIT FOR   1 MS;
			C_PPS <= '0'; WAIT FOR 999 MS;
		END LOOP;
	WAIT;  -- will wait forever
	END PROCESS;

	tb_SYNC : PROCESS
	BEGIN
		FOR isync IN 0 TO 99999999 LOOP
			Sync <= '1'; WAIT FOR 33 NS;
			Sync <= '0'; WAIT FOR 67 NS;
		END LOOP;
	WAIT;  -- will wait forever
	END PROCESS;

	tb_GATE : PROCESS
	BEGIN
		FOR igate IN 0 TO 9999 LOOP
			Gate <= '1'; WAIT FOR   362 NS;
			Gate <= '0'; WAIT FOR 99638 NS;
		END LOOP;
	WAIT;  -- will wait forever
	END PROCESS;

-- *** End Test Bench - User Defined Section ***

END;

