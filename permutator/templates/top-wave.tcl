<%
    const range = require('lodash.range');
%>

lappend system "clk"
lappend system "reset"

set num_added [ gtkwave::addSignalsFromList $system ]

gtkwave::/Edit/Insert_Comment "--- t_dat ---"
<%= range(slices).map(i => `lappend t_dat "top.t${i}_dat"`).join('\n') %>
set num_added [ gtkwave::addSignalsFromList $t_dat ]

gtkwave::/Edit/Insert_Comment "--- i_dat ---"
<%= range(slices).map(i => `lappend i_dat "top.i${i}_dat"`).join('\n') %>
set num_added [ gtkwave::addSignalsFromList $i_dat ]

gtkwave::/Edit/Insert_Comment "--- adr ---"
<%= range(slices).map(i => `lappend adr "top.adr${i}"`).join('\n') %>
set num_added [ gtkwave::addSignalsFromList $adr ]

gtkwave::setZoomFactor -2
