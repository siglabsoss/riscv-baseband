#include "Vpermutator.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

<%
const range = require('lodash.range');
%>

int main(int argc, char **argv, char **env) {
    Verilated::commandArgs(argc, argv);
    Vpermutator* top = new Vpermutator;
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("permutator.vcd");

    top->clk = 1;
<%= range(slices).map(i => `    top->t${i}_dat = ${i};`).join('\n') %>

// arbitrary rotation
<% range(32).forEach(j => { %>
<%= range(slices).map(i => `    top->adr${i} = ${(i + j) % slices};`).join('\n') %>

    for (int clk = 0; clk < 2; clk++) {
        tfp->dump (<%= 2 * j %> + clk);
        top->clk = !top->clk;
        top->eval ();
    }

<% }); %>

// single word broadcast
<% range(36).forEach(j => { %>
<%= range(slices).map(i => `    top->adr${i} = ${j};`).join('\n') %>

    for (int clk = 0; clk < 2; clk++) {
        tfp->dump (<%= 2 * (j + 32) %> + clk);
        top->clk = !top->clk;
        top->eval ();
    }

<% }); %>

    tfp->close();
    exit(0);
}
