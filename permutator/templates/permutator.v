module permutator (
<%

function dest (i, j) {
    const log2blockSize = obj.log2slices - j;
    const blockSize = 1 << log2blockSize;
    const log2halfBlockSize = log2blockSize - 1;
    const halfBlockSize = 1 << log2halfBlockSize;
    const offset = (i >> log2blockSize) << log2blockSize;
    const dest = i + halfBlockSize;
    return offset + (dest % blockSize);
}

for (let i = 0; i < slices; i++) { %>
// Slice <%= i %>
    input        [<%= obj.dataWidth - 1 %>:0] t<%= i %>_dat,
    input         [<%= obj.log2slices - 1 %>:0] adr<%= i %>,
    output logic [<%= obj.dataWidth - 1 %>:0] i<%= i %>_dat,<% } %>
    input clk, reset_n
);

<%
for (let i = 0; i < slices; i++) {
    for (let j = 0; j < obj.log2slices; j++) { %>
logic [<%= obj.dataWidth - 1 %>:0] dat_<%= i %>_<%= dest(i, j) %>;<%
    }
}
%>

<%
for (let i = 0; i < slices; i++) {
    for (let j = 1; j < obj.log2slices; j++) { %>
logic [<%= j - 1 %>:0] adr_<%= i %>_<%= dest(i, j) %>;<%
    }
}
%>

<% for (let i = 0; i < slices; i++) { %>
// Slice <%= i %>


permutator_slice u<%= i %> (

<% for (let j = 0; j < obj.log2slices; j++) { %>
    .i<%= j %>_dat(dat_<%= i %>_<%= dest(i, j) %>),<% } %>
    .i<%= obj.log2slices %>_dat(i<%= i %>_dat),

    .t0_dat(t<%= i %>_dat),
<% for (let j = 1; j <= obj.log2slices; j++) { %>
    .t<%= j %>_dat(dat_<%= dest(i, j - 1) %>_<%= i %>),<% } %>

<% for (let j = 1; j < obj.log2slices; j++) { %>
    .i<%= j %>_adr(adr_<%= i %>_<%= dest(i, j) %>),<% } %>
    .i<%= obj.log2slices %>_adr(adr<%= i %>),

<% for (let j = 2; j <= obj.log2slices; j++) { %>
    .t<%= j %>_adr(adr_<%= dest(i, j - 1) %>_<%= i %>),<% } %>


    .cfg(<%= obj.log2slices %>'d<%= i %>)
);
<% } %>

endmodule
