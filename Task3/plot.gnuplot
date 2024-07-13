
    set terminal png
    set output 'plot.png'
    set title 'Time per MPI processes (1000000000 throws)'
    set ylabel 'Time'
    set xlabel 'Processes'
    plot 'task3_data.txt' using 2:1 with linespoints title 'MPI',          'task3_data.txt' using 2:1:(sprintf("%.4f",$1)) with labels offset char 1,1 notitle
    