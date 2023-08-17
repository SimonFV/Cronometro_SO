
module platform (
	clk_clk,
	reset_reset_n,
	pio_leds_0_external_connection_export,
	pio_switch_0_external_connection_export);	

	input		clk_clk;
	input		reset_reset_n;
	output	[9:0]	pio_leds_0_external_connection_export;
	input		pio_switch_0_external_connection_export;
endmodule
