module chip8_memory (
    input wire clk,
    input wire we,
    input wire [11:0] addr,
    input wire [7:0] din,
    output reg [7:0] dout
);

    reg [7:0] memory [0:4095];

    initial begin
        integer i;
        
        // 1. Wipe memory to zero
        for (i = 0; i < 4096; i = i + 1) begin
            memory[i] = 8'h00;
        end
        
        // 2. Load the fontset from our text file starting at address 0x050
        $readmemh("fontset.hex", memory, 12'h050, 12'h09F);
    end

    always @(posedge clk) begin
        if (we) begin
            memory[addr] <= din;
        end
        dout <= memory[addr];
    end

endmodule