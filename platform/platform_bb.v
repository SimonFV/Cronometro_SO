
module platform (
	clk_clk,
	pio_7segments_0_external_connection_export,
	pio_7segments_1_external_connection_export,
	pio_7segments_2_external_connection_export,
	pio_7segments_3_external_connection_export,
	pio_7segments_4_external_connection_export,
	pio_7segments_5_external_connection_export,
	pio_button_0_external_connection_export,
	pio_switch_0_external_connection_export,
	reset_reset_n);	

	input		clk_clk;
	output	[6:0]	pio_7segments_0_external_connection_export;
	output	[6:0]	pio_7segments_1_external_connection_export;
	output	[6:0]	pio_7segments_2_external_connection_export;
	output	[6:0]	pio_7segments_3_external_connection_export;
	output	[6:0]	pio_7segments_4_external_connection_export;
	output	[6:0]	pio_7segments_5_external_connection_export;
	input		pio_button_0_external_connection_export;
	input	[1:0]	pio_switch_0_external_connection_export;
	input		reset_reset_n;
endmodule
