
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
USE ieee.std_logic_arith.all;
USE ieee.std_logic_unsigned.all;
USE ieee.numeric_std.ALL;
USE generics.components.ALL;

ENTITY testbench IS
END testbench;

ARCHITECTURE behavior OF testbench IS 

	COMPONENT top_lev
	port (
--		-- JTAG
--		TDI 			: in  std_logic;
--		TDO 			: out std_logic;
--		TCK 			: in  std_logic;
--		TMS 			: in  std_logic;


		-- GLOBAL
		RESETn 			: in  std_logic;

		-- Clock Divider
		C_20MHZ 		: in  std_logic;
		C_10MHZ			: out std_logic;
		C_10KHZ 		: in  std_logic;
		C_PPS			: in  std_logic;
		C_2MHZ5			: out std_logic;
		
		-- Phase Error Determination
		SYNC  			: in  std_logic;
		SYNC_COR		: out std_logic;
		GATE_TRIG 		: out std_logic;
		GATE  			: in  std_logic;
		GATE_COR		: out std_logic;
		PHASE_RSFF		: out std_logic;
		PHASE 			: out std_logic;

		-- Serial Communications
		SER_GPS			: in  std_logic;
		ISP_TXD			: in  std_logic;
		ISP_RXD			: out std_logic;
		GPS_RXD			: in  std_logic;
		GPS_TXD			: out std_logic;
		MCU_TXD			: in  std_logic;
		MCU_RXD			: out std_logic
	);
	END COMPONENT;

	SIGNAL RESETn			:     std_logic;
	SIGNAL C_20MHZ			:     std_logic;
	SIGNAL C_10MHZ			:     std_logic;
	SIGNAL C_10KHZ			:     std_logic;
	SIGNAL C_PPS			:     std_logic;
	SIGNAL C_2MHZ5			:     std_logic;

	SIGNAL SYNC			:     std_logic;
	SIGNAL SYNC_COR			:     std_logic;
	SIGNAL GATE_TRIG		:     std_logic;
	SIGNAL GATE			:     std_logic;
	SIGNAL GATE_COR			:     std_logic;
	SIGNAL PHASE_RSFF		:     std_logic;
	SIGNAL PHASE			:     std_logic;

	SIGNAL SER_GPS			:     std_logic;
	SIGNAL ISP_TXD			:     std_logic;
	SIGNAL ISP_RXD			:     std_logic;
	SIGNAL GPS_RXD			:     std_logic;
	SIGNAL GPS_TXD			:     std_logic;
	SIGNAL MCU_TXD			:     std_logic;
	SIGNAL MCU_RXD			:     std_logic;

BEGIN

	uut: top_lev PORT MAP(
		RESETn => RESETn,

		C_20MHZ => C_20MHZ,
		C_10MHZ => C_10MHZ,
		C_10KHZ => C_10KHZ,
		C_PPS => C_PPS,
		C_2MHZ5 => C_2MHZ5,

		SYNC => SYNC,
		SYNC_COR => SYNC_COR,
		GATE_TRIG => GATE_TRIG,
		GATE => GATE,
		GATE_COR => GATE_COR,
		PHASE_RSFF => PHASE_RSFF,
		PHASE => PHASE,

		SER_GPS => SER_GPS,
		ISP_TXD => ISP_TXD,
		ISP_RXD => ISP_RXD,
		GPS_RXD => GPS_RXD,
		GPS_TXD => GPS_TXD,
		MCU_TXD => MCU_TXD,
		MCU_RXD => MCU_RXD
	);



-- *** Test Bench - User Defined Section ***

	tb_RESETn : PROCESS
	BEGIN
		RESETn <= '0'; WAIT FOR 250 NS;
		RESETn <= '1';
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
			C_10KHZ <= '1'; WAIT FOR  1024 NS;
			C_10KHZ <= '0'; WAIT FOR 98976 NS;
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
			WAIT FOR 40 NS;
			Sync <= '1'; WAIT FOR  50 NS;
			Sync <= '0'; WAIT FOR 310 NS;
		END LOOP;
	WAIT;  -- will wait forever
	END PROCESS;


	tb_GATE : PROCESS
	BEGIN
		FOR igate IN 0 TO 9999 LOOP
			WAIT FOR 40 NS;
			Gate <= '1'; WAIT FOR   362 NS;
			Gate <= '0'; WAIT FOR 99598 NS;
		END LOOP;
	WAIT;  -- will wait forever
	END PROCESS;


	tB_SER_GPS : PROCESS
	BEGIN
		SER_GPS <= '1';
	WAIT;  -- will wait forever
	END PROCESS;


	tB_ISP_TXD : PROCESS
	BEGIN
		ISP_TXD <= '1';
	WAIT;  -- will wait forever
	END PROCESS;


	tB_GPS_RXD : PROCESS
	BEGIN
		GPS_RXD <= '1';
	WAIT;  -- will wait forever
	END PROCESS;


	tB_MCU_TXD : PROCESS
	BEGIN
		MCU_TXD <= '1';
	WAIT;  -- will wait forever
	END PROCESS;

-- *** End Test Bench - User Defined Section ***

END;

