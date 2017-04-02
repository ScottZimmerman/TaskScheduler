
[Insert Task Structure Image]

This example is based on my research. It illustrates dynamic task structures that are not known when the job is started.

We simulate populations from a set of different mathematical models based on a user's input, and measure the bias of a a set of study design and analysis procedures for each population.

The calculation of the bias is considered complete when the bias converges. Thus we need to periodically check for convergence. 

The python scripts that run the tasks are given prefixes for "levels": UK (user knowledge), CS (causal system), P (population), and S (study); and the suffixes C (coordination) and A (aggregation).

Convergence is checked in the P_A.py script. If the bias of any of the study design and analysis methods has not converged for a given population, the simulation is not complete. 

In the code the dynamic behavior is illustrated more simply: If the result of the P_A task is less than 200, two more S tasks and an additional P_A task are queued.