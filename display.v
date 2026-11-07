module display (
    input wire clk,
    input wire rst,

    input wire clear,
    input wire draw_start,
    input wire [5:0] draw_x,
    input wire [4:0] draw_y,
    input wire [3:0] sprite_height,

    input wire [7:0] sprite_data,
    output reg [3:0] sprite_row,

    output reg busy,
    output reg draw_done,
    output reg collision,

    input wire [5:0] pixel_x,
    input wire [4:0] pixel_y,
    output wire pixel_out
);

    reg [2047:0] framebuffer;

    localparam IDLE  = 2'b00;
    localparam FETCH = 2'b01;
    localparam DRAW  = 2'b10;

    reg [1:0] state;

    reg [5:0] base_x;
    reg [4:0] base_y;
    reg [3:0] height_latched;

    reg [3:0] row_index;
    reg [2:0] bit_index;
    reg [7:0] sprite_latch;

    integer i;

    wire [5:0] draw_px = base_x + bit_index;
    wire [4:0] draw_py = base_y + row_index;

    wire [10:0] draw_addr =
        {draw_py, 6'b000000} + draw_px;

    wire [10:0] read_addr =
        {pixel_y, 6'b000000} + pixel_x;

    assign pixel_out = framebuffer[read_addr];

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state          <= IDLE;
            busy           <= 1'b0;
            draw_done      <= 1'b0;
            collision      <= 1'b0;

            base_x         <= 0;
            base_y         <= 0;
            height_latched <= 0;

            row_index      <= 0;
            bit_index      <= 0;
            sprite_row     <= 0;
            sprite_latch   <= 0;

            for (i = 0; i < 2048; i = i + 1)
                framebuffer[i] <= 1'b0;
        end
        else begin
            draw_done <= 1'b0;

            if (clear) begin
                state     <= IDLE;
                busy      <= 1'b0;
                collision <= 1'b0;

                for (i = 0; i < 2048; i = i + 1)
                    framebuffer[i] <= 1'b0;
            end
            else begin
                case (state)

                    IDLE: begin
                        busy <= 1'b0;

                        if (draw_start) begin
                            if (sprite_height == 0) begin
                                draw_done <= 1'b1;
                            end
                            else begin
                                base_x         <= draw_x;
                                base_y         <= draw_y;
                                height_latched <= sprite_height;

                                row_index  <= 0;
                                bit_index  <= 0;
                                sprite_row <= 0;
                                collision  <= 1'b0;

                                busy  <= 1'b1;
                                state <= FETCH;
                            end
                        end
                    end

                    FETCH: begin
                        sprite_latch <= sprite_data;
                        bit_index    <= 0;
                        state        <= DRAW;
                    end

                    DRAW: begin
                        if (sprite_latch[7 - bit_index]) begin

                            if (framebuffer[draw_addr])
                                collision <= 1'b1;

                            framebuffer[draw_addr] <=
                                ~framebuffer[draw_addr];
                        end

                        if (bit_index == 3'd7) begin

                            if (row_index ==
                                height_latched - 1'b1) begin

                                state     <= IDLE;
                                busy      <= 1'b0;
                                draw_done <= 1'b1;
                            end
                            else begin
                                row_index  <= row_index + 1'b1;
                                sprite_row <= row_index + 1'b1;
                                state      <= FETCH;
                            end
                        end
                        else begin
                            bit_index <= bit_index + 1'b1;
                        end
                    end

                    default: begin
                        state <= IDLE;
                        busy  <= 1'b0;
                    end

                endcase
            end
        end
    end

endmodule
