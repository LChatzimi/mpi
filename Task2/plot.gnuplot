
    set terminal png
    set output 'plot.png'
    set title 'Time per MPI processes (16000 size)'
    set ylabel 'Time'
    set xlabel 'Processes'
    plot 'task2_data.txt' using 2:1 with linespoints title 'MPI',          'task2_data.txt' using 2:1:(sprintf("%.4f",$1)) with labels offset char 1,1 notitle
    