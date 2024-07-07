import subprocess
import sys



def compile_program(target):
    subprocess.run(["make", target])

def execute_program(program,mpi_processes, *args):
    command = f"mpirun -np {mpi_processes} ./{program} {' '.join(args)}"
    print("Executing command:", command)
    
    result = subprocess.run(command, capture_output=True, text=True, shell=True)
    print("Output:", result.stdout)
    print("Error:", result.stderr)
    print("Return Code:", result.returncode)
    output_lines = result.stdout.strip().split("\n")
    estimated_pi = float(output_lines[0].split(":")[1].strip())
    execution_time = float(output_lines[1].split(":")[1].strip().split()[0])
    return estimated_pi, execution_time



def run_and_plot(program, throws, mpi_processes):
    compile_program(program)
    estimated_pi, execution_time = execute_program(program, str(mpi_processes), str(throws))
    print(f"{program}: Estimated Pi: {estimated_pi}, Execution Time: {execution_time} seconds")
    return execution_time


def main(throws):
    
   

    for program in ["task1"]:
        with open(f"{program}_data.txt", "w") as data_file:
            for mpi_processes in [1, 2, 4]:
                total_time = 0
                times = 1
                for _ in range(times):  
                    execution_time = run_and_plot(program, throws, mpi_processes)
                    total_time += execution_time
                average_time = total_time / times # Calculate the average time
                data_file.write(f"{average_time} {mpi_processes}\n")

    # Create a Gnuplot script to plot the data
    gnuplot_script = f"""
    set terminal png
    set output 'plot.png'
    set title 'Time per MPI processes ({throws} throws)'
    set ylabel 'Time'
    set xlabel 'Processes'
    plot 'task1_data.txt' using 2:1 with linespoints title 'MPI', \
         'task1_data.txt' using 2:1:(sprintf("%.4f",$1)) with labels offset char 1,1 notitle
    """

    # Write the Gnuplot script to a file
    with open("plot.gnuplot", "w") as script_file:
        script_file.write(gnuplot_script)

    # Run the Gnuplot script
    subprocess.run(["gnuplot", "plot.gnuplot"])

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 script_name.py <number_of_throws>")
        sys.exit(1)
    
    try:
        throws = int(sys.argv[1])
    except ValueError:
        print("Please provide a valid integer for the number of throws.")
        sys.exit(1)
    
    main(throws)