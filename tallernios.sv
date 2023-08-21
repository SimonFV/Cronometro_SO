
module tallernios (
		input  logic	clk, rst_n,
		input logic [1:0]	switch,
		output logic [6:0] pio_7segments_0,
		output logic [6:0] pio_7segments_1,
		output logic [6:0] pio_7segments_2,
		output logic [6:0] pio_7segments_3,
		output logic [6:0] pio_7segments_4,
		output logic [6:0] pio_7segments_5,
		input  logic pio_button                    
	);
	
	logic [6:0] segments7_0,
					segments7_1,
					segments7_2,
					segments7_3,
					segments7_4,
					segments7_5;
	
	platform plat(
		.clk_clk(clk),
		.pio_7segments_0_external_connection_export(segments7_0),	
		.pio_7segments_1_external_connection_export(segments7_1),
		.pio_7segments_2_external_connection_export(segments7_2),
		.pio_7segments_3_external_connection_export(segments7_3),
		.pio_7segments_4_external_connection_export(segments7_4),
		.pio_7segments_5_external_connection_export(segments7_5),
		.pio_button_0_external_connection_export(pio_button),
		.pio_switch_0_external_connection_export(switch), 
		.reset_reset_n(rst_n)   
	);
	
	display7 s0(segments7_0[3:0], pio_7segments_0);
	display7 s1(segments7_1[3:0], pio_7segments_1);
	display7 s2(segments7_2[3:0], pio_7segments_2);
	display7 s3(segments7_3[3:0], pio_7segments_3);
	display7 s4(segments7_4[3:0], pio_7segments_4);
	display7 s5(segments7_5[3:0], pio_7segments_5);
	
	
endmodule
