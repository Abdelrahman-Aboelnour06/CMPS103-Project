module ecess2bcd(
input wire d,
input wire c,
input wire b,
input wire a,
output wire w,
output wire x,
output wire y,
output wire z);

assign w = a & (b | (c & d));
assign x = (a&(~b)&(~c))|(b&c&d)|(a&c&(~d));
assign y = c ^ d;
assign z = ~d;


endmodule